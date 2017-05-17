#ifndef __V_FUNC_H__
#define __V_FUNC_H__
/**********************************************************************************\
    ��ͼ�ļ���Ҫ����һЩ���õ�ȫ�ָ�������
    ����ߣ�  Vinca
              2003.11.4
\**********************************************************************************/
////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <tchar.h>
#include <stdarg.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <io.h>
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
/*----------------------------------------------------------------------------------
  ���WINDOWS�İ汾
  ����ֵ��-999  -- ����
      -2    -- win32s
      -1    -- win95
      0   -- win98
      1   -- winnt
      2   -- win2k
      999   -- ���߰汾
----------------------------------------------------------------------------------*/
inline int GetWinVer()
{
  int nRet ( -999 );
  BOOL bOsVersionInfoEx ( TRUE );
  OSVERSIONINFOEX osvi;
  ::ZeroMemory ( ( void* ) &osvi, sizeof ( OSVERSIONINFOEX ) );
  osvi.dwOSVersionInfoSize = sizeof ( OSVERSIONINFOEX );

  if ( ! ( bOsVersionInfoEx =::GetVersionEx ( ( LPOSVERSIONINFO ) &osvi ) ) )
  {
    ::ZeroMemory ( ( void* ) &osvi, sizeof ( OSVERSIONINFOEX ) );
    osvi.dwOSVersionInfoSize = sizeof ( OSVERSIONINFO );

    if ( !::GetVersionEx ( ( LPOSVERSIONINFO ) &osvi ) )
      return nRet;
  }

  //////
  switch ( osvi.dwPlatformId )
  {
    case VER_PLATFORM_WIN32s:
      nRet = -2;
      break;

    case VER_PLATFORM_WIN32_WINDOWS:
      if ( ( osvi.dwMajorVersion > 4 ) ||
           ( ( osvi.dwMajorVersion == 4 ) && ( osvi.dwMinorVersion > 0 ) ) )
        nRet = 0;

      else nRet = -1;

      break;

    case VER_PLATFORM_WIN32_NT:
      if ( osvi.dwMajorVersion <= 4 )
        nRet = 1;

      else if ( osvi.dwMajorVersion == 5 )
        nRet = 2;

      else
        nRet = 999;

      break;
  }

  //////
  return nRet;
}

/*----------------------------------------------------------------------------------
  RegisterComDll(): ���ڶԽ��������ע��/ע��
  ��ڲ���:
      lpcszDllFullPath -- ��ע���DLL����·������
      bRegister -- TRUE��ʾע�ᣬFALSE��ʾע��
  ����ֵ:
      -4��ʾDLL·�������Ƿ�
      -3��ʾDLLָ��·���²�����
      -2��ʾDLL����ں���������
      -1��ʾ��������ʧ��
      0��ʾ�ɹ�ִ��
----------------------------------------------------------------------------------*/
inline int RegisterComDll ( LPCTSTR lpcszDllFullPath, BOOL bRegister = TRUE )
{
  if ( NULL == lpcszDllFullPath || 0 == *lpcszDllFullPath )
    return -4;

  HINSTANCE hLib =::LoadLibrary ( lpcszDllFullPath );

  if ( NULL == hLib ) return -3;

  typedef long ( __stdcall * pFunc ) ( void );
  int ret ( 0 );

  if ( bRegister )
  {
    pFunc func = ( pFunc ) ::GetProcAddress ( ( HMODULE ) hLib, LPCSTR ( "DllRegisterServer" ) );

    if ( NULL != func )
    {
      long _r = func();

      if ( _r < 0 ) ret = -1;
    }

    else ret = -2;
  }

  else
  {
    pFunc func = ( pFunc ) ::GetProcAddress ( ( HMODULE ) hLib, LPCSTR ( "DllUnregisterServer" ) );

    if ( NULL != func )
    {
      long _r = func();

      if ( _r < 0 ) ret = -1;
    }

    else ret = -2;
  }

  ::FreeLibrary ( ( HMODULE ) hLib );
  return ret;
}

/*----------------------------------------------------------------------------------
  GetWinSysFreq(): ��ȡ��ǰ��ϵͳƵ��
----------------------------------------------------------------------------------*/
inline double GetWinSysFreq ( void )
{
  _LARGE_INTEGER dfValue;
  ::QueryPerformanceFrequency ( &dfValue );
  return ( double ) dfValue.QuadPart;
}

/*----------------------------------------------------------------------------------
  GetWinCurSysCounter(): ��ȡ��ǰ��ϵͳCOUNTER����ֵ
----------------------------------------------------------------------------------*/
inline LONGLONG GetWinCurSysCounter ( void )
{
  _LARGE_INTEGER dfValue;
  ::QueryPerformanceCounter ( &dfValue );
  return ( LONGLONG ) dfValue.QuadPart;
}
/*------------------------------------*/

inline DWORD GetCurTime_us()
{
  static double dbFreq = 0;
  LONGLONG tStart = 0, tEnd = 0, tDelay = 0;
  DWORD dwDelay;

  if ( dbFreq < 0.000001 )
    dbFreq = GetWinSysFreq();

  //  tDelay=(LONGLONG) (dbFreq*usToDelay/1000000.0);
  tStart = GetWinCurSysCounter();
  dwDelay = ( 1000000.0 / dbFreq ) * tStart;
  return ( DWORD ) ( dwDelay );
}

inline DWORD GetCurTime_ms()
{
  static double dbFreq = 0;
  LONGLONG tStart = 0, tEnd = 0, tDelay = 0;
  DWORD dwDelay;

  if ( dbFreq < 0.000001 )
    dbFreq = GetWinSysFreq();

  //  tDelay=(LONGLONG) (dbFreq*usToDelay/1000000.0);
  tStart = GetWinCurSysCounter();
  dwDelay = ( 1000000.0 / dbFreq ) * tStart;
  return ( DWORD ) ( dwDelay / 1000 );
}
/*----------------------------------------------------------------------------------
  vDelay_us(): us��λ����ʱ
  vDelay_ms(): ms��λ����ʱ
  vDelay_s():  s��λ����ʱ
----------------------------------------------------------------------------------*/
inline void vDelay_us ( double usToDelay )
{
  static double dbFreq = 0;
  LONGLONG tStart, tEnd, tDelay = 0;

  if ( dbFreq < 0.000001 )
    dbFreq = GetWinSysFreq();

  if ( usToDelay < 0 ) usToDelay = 0;

  tDelay = ( LONGLONG ) ( dbFreq * usToDelay / 1000000.0 );
  tStart = GetWinCurSysCounter();

  while ( 1 )
  {
    tEnd = GetWinCurSysCounter();

    if ( tEnd < tStart || ( tEnd - tStart ) >= tDelay )
      break;
  }
}

inline void vDelay_ms ( double msToDelay )
{
  vDelay_us ( msToDelay * 1000.0 );
}
inline void vDelay_s ( double sToDelay )
{
  vDelay_us ( sToDelay * 1000000.0 );
}


/*----------------------------------------------------------------------------------
  ������Ϣѭ���ĵȴ�
----------------------------------------------------------------------------------*/
inline void DoEvent ( void )
{
  MSG msg;

  while ( ::PeekMessage ( &msg, NULL, 0, 0, PM_REMOVE ) )
  {
    ::TranslateMessage ( &msg );
    ::DispatchMessage ( &msg );
  }
}

/*----------------------------------------------------------------------------------
  ��ȡָ�����ڵĶ������ھ��
----------------------------------------------------------------------------------*/
inline HWND GetTopHwnd ( HWND hWnd )
{
  HWND hwndPre = hWnd;

  if ( !::IsWindow ( hWnd ) ) return ( HWND ) NULL;

  while ( ::IsWindow ( hwndPre ) )
  {
    hWnd = hwndPre;
    hwndPre = ( HWND ) ::GetWindowLong ( hWnd, GWL_HWNDPARENT );
  }

  return hWnd;
}

/*----------------------------------------------------------------------------------
  hdc--����DC;
  bRatio--λͼ�Ƿ�������Ŵ���(�����У���cx�������ź�Ŀ�ȣ�
                    cy�������ź�ĸ߶�)
  x,y--����Ŀ��hdc�ϻ滭��λ���������
----------------------------------------------------------------------------------*/
inline void DrawTransBmp ( HDC hdc, HBITMAP hBitmap, BOOL bRatio,
                           int x = 0, int y = 0, int cx = 0, int cy = 0, COLORREF clr = RGB ( 255, 255, 255 ) )
{
  ////////�������
  if ( ( !hdc ) || ( !hBitmap ) ) return;

  BITMAP bm;
  memset ( ( void* ) &bm, 0, sizeof ( BITMAP ) );
  ::GetObject ( hBitmap, sizeof ( BITMAP ), &bm );

  if ( ( !bRatio ) || ( bRatio && ( ( 0 == cx ) || ( 0 == cy ) ) ) )
  {
    cx = bm.bmWidth;
    cy = bm.bmHeight;
  }

  ////////
  HDC dcIm =::CreateCompatibleDC ( hdc );
  ::SetMapMode ( dcIm, ::GetMapMode ( hdc ) );
  HBITMAP hbIm = ( HBITMAP ) ::SelectObject ( dcIm, hBitmap );
  ////
  HDC dcImage =::CreateCompatibleDC ( hdc );
  ::SetMapMode ( dcImage, ::GetMapMode ( hdc ) );
  HBITMAP hBitmapImage =::CreateCompatibleBitmap ( hdc, cx, cy );
  HBITMAP hOldBitmapImage = ( HBITMAP ) ::SelectObject ( dcImage, hBitmapImage );
  ::StretchBlt ( dcImage, 0, 0, cx, cy, dcIm, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY );
  ////
  ::SelectObject ( dcIm, hbIm );
  ::DeleteDC ( dcIm );
  ////
  HDC dcAnd =::CreateCompatibleDC ( hdc );
  ::SetMapMode ( dcAnd, ::GetMapMode ( hdc ) );
  HBITMAP bitmapAnd =::CreateBitmap ( cx, cy, 1, 1, NULL );
  HBITMAP hOldBitmapAnd = ( HBITMAP ) ::SelectObject ( dcAnd, bitmapAnd );
  ::SetBkColor ( dcImage, clr );
  ::BitBlt ( dcAnd, 0, 0, cx, cy, dcImage, 0, 0, SRCCOPY );
  HDC dcXor =::CreateCompatibleDC ( hdc );
  ::SetMapMode ( dcXor, ::GetMapMode ( hdc ) );
  HBITMAP bitmapXor =::CreateCompatibleBitmap ( dcImage, cx, cy );
  HBITMAP hOldBitmapXor = ( HBITMAP ) ::SelectObject ( dcXor, bitmapXor );
  ::BitBlt ( dcXor, 0, 0, cx, cy, dcImage, 0, 0, SRCCOPY );
  ::BitBlt ( dcXor, 0, 0, cx, cy, dcAnd, 0, 0, 0x220326 );
  HDC dcTemp = CreateCompatibleDC ( hdc );
  ::SetMapMode ( dcTemp, ::GetMapMode ( hdc ) );
  HBITMAP bitmapTemp =::CreateCompatibleBitmap ( dcImage, cx, cy );
  HBITMAP hOldBitmapTemp = ( HBITMAP ) ::SelectObject ( dcTemp, bitmapTemp );
  ::BitBlt ( dcTemp, 0, 0, cx, cy, hdc, x, y, SRCCOPY );
  ::BitBlt ( dcTemp, 0, 0, cx, cy, dcAnd, 0, 0, SRCAND );
  ::BitBlt ( dcTemp, 0, 0, cx, cy, dcXor, 0, 0, SRCINVERT );
  ::BitBlt ( hdc, x, y, cx, cy, dcTemp, 0, 0, SRCCOPY );
  ////////
  ::DeleteObject ( ::SelectObject ( dcImage, hOldBitmapImage ) );
  ::DeleteDC ( dcImage );
  ::DeleteObject ( ::SelectObject ( dcAnd, hOldBitmapAnd ) );
  ::DeleteDC ( dcAnd );
  ::DeleteObject ( ::SelectObject ( dcXor, hOldBitmapXor ) );
  ::DeleteDC ( dcXor );
  ::DeleteObject ( ::SelectObject ( dcTemp, hOldBitmapTemp ) );
  ::DeleteDC ( dcTemp );
}

/*----------------------------------------------------------------------------------
  ��ȡ2���ľ���
----------------------------------------------------------------------------------*/
inline double Points2Dist ( double x1, double y1, double x2, double y2 )
{
  double tmp1 = x1 - x2;
  double tmp2 = y1 - y2;
  double ret = tmp1 * tmp1 + tmp2 * tmp2;
  return ::sqrt ( ret );
}

/*----------------------------------------------------------------------------------
  ��ȡ����ֵ�е���С�����ֵֵ
----------------------------------------------------------------------------------*/
template<class T>
T Min ( T& t1, T& t2 )
{
  return ( t1 < t2 ? t1 : t2 );
}
template<class T>
T Max ( T& t1, T& t2 )
{
  return ( t1 > t2 ? t1 : t2 );
}

/*----------------------------------------------------------------------------------
  GetBit(): ����ָ����ֵ�е�ָ��λ��״̬(1--����TRUE��0--����FALSE)
----------------------------------------------------------------------------------*/
template<class T>
BOOL GetBit ( const T tValue, const int nIndex )
{
  assert ( nIndex > -1 && nIndex < 32 );
  BOOL bRet ( FALSE );
  DWORD dwMask ( 0x01 );
  DWORD dwTmp ( 0 );

  switch ( sizeof ( T ) )
  {
    case 4:
    case 3:
    case 2:
    case 1:
      dwMask <<= nIndex;
      dwTmp = dwMask & tValue;

      if ( dwTmp != 0 ) bRet = TRUE;

      break;

    default:
      break;
  }

  ////////
  return bRet;
}

/*----------------------------------------------------------------------------------
  ���2ָ���Ƿ��ص�
----------------------------------------------------------------------------------*/
template<class T>
BOOL IsPtrEqual64 ( const T* pDest, const __int64* pSrc )
{
  BOOL bRet ( FALSE );
  T* pTmp = NULL;

  ////
  switch ( sizeof ( T ) )
  {
    case 8:
      if ( ( ( __int64* ) pDest ) == pSrc ) bRet = TRUE;

      break;

    case 4:
      pTmp = ( T* ) pSrc;

      if ( pDest == pTmp || pDest == ( pTmp + 1 ) ) bRet = TRUE;

      break;

    case 2:
      pTmp = ( T* ) pSrc;

      if ( pDest == pTmp || pDest == ( pTmp + 1 ) || pDest == ( pTmp + 2 ) || pDest == ( pTmp + 3 ) )
        bRet = TRUE;

      break;

    default:  //1
      pTmp = ( T* ) pSrc;

      if ( pDest == pTmp || pDest == ( pTmp + 1 ) || pDest == ( pTmp + 2 ) || pDest == ( pTmp + 3 ) ||
           pDest == ( pTmp + 4 ) || pDest == ( pTmp + 5 ) || pDest == ( pTmp + 6 ) || pDest == ( pTmp + 7 ) )
        bRet = TRUE;

      break;
  }

  //
  return bRet;
}

template<class T>
BOOL IsPtrEqual32 ( const T* pDest, const __int32* pSrc )
{
  BOOL bRet ( FALSE );
  T* pTmp = NULL;

  ////
  switch ( sizeof ( T ) )
  {
    case 8:
    case 4:
      if ( ( ( __int32* ) pDest ) == pSrc ) bRet = TRUE;

      break;

    case 2:
      pTmp = ( T* ) pSrc;

      if ( pDest == pTmp || pDest == ( pTmp + 1 ) ) bRet = TRUE;

      break;

    default:  //1
      pTmp = ( T* ) pSrc;

      if ( pDest == pTmp || pDest == ( pTmp + 1 ) || pDest == ( pTmp + 2 ) || pDest == ( pTmp + 3 ) )
        bRet = TRUE;

      break;
  }

  //
  return bRet;
}

/*----------------------------------------------------------------------------------
  ������ǶȻ���ת������
----------------------------------------------------------------------------------*/
inline double GetArcAssoValue ( double dbDest, BOOL bArcToAngle = TRUE )
{
  double dbRet = 0;

  if ( bArcToAngle ) //����ת���ɽǶ�
  {
    dbRet = 180.0 / 3.141592653589793;
    dbRet *= dbDest;
  }

  else //�Ƕ�ת���ɻ���
  {
    dbRet = 3.141592653589793 / 180.0;
    dbRet *= dbDest;
  }

  return dbRet;
}

/*----------------------------------------------------------------------------------
  ���ָ���ļ��Ƿ����
----------------------------------------------------------------------------------*/
inline BOOL vFileIsExist ( LPCTSTR lpszFullPathName )
{
  DWORD attr =::GetFileAttributes ( lpszFullPathName );

  if ( -1 == attr || ( FILE_ATTRIBUTE_DIRECTORY & attr ) == FILE_ATTRIBUTE_DIRECTORY )
    return FALSE;

  return TRUE;
}

/*----------------------------------------------------------------------------------
  ���ָ��Ŀ¼�Ƿ����
----------------------------------------------------------------------------------*/
inline BOOL vPathIsExist ( LPCTSTR lpszPath )
{
  DWORD attr =::GetFileAttributes ( lpszPath );

  if ( -1 == attr || ( FILE_ATTRIBUTE_DIRECTORY & attr ) != FILE_ATTRIBUTE_DIRECTORY )
    return FALSE;

  return TRUE;
}

/*----------------------------------------------------------------------------------
  ����ָ���ļ�
----------------------------------------------------------------------------------*/
inline BOOL vCreateFile ( LPCTSTR lpszFullPathName )
{
  if ( !vFileIsExist ( lpszFullPathName ) )
  {
    HANDLE hFile =::CreateFile ( lpszFullPathName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,
                                 NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_NORMAL,
                                 NULL );

    if ( INVALID_HANDLE_VALUE == hFile )
      return FALSE;

    ::CloseHandle ( hFile );
  }

  return TRUE;
}

/*----------------------------------------------------------------------------------
  �������OutputDebugString()�����ķ�װ���������������Ϣ�����
----------------------------------------------------------------------------------*/
inline void vInfoPrint ( const char* fmt, ... )
{
  char buf[8192];
  buf[0] = 0;
  va_list ap;
  va_start ( ap, fmt );
  vsprintf ( buf, fmt, ap );
  va_end ( ap );
  ::OutputDebugStringA ( buf );
}

/*----------------------------------------------------------------------------------
  �ַ���IP��ַת����4��BYTE
  192.168.1.2 ==>> cbHh=192; chHl=168; cbLh=1; cbLl=2;
----------------------------------------------------------------------------------*/
inline void vGetBytesIP ( LPCSTR lpcszIp, BYTE& cbHh, BYTE& cbHl, BYTE& cbLh, BYTE& cbLl )
{
  cbHh = cbHl = cbLh = cbLl = 0;

  if ( NULL == lpcszIp || 0 == *lpcszIp )
    return;

  char* pCh = ( char* ) ( LPCSTR ) lpcszIp;

  if ( pCh ) cbHh = ( BYTE ) ::strtol ( pCh, NULL, 10 );

  pCh =::strchr ( pCh, ( '.' ) );
  pCh++;

  if ( pCh ) cbHl = ( BYTE ) ::strtol ( pCh, NULL, 10 );

  pCh =::strchr ( pCh, ( '.' ) );
  pCh++;

  if ( pCh ) cbLh = ( BYTE ) ::strtol ( pCh, NULL, 10 );

  pCh =::strchr ( pCh, ( '.' ) );
  pCh++;

  if ( pCh ) cbLl = ( BYTE ) ::strtol ( pCh, NULL, 10 );
}

/*----------------------------------------------------------------------------------
  IP��ַ��4�ֽ�DWORD��4��BYTE�Ļ���ת��
----------------------------------------------------------------------------------*/
inline void vIPConverDWORD ( DWORD& dwIp, BYTE& cbHh, BYTE& cbHl,
                             BYTE& cbLh, BYTE& cbLl, BOOL bIpTo4Bytes = TRUE )
{
  if ( bIpTo4Bytes ) //DWORD==>>4Bytes
  {
    cbHh = HIBYTE ( HIWORD ( dwIp ) );
    cbHl = LOBYTE ( HIWORD ( dwIp ) );
    cbLh = HIBYTE ( LOWORD ( dwIp ) );
    cbLl = LOBYTE ( LOWORD ( dwIp ) );
  }

  else //4Bytes==>>DWORD
  {
    dwIp = MAKELONG ( MAKEWORD ( cbLl, cbLh ), MAKEWORD ( cbHl, cbHh ) );
  }
}

/*----------------------------------------------------------------------------------
  ִ�е��Թػ�����
  dwMask ���� Bit31~~Bit28��0001��ʾͬʱǿ�ƹر����н���
                0010��ʾͬʱǿ�ƹرղ���Ӧ�Ľ���
        Bit3~~Bit0��0000��ʾ�ػ����رյ�Դ
              0001��ʾ�ر�ϵͳ
              0010��ʾϵͳ����
              0011��ʾע��

----------------------------------------------------------------------------------*/
inline void vCloseComputer ( DWORD dwMask = 0x00 )
{
  ////���Win2K�����ϵ�����Ȩ�޵����⴦��
  if ( ::GetWinVer() > 0 )
  {
    TOKEN_PRIVILEGES tp;
    memset ( &tp, 0, sizeof ( tp ) );
    HANDLE hToken = NULL;
    LUID luid;
    memset ( &luid, 0, sizeof ( luid ) );

    if ( !::OpenProcessToken ( GetCurrentProcess(),
                               TOKEN_ADJUST_PRIVILEGES,
                               &hToken ) )
    {
      return;
    }

    if ( !::LookupPrivilegeValue ( NULL, SE_SHUTDOWN_NAME, &luid ) )
    {
      return;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    ::AdjustTokenPrivileges ( hToken, FALSE, &tp, 0, NULL, NULL );
  }

  ////ִ�йرյ��ԵĲ���
  UINT uFlags = 0x00;

  //������־
  switch ( 0x0F & ( dwMask >> 28 ) )
  {
    case 0x01:
      uFlags |= EWX_FORCE;
      break;

    case 0x02:
      if ( ::GetWinVer() > 0 )
      {
        uFlags |= 0x00000010;
      }

      break;
  }

  //ִ�б�־
  switch ( 0x0F & dwMask )
  {
    case 0x01:
      uFlags |= EWX_SHUTDOWN;
      break; //��ʾ�ر�ϵͳ

    case 0x02:
      uFlags |= EWX_REBOOT;
      break; //��ʾϵͳ����

    case 0x03:
      uFlags |= EWX_LOGOFF;
      break; //��ʾע��

    default:
      uFlags |= EWX_POWEROFF;
      break; //��ʾ�ػ����رյ�Դ
  }

  ::ExitWindowsEx ( uFlags, 0x00 );
}

/*----------------------------------------------------------------------------------
  ��ȡָ�����ļ�
  lpcszTitle������ʾ�ı���
  lpcszFilter��_T("Dll Files (*.dll)|*.dll|Ocx Files (*.ocx)|*.ocx|All Files (*.*)|*.*||")
  lpcszInitDir����ʼ·��
  lpcszDefExt��Ĭ�ϵ��ļ���չ��(������".")������_T("txt")
  dwMaskStyle��bit0 ���� 1��ʾ��ʾ�Ѵ��ڵ��ļ�
        bit1 ���� 1��ʾ��ʾ�����ļ�
        bit2 ���� 1��ʾ�������ļ�ʱ������ʾ����
        bit3 ���� 1��ʾ·���������
  ����ֵ�������ص�ֵ��ΪNULL���������������ͷ��ڴ�(delete[])
----------------------------------------------------------------------------------*/
inline TCHAR* vGetFile ( LPCTSTR lpcszTitle, LPCTSTR lpcszFilter,
                         LPCTSTR lpcszInitDir,
                         HINSTANCE hInst, HWND hWndParent,
                         DWORD dwMaskStyle = 0x01, LPCTSTR lpcszDefExt = NULL )
{
  ////////
  TCHAR szDefaultFilter[64] = _T ( "All Files (*.*)|*.*||" );
  TCHAR szFilter[256] = _T ( "" );
  TCHAR szTitle[256] = _T ( "" );
  TCHAR szInitDir[256] = _T ( "" );
  TCHAR szReceive[1024] = _T ( "" );
  TCHAR szDefExt[16] = _T ( "" );
  TCHAR* pCh = NULL;
  ////
  OPENFILENAME of;
  memset ( &of, 0, sizeof ( OPENFILENAME ) );
  of.lStructSize = sizeof ( OPENFILENAME );
  of.Flags = OFN_LONGNAMES;

  if ( 0x01 & dwMaskStyle ) of.Flags |= OFN_FILEMUSTEXIST;

//  if( 0x02&dwMaskStyle ) of.Flags |= OFN_FORCESHOWHIDDEN;
  if ( 0x04 & dwMaskStyle ) of.Flags |= OFN_CREATEPROMPT;

  if ( 0x08 & dwMaskStyle ) of.Flags |= OFN_PATHMUSTEXIST;

  of.hwndOwner = hWndParent;
  of.hInstance = hInst;

  if ( NULL == lpcszFilter || 0 == *lpcszFilter )
    ::_tcscpy ( szFilter, szDefaultFilter );

  else
    ::_tcscpy ( szFilter, lpcszFilter );

  pCh = &szFilter[0];

  while ( ( pCh =::_tcschr ( pCh, TCHAR ( '|' ) ) ) != NULL ) * pCh++ = TCHAR ( '\0' );

  of.lpstrFilter = &szFilter[0];

  if ( NULL != lpcszTitle && 0 != *lpcszTitle )
    ::_tcscpy ( szTitle, lpcszTitle );

  of.lpstrTitle = &szTitle[0];

  if ( NULL == lpcszInitDir || 0 == *lpcszInitDir )
    ::GetCurrentDirectory ( 256, szInitDir );

  else
    ::_tcscpy ( szInitDir, lpcszInitDir );

  of.lpstrInitialDir = &szInitDir[0];

  if ( NULL != lpcszDefExt && 0 != *lpcszDefExt )
  {
    if ( ::_tcslen ( lpcszDefExt ) > 3 ) ::_tcsncpy ( szDefExt, lpcszDefExt, 3 );

    else ::_tcscpy ( szDefExt, lpcszDefExt );
  }

  of.lpstrDefExt = &szDefExt[0];
  of.lpstrFile = &szReceive[0];
  of.nMaxFile = 1024;

  if ( ::GetOpenFileName ( &of ) )
  {
    int len =::_tcslen ( of.lpstrFile );
    pCh = new TCHAR[len + 1];

    if ( NULL != pCh )
      ::_tcscpy ( pCh, of.lpstrFile );

    return pCh;
  }

  return NULL;
}

/*----------------------------------------------------------------------------------
  ��ȡ��ǰ�������ڵ�·��
----------------------------------------------------------------------------------*/
inline BOOL GetLocalPath ( LPTSTR lpszRetBuff, long nBuffSize, BOOL bCorrect = TRUE )
{
  int len;
  TCHAR *pCh;
  TCHAR* pszPath = new TCHAR[1024];
  ////
  ::GetModuleFileName ( NULL, pszPath, 1024 );
  pCh =::_tcsrchr ( pszPath, TCHAR ( '\\' ) );

  if ( bCorrect )
  {
    if ( NULL == pCh )
    {
      len =::_tcslen ( pszPath );
      pszPath[len] = TCHAR ( '\\' );
      len++;
      pszPath[len] = 0;
    }

    else
    {
      pCh++;
      *pCh = 0;
    }
  }

  else
  {
    if ( NULL != pCh )
    {
      *pCh = 0;
    }
  }

  ////
  len =::_tcslen ( pszPath );

  if ( NULL == lpszRetBuff || len < 1 || nBuffSize < ( len + 1 ) )
  {
    if ( NULL != lpszRetBuff )
      lpszRetBuff[0] = 0;

    delete[] pszPath;
    return FALSE;
  }

  else
  {
    memcpy ( lpszRetBuff, pszPath, sizeof ( TCHAR ) * ( len + 1 ) );
    delete[] pszPath;
    return TRUE;
  }
}
//
inline BOOL IsDigital ( CString str )
{
  TCHAR szBuff;

  if ( str.GetLength() <= 0 )
    return FALSE;

  for ( int i = 0; i < str.GetLength(); i++ )
  {
    szBuff = str[i];

    if ( szBuff == 46 || szBuff == 45 ) //"-","."�����ж�
      continue;

    if ( !::isdigit ( szBuff ) ) //�����ж�
    {
      return FALSE;
    }
  }

  return TRUE;
}
/*----------------------------------------------------------------------------------
  vGetUnicodeFromMultiByte()����MultiByteת����Unicode
  ����ֵ��0ʧ�ܣ��ɹ�ʱ����unicode�ַ����ַ�����
      �ɹ�ʱ���ⲿ���ͷ�*ppszUnicodeRet�ڴ�
----------------------------------------------------------------------------------*/
inline int vGetUnicodeFromMultiByte ( const char* pszMultiByte, wchar_t** ppszUnicodeRet, UINT nCodePage = -1 )
{
  int nRlt = 0;

  if ( NULL != ppszUnicodeRet )
  {
    *ppszUnicodeRet = NULL;
  }

  if ( NULL != pszMultiByte && 0 != *pszMultiByte && NULL != ppszUnicodeRet )
  {
    if ( -1 == nCodePage ) //���ش���ҳ
    {
      nCodePage = ::GetACP();
    }

    int nSize = ::MultiByteToWideChar ( nCodePage, 0, pszMultiByte, -1, NULL, 0 );
    *ppszUnicodeRet = new wchar_t[nSize + 1];
    nRlt = ::MultiByteToWideChar ( nCodePage, 0, pszMultiByte, -1, *ppszUnicodeRet, nSize );

    if ( 0 == nRlt )
    {
      delete[] *ppszUnicodeRet;
      *ppszUnicodeRet = NULL;
    }
  }

  return nRlt;
}

/*----------------------------------------------------------------------------------
  vGetMultiByteFromUnicode()����Unicodeת����MultiByte
  ����ֵ��0ʧ�ܣ��ɹ�ʱ����MultiByte�ַ����ַ�����
      �ɹ�ʱ���ⲿ���ͷ�*ppszMultiByteRet�ڴ�
----------------------------------------------------------------------------------*/
inline int vGetMultiByteFromUnicode ( const wchar_t* pszUnicode, char** ppszMultiByteRet, UINT nCodePage = -1 )
{
  int nRlt = 0;

  if ( NULL != ppszMultiByteRet )
  {
    *ppszMultiByteRet = NULL;
  }

  if ( NULL != pszUnicode && 0x00 != *pszUnicode && NULL != ppszMultiByteRet )
  {
    if ( -1 == nCodePage ) //���ش���ҳ
    {
      nCodePage = ::GetACP();
    }

    int nSize = ::WideCharToMultiByte ( nCodePage, 0, pszUnicode, -1, NULL, 0, NULL, NULL );
    *ppszMultiByteRet = new char[nSize + 1];
    nRlt = ::WideCharToMultiByte ( nCodePage, 0, pszUnicode, -1, *ppszMultiByteRet, nSize, NULL, NULL );

    if ( 0 == nRlt )
    {
      delete[] *ppszMultiByteRet;
      *ppszMultiByteRet = NULL;
    }
  }

  return nRlt;
}
inline double liabs ( double a )
{
  if ( a < 0 )
  {
    a = 0 - a;
  }

  return a;
}
inline CString CircleFitByPratt ( double x[], double y[], int n, double* ArcX, double* ArcY, double* ArcRadius )
{
  int i = 0;
  double tmpx = 0;
  double tmpy = 0;
  double Xi = 0, Yi = 0, Zi = 0;

  for ( i = 0; i < n; i++ )
  {
    tmpx += x[i];
    tmpy += y[i];
  }

  tmpx = tmpx / n;
  tmpy = tmpy / n;

  double centroidx = tmpx;
  double centroidy = tmpy;
  double Mxx = 0, Myy = 0, Mxy = 0, Mxz = 0, Myz = 0, Mzz = 0;

  for ( i = 0; i < n ; i++ )
  {
    Xi = x[i] - centroidx;
    Yi = y[i] - centroidy;
    Zi = Xi * Xi + Yi * Yi;
    Mxy = Mxy + Xi * Yi;
    Mxx = Mxx + Xi * Xi;
    Myy = Myy + Yi * Yi;
    Mxz = Mxz + Xi * Zi;
    Myz = Myz + Yi * Zi;
    Mzz = Mzz + Zi * Zi;
  }

  Mxx = Mxx / n;
  Myy = Myy / n;
  Mxy = Mxy / n;
  Mxz = Mxz / n;
  Myz = Myz / n;
  Mzz = Mzz / n;
  double  Mz = Mxx + Myy;
  double  Cov_xy = Mxx * Myy - Mxy * Mxy;
  double  Mxz2 = Mxz * Mxz;
  double  Myz2 = Myz * Myz;

  double  A2 = 4 * Cov_xy - 3 * Mz * Mz - Mzz;
  double  A1 = Mzz * Mz + 4 * Cov_xy * Mz - Mxz2 - Myz2 - Mz * Mz * Mz;
  double  A0 = Mxz2 * Myy + Myz2 * Mxx - Mzz * Cov_xy - 2 * Mxz * Myz * Mxy + Mz * Mz * Cov_xy;
  double  A22 = A2 + A2;
  double  epsilon = 1e-12;
  double  ynew = 1e+20;
  double  IterMax = 20;
  double  xnew = 0;

  for ( i = 0; i < IterMax; i++ )
  {
    double  yold = ynew;
    ynew = A0 + xnew * ( A1 + xnew * ( A2 + 4.*xnew * xnew ) );

    if ( liabs ( ynew ) > liabs ( yold ) )
    {
      //AfxMessageBox(_T("Newton-Pratt goes wrong direction: |ynew| > |yold|"));
      ::OutputDebugString ( _T ( "Newton-Pratt goes wrong direction: |ynew| > |yold|" ) ) ;
      xnew = 0;
      break;
    }

    double    Dy = A1 + xnew * ( A22 + 16 * xnew * xnew );
    double    xold = xnew;
    xnew = xold - ynew / Dy;

    if ( liabs ( ( xnew - xold ) / xnew ) < epsilon )
      break;

    if ( i >= IterMax )
    {
      //AfxMessageBox(_T("Newton-Pratt will not converge"));
      ::OutputDebugString ( _T ( "Newton-Pratt will not converge" ) ) ;
      xnew = 0;
    }

    if ( xnew < 0 )
    {
      CString tmp ;
      tmp.Format ( _T ( "Newton-Pratt negative root:  x=%f\n" ), xnew );
      ::OutputDebugString ( tmp ) ;
      //AfxMessageBox(tmp);
      xnew = 0;
    }

    double  DET = xnew * xnew - xnew * Mz + Cov_xy;
    double  Centerx = ( Mxz * ( Myy - xnew ) - Myz * Mxy ) / DET / 2;
    double  Centery = ( Myz * ( Mxx - xnew ) - Mxz * Mxy ) / DET / 2;
    double  Parx = Centerx + centroidx;
    double  Pary = Centery + centroidy;
    double  Parz = sqrt ( Centerx * Centerx + Centery * Centery + Mz );

    CString tmp ;
    tmp.Format ( _T ( "%2d����:%f, %f, %f\n" ), n, Parx, Pary, Parz );
    ::OutputDebugString ( tmp ) ;
    //AfxMessageBox(tmp) ;
    *ArcX = Parx ;
    *ArcY = Pary ;
    *ArcRadius = Parz ;
    return tmp;
  }

}
inline CString CircleFitByTaubin ( double x[], double y[], int n )
{
  int i = 0;
  double tmpx = 0;
  double tmpy = 0;
  double Xi = 0, Yi = 0, Zi = 0;

  for ( i = 0; i < n; i++ )
  {
    tmpx += x[i];
    tmpy += y[i];
  }

  tmpx = tmpx / n;
  tmpy = tmpy / n;

  double centroidx = tmpx;
  double centroidy = tmpy;
  double Mxx = 0, Myy = 0, Mxy = 0, Mxz = 0, Myz = 0, Mzz = 0;

  for ( i = 0; i < n ; i++ )
  {
    Xi = x[i] - centroidx;
    Yi = y[i] - centroidy;
    Zi = Xi * Xi + Yi * Yi;
    Mxy = Mxy + Xi * Yi;
    Mxx = Mxx + Xi * Xi;
    Myy = Myy + Yi * Yi;
    Mxz = Mxz + Xi * Zi;
    Myz = Myz + Yi * Zi;
    Mzz = Mzz + Zi * Zi;
  }

  Mxx = Mxx / n;
  Myy = Myy / n;
  Mxy = Mxy / n;
  Mxz = Mxz / n;
  Myz = Myz / n;
  Mzz = Mzz / n;

  double  Mz = Mxx + Myy;
  double  Cov_xy = Mxx * Myy - Mxy * Mxy;
  double  A3 = 4 * Mz;
  double  A2 = -3 * Mz * Mz - Mzz;
  double  A1 = Mzz * Mz + 4 * Cov_xy * Mz - Mxz * Mxz - Myz * Myz - Mz * Mz * Mz;
  double  A0 = Mxz * Mxz * Myy + Myz * Myz * Mxx - Mzz * Cov_xy - 2 * Mxz * Myz * Mxy + Mz * Mz * Cov_xy;
  double  A22 = A2 + A2;
  double  A33 = A3 + A3 + A3;
  double  xnew = 0;
  double  ynew = 1e+20;
  double  epsilon = 1e-12;
  double  IterMax = 20;

  for ( i = 0; i < IterMax; i++ )
  {
    double  yold = ynew;
    ynew = A0 + xnew * ( A1 + xnew * ( A2 + xnew * A3 ) );

    if ( liabs ( ynew ) > liabs ( yold ) )
    {
      AfxMessageBox ( _T ( "Newton-Taubin goes wrong direction: |ynew| > |yold|" ) );
      xnew = 0;
      break;
    }

    double    Dy = A1 + xnew * ( A22 + xnew * A33 );
    double    xold = xnew;
    xnew = xold - ynew / Dy;

    if ( liabs ( ( xnew - xold ) / xnew ) < epsilon )
      break;

    if ( i >= IterMax )
    {
      AfxMessageBox ( _T ( "Newton-Taubin will not converge" ) );
      xnew = 0;
    }

    if ( xnew < 0 )
    {
      CString tmp ;
      tmp.Format ( _T ( "Newton-Taubin negative root:  x=%f\n" ), xnew );
      AfxMessageBox ( tmp );
      xnew = 0;
    }
  }

  double  DET = xnew * xnew - xnew * Mz + Cov_xy;
  double  Centerx = ( Mxz * ( Myy - xnew ) - Myz * Mxy ) / DET / 2;
  double  Centery = ( Myz * ( Mxx - xnew ) - Mxz * Mxy ) / DET / 2;
  double  Parx = Centerx + centroidx;
  double  Pary = Centery + centroidy;
  double  Parz = sqrt ( Centerx * Centerx + Centery * Centery + Mz );

  CString tmp ;
  tmp.Format ( _T ( "%2d����:%f, %f, %f\n" ), n, Parx, Pary, Parz );
  AfxMessageBox ( tmp ) ;
  return tmp;

}

inline CString GetStringByVal ( int nGray )
{
  CString strText ;
  strText.Format ( "%d", nGray );

  if ( strText.GetLength() == 1 )
  {
    strText = "00" + strText + "T" ;
  }

  else if ( strText.GetLength() == 2 )
  {
    strText = "0" + strText + "T";
  }

  else
  {
    strText = strText + "T";

  }

  return strText ;
}

inline void GetExepath ( TCHAR *pPath ) //��ȡִ��Ŀ¼
{
  TCHAR exePath[MAX_PATH];
  ::memset ( exePath, 0, sizeof ( TCHAR ) *MAX_PATH );
  ::GetModuleFileName ( NULL, exePath, MAX_PATH );
  TCHAR* pEnd = _tcsrchr ( exePath, _T ( '\\' ) );
  * ( pEnd + 1 ) = NULL;

  if ( pPath != NULL )
  {
    _tcscpy ( pPath, exePath );
  }
}


inline void DoEvents()
{
  MSG msg;

  if ( PeekMessage ( &msg, NULL, 0, 0, PM_NOREMOVE ) )
  {
    GetMessage ( &msg, NULL, 0, 0 );

    if ( msg.message == WM_QUIT )
    {
      return;
    }

    TranslateMessage ( &msg );
    DispatchMessage ( &msg );
  }
}

inline void Delay ( DWORD dwTime )
{
  if ( 0 == dwTime )
  {
    return;
  }

  long start = GetTickCount();

  while ( TRUE )
  {
    DoEvents();

    if ( ( GetTickCount() - start ) >= dwTime )
      break;
  }
}


inline CString GetBrowseFolder ( HWND pParent, CString wndTitle )
{
  char        szDir[MAX_PATH] = {0};
  BROWSEINFO    bi;
  ITEMIDLIST    *pidl = NULL;

  bi.hwndOwner = pParent;
  bi.pidlRoot = NULL;
  bi.pszDisplayName = szDir;
  bi.lpszTitle = wndTitle;
  bi.ulFlags = BIF_RETURNONLYFSDIRS;
  bi.lpfn = NULL;
  bi.lParam = 0;
  bi.iImage = 0;

  pidl = SHBrowseForFolder ( &bi );

  if ( NULL == pidl )
    return "";

  if ( !SHGetPathFromIDList ( pidl, szDir ) )
    return "";

  return CString ( szDir );
}
////////////////////////////////////////////////////////////////////////////////////
#endif
