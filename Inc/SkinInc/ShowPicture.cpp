// ShowPicture.cpp: implementation of the CShowPicture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ShowPicture.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define FreeMyMemory(ptr) { \
		if(ptr) free(ptr);	\
		(ptr) = NULL;\
		}
CShowPicture::CShowPicture()
{
	PictureLoaded = FALSE;
	memset(&Picture, 0, sizeof(Pictures));
}

CShowPicture::~CShowPicture()
{
	RemovePictures();
}

//////////////////////////////////////////////////////////////////////
// 
void CShowPicture::AddPicture(HWND hWnd,int ResourceHandle,int PositionX,int PositionY)
{
	if(PictureLoaded)
		return;
	HRSRC res = FindResource(GetModuleHandle(NULL),MAKEINTRESOURCE(ResourceHandle),"BINARY");
	if (res) 
	{
		HGLOBAL mem = LoadResource(GetModuleHandle(NULL), res);
		void *data = LockResource(mem);
		size_t sz = SizeofResource(GetModuleHandle(NULL), res);
		/* Note: delete the memory , otherwise leak the memory */
		Picture.Picture = LoadPicture(hWnd, (unsigned char *)data, sz, &Picture.PictureWitdh, &Picture.PictureHeight);
		if (Picture.Picture != NULL)
		{
			Picture.PositionX=PositionX;
			Picture.PositionY=PositionY;
			Picture.hWnd=hWnd;
			PictureLoaded = TRUE;
		}
		else
		{
			FreeMyMemory(data);
		}
	}
}

void CShowPicture::AddPicture(HWND hWnd,unsigned char *data, unsigned int sz,int PositionX,int PositionY)
{
	if(PictureLoaded)
		return;
	Picture.Picture = LoadPicture(hWnd, (unsigned char *)data, sz, &Picture.PictureWitdh, &Picture.PictureHeight);
	if (Picture.Picture != NULL)
	{
		Picture.PositionX=PositionX;
		Picture.PositionY=PositionY;
		Picture.hWnd=hWnd;
		PictureLoaded = TRUE;
	}
	else
	{
		FreeMyMemory(data);
	}
}

void CShowPicture::AddPicture(HWND hWnd, char * FileName, int PositionX, int PositionY)
{
	if(PictureLoaded)
		return;
	
	FILE *fp = NULL;
	fp = fopen(FileName,"rb");
	if(NULL == fp)
	{
		PictureLoaded = FALSE;
		return;
	}
	
	struct stat file_stat;
	
	if(-1 == fstat(fileno(fp), &file_stat))
	{
		PictureLoaded = FALSE;
		fclose(fp);
		return;
	}
	
    unsigned char *f_buf = (unsigned char *)malloc(sizeof(unsigned char)*file_stat.st_size);
	
	if(NULL == f_buf)
	{
		PictureLoaded = FALSE;
		fclose(fp);
		return;
	}
	
	long file_size = fread(f_buf,1,file_stat.st_size,fp);
	fclose(fp);
	
	if(file_size != file_stat.st_size)
	{
		PictureLoaded = FALSE;
		FreeMyMemory(f_buf);
		return;
	}
	
	Picture.Picture = LoadPicture(hWnd, f_buf, file_size, &Picture.PictureWitdh, &Picture.PictureHeight);
	if (Picture.Picture != NULL)
	{
		Picture.PositionX=PositionX;
		Picture.PositionY=PositionY;
		Picture.hWnd=hWnd;
		PictureLoaded = TRUE;
	}
	else
	{
		FreeMyMemory(f_buf);
	}
}

IPicture *CShowPicture::LoadPicture(HWND hwnd, const unsigned char *data, size_t len,long *ret_w, long *ret_h)
{
	IPicture *pic = NULL;
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, len);
	LPVOID pvData = GlobalLock( hGlobal );
	memcpy(pvData,data,len);
	GlobalUnlock(hGlobal);
	LPSTREAM pStream = NULL;
	HRESULT hr = CreateStreamOnHGlobal( hGlobal, TRUE, &pStream );
	OleLoadPicture(pStream, 0, FALSE,IID_IPicture, (void **)&pic);
	pStream->Release();
	OLE_XSIZE_HIMETRIC cx;
	OLE_YSIZE_HIMETRIC cy;
	pic->get_Width(&cx);
	pic->get_Height(&cy);
	*ret_w = MAP_LOGHIM_TO_PIX(cx, GetDeviceCaps(GetDC(hwnd), LOGPIXELSX));
	*ret_h = MAP_LOGHIM_TO_PIX(cy, GetDeviceCaps(GetDC(hwnd), LOGPIXELSX));
	return pic;
}

void CShowPicture::RenderPicture(HDC dc, const RECT &bounds, void *pic)
{
	IPicture *picture = (IPicture *)pic;
	OLE_XSIZE_HIMETRIC cx;
	OLE_YSIZE_HIMETRIC cy;
	picture->get_Width(&cx);
	picture->get_Height(&cy);
	picture->Render(dc, bounds.left, bounds.bottom, bounds.right - bounds.left,
		bounds.top - bounds.bottom, 0, 0, cx, cy, NULL);
}

void CShowPicture::RepaintPictures()
{
	if(!PictureLoaded)
		return;
	RECT bounds;
	RECT temp_rect;
	::GetWindowRect(Picture.hWnd,&temp_rect);
	
	bounds.top = Picture.PositionY;;
	bounds.bottom = Picture.PositionY + Picture.PictureHeight;
	bounds.left = Picture.PositionX;
	bounds.right = Picture.PositionX + Picture.PictureWitdh;

	RenderPicture(GetDC(Picture.hWnd), bounds, Picture.Picture);
}

void CShowPicture::RemovePictures()
{
	if(!PictureLoaded)
		return;
	IPicture *freepic = (IPicture *)Picture.Picture;
	freepic->Release();
	memset(&Picture, 0, sizeof(Pictures));
	PictureLoaded = FALSE;
}

void CShowPicture::RepaintPicturesSize(CRect m_pRect)
{
	if(!PictureLoaded)
		return;
	RECT bounds;
	RECT temp_rect;
	::GetWindowRect(Picture.hWnd,&temp_rect);
	bounds.top = m_pRect.top;
	bounds.bottom =m_pRect.bottom;
	bounds.left =m_pRect.left;
	bounds.right =m_pRect.right;
	
	RenderPicture(GetDC(Picture.hWnd), bounds, Picture.Picture);
}
