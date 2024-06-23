//-----------------------------------------------------------------------------
//
// Copyright (C) July 24, 2000 by Zhang Yong
// Email: z-meng@yeah.net
// This source is available for distribution and/or modification
// only under the terms of the GPL license.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the GPL.txt for more details.
//
//-----------------------------------------------------------------------------

#include "../bitmap.h"


extern LPDIRECTDRAW			g_pDD;
extern LPDIRECTDRAWSURFACE	g_pddsBackBuffer;

void TRACE( char *format, ... );

#define COLORKEY	RGB(255,60,174)


LPDIRECTDRAWSURFACE DDCreateSurface( int width, int height )
{
	DDSURFACEDESC	ddsd;
	ZeroMemory( &ddsd, sizeof(ddsd) );
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwWidth = width;
	ddsd.dwHeight = height;

	LPDIRECTDRAWSURFACE pdds;
	if( FAILED(g_pDD->CreateSurface( &ddsd, &pdds, NULL )) )
		return NULL;

	return pdds;
}



HRESULT DDCopyBitmap( LPDIRECTDRAWSURFACE pdds, 
						HBITMAP hbm, int x, int y, 
						int dx, int dy)
{
    HDC                     hdcImage;
    HDC                     hdc;
    BITMAP                  bm;
    DDSURFACEDESC			ddsd;
    HRESULT                 hr;

    if (hbm == NULL || pdds == NULL)
        return E_FAIL;
    //
    // Make sure this surface is restored.
    //
    pdds->Restore();
    //
    // Select bitmap into a memoryDC so we can use it.
    //
    hdcImage = CreateCompatibleDC(NULL);
    if (!hdcImage)
        TRACE("createcompatible dc failed\n");
    SelectObject(hdcImage, hbm);
    //
    // Get size of the bitmap
    //
    GetObject(hbm, sizeof(bm), &bm);
    dx = dx == 0 ? bm.bmWidth : dx;     // Use the passed size, unless zero
    dy = dy == 0 ? bm.bmHeight : dy;
    //
    // Get size of surface.
    //
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
    pdds->GetSurfaceDesc(&ddsd);

    if ((hr = pdds->GetDC(&hdc)) == DD_OK)
    {
        StretchBlt(hdc, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, x, y,
                   dx, dy, SRCCOPY);
        pdds->ReleaseDC(hdc);
    }
    DeleteDC(hdcImage);
    return hr;
}



//-----------------------------------------------------------------------------
// Name: DDLoadBitmap()
// Desc: Create a DirectDrawSurface from a bitmap resource.
//-----------------------------------------------------------------------------
LPDIRECTDRAWSURFACE DDLoadBitmap( LPCSTR szBitmap, int dx, int dy)
{
    HBITMAP                 hbm;
    BITMAP                  bm;
    IDirectDrawSurface		*pdds;

    //
    //  Try to load the bitmap as a resource, if that fails, try it as a file
    //
    hbm = (HBITMAP) LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, dx,
                              dy, LR_CREATEDIBSECTION);
    if (hbm == NULL)
        hbm = (HBITMAP) LoadImage(NULL, szBitmap, IMAGE_BITMAP, dx, dy,
                                  LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if (hbm == NULL)
        return NULL;
    //
    // Get size of the bitmap
    //
    GetObject(hbm, sizeof(bm), &bm);
    //
    // Create a DirectDrawSurface for this bitmap
    //
    pdds = DDCreateSurface( bm.bmWidth, bm.bmHeight );
	if( !pdds )
        return NULL;
    DDCopyBitmap(pdds, hbm, 0, 0, 0, 0);
    DeleteObject(hbm);
    return pdds;
}




//-----------------------------------------------------------------------------
// Name: DDReLoadBitmap()
// Desc: Load a bitmap from a file or resource into a directdraw surface.
//       normaly used to re-load a surface after a restore.
//-----------------------------------------------------------------------------
HRESULT
DDReLoadBitmap(IDirectDrawSurface *pdds, LPCSTR szBitmap)
{
    HBITMAP                 hbm;
    HRESULT                 hr;

    //
    //  Try to load the bitmap as a resource, if that fails, try it as a file
    //
    hbm = (HBITMAP) LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, 0,
                              0, LR_CREATEDIBSECTION);
    if (hbm == NULL)
        hbm = (HBITMAP) LoadImage(NULL, szBitmap, IMAGE_BITMAP, 0, 0,
                                  LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if (hbm == NULL)
    {
        TRACE( "handle is null\n" );
        return E_FAIL;
    }
    hr = DDCopyBitmap(pdds, hbm, 0, 0, 0, 0);
    if (hr != DD_OK)
    {
        TRACE( "ddcopybitmap failed\n" );
    }
    DeleteObject(hbm);
    return hr;
}



//-----------------------------------------------------------------------------
// Name: DDColorMatch()
// Desc: Convert a RGB color to a pysical color.
//       We do this by leting GDI SetPixel() do the color matching
//       then we lock the memory and see what it got mapped to.
//-----------------------------------------------------------------------------
DWORD DDColorMatch(LPDIRECTDRAWSURFACE pdds, COLORREF rgb)
{
    COLORREF                rgbT;
    HDC                     hdc;
    DWORD                   dw = CLR_INVALID;
    DDSURFACEDESC			ddsd;
    HRESULT                 hres;

    //
    //  Use GDI SetPixel to color match for us
    //
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
        rgbT = GetPixel(hdc, 0, 0);     // Save current pixel value
        SetPixel(hdc, 0, 0, rgb);       // Set our value
        pdds->ReleaseDC(hdc);
    }
    //
    // Now lock the surface so we can read back the converted color
    //
    ddsd.dwSize = sizeof(ddsd);
    while ((hres = pdds->Lock(NULL, &ddsd, 0, NULL)) == DDERR_WASSTILLDRAWING)
        ;
    if (hres == DD_OK)
    {
        dw = *(DWORD *) ddsd.lpSurface;                 // Get DWORD
        if (ddsd.ddpfPixelFormat.dwRGBBitCount < 32)
            dw &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount) - 1;  // Mask it to bpp
        pdds->Unlock(NULL);
    }
    //
    //  Now put the color that was there back.
    //
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
        SetPixel(hdc, 0, 0, rgbT);
        pdds->ReleaseDC(hdc);
    }
    return dw;
}


//-----------------------------------------------------------------------------
// Name: DDSetColorKey()
// Desc: Set a color key for a surface, given a RGB.
//       If you pass CLR_INVALID as the color key, the pixel
//       in the upper-left corner will be used.
//-----------------------------------------------------------------------------
HRESULT DDSetColorKey(LPDIRECTDRAWSURFACE pdds, COLORREF rgb)
{
    if( !pdds )
		return E_FAIL;
	
	DDCOLORKEY              ddck;
    ddck.dwColorSpaceLowValue = DDColorMatch(pdds, rgb);
    ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;
	return pdds->SetColorKey(DDCKEY_SRCBLT, &ddck);
}




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBitmap::CBitmap()
{
	m_pdds = NULL;
}


void CBitmap::Release()
{
	if( m_pdds )
	{
		m_pdds->Release();
		m_pdds = NULL;
	}
}


BOOL CBitmap::Load( char *filename )
{
	m_pdds = DDLoadBitmap( filename, 0, 0 );
	if( m_pdds )
	{
		DDSetColorKey( m_pdds, COLORKEY );
		return TRUE;
	}
	return FALSE;
}



void CBitmap::Draw( int x, int y, RECT &rc )
{
	if( m_pdds )
	{
		g_pddsBackBuffer->BltFast( x, y, m_pdds, &rc,
			DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
	}
}


void CBitmap::Restore( char *filename )
{
	DDReLoadBitmap( m_pdds, filename );
	DDSetColorKey( m_pdds, COLORKEY );
}
