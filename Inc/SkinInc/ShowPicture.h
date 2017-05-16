// ShowPicture.h: interface for the CShowPicture class.
//
//////////////////////////////////////////////////////////////////////
// Load picture module 
// version 1.0.0 (3/8/2011)
// This will help you with showing .GIF .JPG .BMP .WMF files
// Declare: the source come from the module by Goofy [FreeStylers],I only 
//			perfect it,upgrade it to this version
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_SHOWPICTURE_H__5214D8FA_CF1A_4311_8D6A_B9CAEFF415FD__INCLUDED_)
#define AFX_SHOWPICTURE_H__5214D8FA_CF1A_4311_8D6A_B9CAEFF415FD__INCLUDED_
#include "olestd.h"
#include <sys/stat.h>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
typedef struct PICTURES
{
	void *Picture;		// pointer to the picture
	long PictureWitdh;	// picture witdh (in pixels)
	long PictureHeight; // picture height (in pixels)
	int PositionX;		// the X coordinate of the picture on the Window
	int PositionY;		// the Y coordinate of the picture on the Window
	HWND hWnd;			// the handle of the window where the picture is printed on
} Pictures,*pPictures;

class CShowPicture  
{
public:
	void RepaintPicturesSize(CRect m_pRect);////指定图片的宽高位置
	void RepaintPictures();/////显示全图大小
	CShowPicture();
	virtual ~CShowPicture();

	void AddPicture(HWND hWnd, unsigned char * data, unsigned int sz, int PositionX, int PositionY);
	// Procedure: AddPicture
	//
	// HWND hWnd            = The handle of the window where you want to add a picture
	// unsigned char * data = The data of your picture 
	// unsigned int sz		= The sz is the size of picture
	// int PositionX        = The X coordinate on the window where the picture should popup :)
	// int PositionY        = The Y coordinate .....bleh
	void AddPicture(HWND hWnd, char * FileName, int PositionX, int PositionY);
	// Procedure: AddPicture
	//
	// HWND hWnd            = The handle of the window where you want to add a picture
	// char * FileName		= The FileName is all path of your picture file
	// int PositionX        = The X coordinate on the window where the picture should popup :)
	// int PositionY        = The Y coordinate .....bleh
	void AddPicture(HWND hWnd,int ResourceHandle,int PositionX,int PositionY);
	// Procedure: AddPicture
	//
	// HWND hWnd            = The handle of the window where you want to add a picture
	// int ResourceHandle   = The RecourceId (u can use the ALIAS u gave in .RC file) 
	//                        example: ID_BLAH
	// int PositionX        = The X coordinate on the window where the picture should popup :)
	// int PositionY        = The Y coordinate .....bleh
	IPicture *LoadPicture(HWND hwnd, const unsigned char *data, size_t len,long *ret_w, long *ret_h);
	
//private:
public:
	void RemovePictures();
	//
	void RenderPicture(HDC dc, const RECT &bounds, void *pic);
	//
	bool PictureLoaded;
	Pictures Picture;
};

#endif // !defined(AFX_SHOWPICTURE_H__5214D8FA_CF1A_4311_8D6A_B9CAEFF415FD__INCLUDED_)
