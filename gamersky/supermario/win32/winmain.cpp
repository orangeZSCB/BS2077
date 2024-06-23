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

#include "resource.h"
#include "..\sound.h"
#include "..\input.h"
#include "..\game.h"
#include "..\mytime.h"
#include <ddraw.h>
#include <stdio.h>


LPDIRECTDRAW		g_pDD;
LPDIRECTDRAWPALETTE	g_pddPalette;
LPDIRECTDRAWSURFACE	g_pddsFrontBuffer;
LPDIRECTDRAWSURFACE	g_pddsBackBuffer;


HINSTANCE	g_hInst;
HWND		g_hWnd;
BOOL		g_bActive;

BOOL		g_bFullScreen;
RECT		g_rcWindow;
DWORD		g_dwFillColor;


#define SAFE_RELEASE(x)		if(x){ x->Release(); x = NULL; }
LPDIRECTDRAWSURFACE DDCreateSurface( int width, int height );
DWORD DDColorMatch(LPDIRECTDRAWSURFACE pdds, COLORREF rgb);
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );


void __cdecl TRACE( char *format, ... )
{
#ifdef _DEBUG
	char    buf[128];
    va_list vl;

    va_start(vl, format);
    sprintf(buf, format, vl);
    OutputDebugString( buf );
	va_end(vl);
#endif
}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


void DDTerm()
{
	ReleaseBitmaps();
	
	if( g_bFullScreen )
		SAFE_RELEASE( g_pddPalette );
	if( !g_bFullScreen )
		SAFE_RELEASE( g_pddsBackBuffer );
	SAFE_RELEASE( g_pddsFrontBuffer );
	SAFE_RELEASE( g_pDD );
}


BOOL DDInit()
{
	HRESULT hr;

	hr = DirectDrawCreate( NULL, &g_pDD, NULL );
	if( FAILED(hr) )
	{
		TRACE( "Error Create DirectDraw\n" );
		return FALSE;
	}

	if( g_bFullScreen )
		g_pDD->SetCooperativeLevel( g_hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
	else
		g_pDD->SetCooperativeLevel( g_hWnd, DDSCL_NORMAL );

	if( g_bFullScreen )
	{
		if( FAILED(g_pDD->SetDisplayMode( SCREEN_W, SCREEN_H, 8 )) )
		{
			TRACE( "Error SetDiaplayMode\n" );
			return FALSE;
		}
	}

	DDSURFACEDESC	ddsd;
	ZeroMemory( &ddsd, sizeof(ddsd) );
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	if( g_bFullScreen )
	{
		ddsd.dwFlags |= DDSD_BACKBUFFERCOUNT;
		ddsd.ddsCaps.dwCaps |= DDSCAPS_FLIP | DDSCAPS_COMPLEX;
		ddsd.dwBackBufferCount = 1;
	}
	hr = g_pDD->CreateSurface( &ddsd, &g_pddsFrontBuffer, NULL );
	if( FAILED(hr) )
	{
		TRACE( "Error Create Front Buffer\n" );
		return FALSE;
	}

	if( g_bFullScreen )
	{
		DDSCAPS ddscaps;
		ZeroMemory( &ddscaps, sizeof(ddscaps) );
		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
		g_pddsFrontBuffer->GetAttachedSurface( &ddscaps, &g_pddsBackBuffer );
	}
	else
		g_pddsBackBuffer = DDCreateSurface( SCREEN_W, SCREEN_H );

	if( g_bFullScreen )
	{
		PALETTEENTRY ape[256];
		LoadPalette( "bright.pal", ape );
		
		hr = g_pDD->CreatePalette( DDPCAPS_8BIT, ape, &g_pddPalette, NULL );
		if( FAILED(hr) )
		{
			TRACE( "Error Create Palette\n" );
			return FALSE;
		}
		g_pddsFrontBuffer->SetPalette( g_pddPalette );
	}
	
	g_dwFillColor = DDColorMatch( g_pddsFrontBuffer, RGB(107,136,255) );

	LoadBitmaps();


	if( !g_bFullScreen )
	{
		SetWindowPos( g_hWnd, 0, 0, 0, 646, 505, SWP_NOMOVE | SWP_NOZORDER );
		g_rcWindow.right = g_rcWindow.left + 640;
		g_rcWindow.bottom = g_rcWindow.top + 480;
	}

	return TRUE;
}



void SetPalette( PALETTEENTRY ape[] )
{
	if( g_bFullScreen )
		g_pddPalette->SetEntries( 0, 0, 256, ape );
}



BOOL InitApplication()
{
	char szClassName[] = "MARIO";
	char szTitle[] = "DX SuperMario";

	WNDCLASS wc;
	wc.hInstance = g_hInst;
	wc.lpszClassName = szClassName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_DBLCLKS;
	wc.hIcon = LoadIcon( g_hInst, MAKEINTRESOURCE(IDI_MARIO) );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );

	if( !RegisterClass( &wc ) )
	{
		TRACE( "Error In RegisterClassEx\n" );
		return FALSE;
	}

	g_hWnd = CreateWindow( szClassName,
				szTitle,
				WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				646, 505,
				NULL,
				NULL,
				g_hInst,
				NULL );
	if( !g_hWnd )
	{
		TRACE( "Error In CreateWindow\n" );
		return FALSE;
	}

	UpdateWindow( g_hWnd );
	ShowWindow( g_hWnd, SW_NORMAL );

	return TRUE;
}



BOOL Initialize()
{
	if( !InitApplication() || 
		!DDInit() ||
		!InitGame() )
	{
		DDTerm();
		return FALSE;
	}
	return TRUE;
}


void RestoreSurfaces()
{
	g_pddsBackBuffer->Restore();
	g_pddsFrontBuffer->Restore();
	RestoreBitmaps();
}



void FlipScreen()
{
	HRESULT hr;
	
	if( g_bFullScreen )
		hr = g_pddsFrontBuffer->Flip( NULL, DDFLIP_WAIT );
	else
	{
		hr = g_pddsFrontBuffer->Blt( &g_rcWindow, g_pddsBackBuffer,
				NULL, DDBLT_WAIT, NULL );
	}

	if( hr == DDERR_SURFACELOST )
	{
		RestoreSurfaces();
		g_pddsFrontBuffer->SetPalette( g_pddPalette );
	}
}



void OutputText( int x, int y, char *text )
{
	HDC hdc;
	if( g_pddsBackBuffer && 
		g_pddsBackBuffer->GetDC(&hdc) == DD_OK )
	{
		SetBkMode( hdc, TRANSPARENT );
		SetTextColor( hdc, RGB(255,255,0) );
		TextOut( hdc, x, y, text, lstrlen(text) );
		g_pddsBackBuffer->ReleaseDC( hdc );
	}
}



void ClearBackground()
{
	DDBLTFX	ddbfx;
	ZeroMemory( &ddbfx, sizeof(ddbfx) );
	ddbfx.dwSize = sizeof(ddbfx);
	ddbfx.dwFillColor = g_dwFillColor;
	
	g_pddsBackBuffer->Blt( NULL, NULL, NULL, 
		DDBLT_COLORFILL | DDBLT_WAIT, &ddbfx );
}



void OnKeyDown( WPARAM wKey )
{
	switch( wKey )
	{
	case VK_ESCAPE:
		SendMessage( g_hWnd, WM_CLOSE, 0, 0 );
		break;		
		
	case VK_F4:
		DDTerm();
		g_bFullScreen = !g_bFullScreen;
		DDInit();
		if( g_bFullScreen )
		{
			PALETTEENTRY ape[256];
			if( !g_darken )
				LoadPalette( "bright.pal", ape );
			else
				LoadPalette( "darken.pal", ape );
			SetPalette( ape );
		}
		g_lasttime.GetTime();
		break;

	case VK_F5:
		g_bShowStats = !g_bShowStats;
		break;

	case VK_PAUSE:
		PauseGame();
		break;
	}
}



LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
	case WM_ACTIVATEAPP:
		g_bActive = (BOOL)wParam;
		
		g_input.SetAcquire( g_bActive );
		
		g_bPaused = g_bActive;
		PauseGame();
		break;

	case WM_SETCURSOR:
		if( g_bFullScreen )
		{
			SetCursor( NULL );
			return TRUE;
		}
		break;

	case WM_DESTROY:
		StopMidi();
		PostQuitMessage(0);
		break;

	case WM_CLOSE:
		DestroyWindow( hWnd );
		break;

	case WM_MOVE:
		g_bActive = TRUE;
		GetClientRect( hWnd, &g_rcWindow );
		ClientToScreen( hWnd, (LPPOINT)&g_rcWindow );
		ClientToScreen( hWnd, (LPPOINT)&g_rcWindow + 1 );
		break;
		
	case WM_MOVING:
		g_bActive = FALSE;
		break;

	case WM_KEYDOWN:
		OnKeyDown( wParam );
		break;

	case MM_MCINOTIFY:		// @FIXME: I don't know why this message can never been received.
		if (wParam == MCI_NOTIFY_SUCCESSFUL)
			ReplayMidi();
        break;
	}

	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}



int GameLoop()
{	
	MSG	msg;

    g_lasttime.GetTime();
	while( TRUE )
    {
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            if ( msg.message == WM_QUIT )
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else if( g_bActive && !g_bPaused )
        {
			UpdateFrame();
        }
        else
            WaitMessage();
    }
	
	DDTerm();
	return msg.wParam;
}


			

//////////////////////////////////////////////////////////
//														//
//		Main entry point for win32 application			//
//														//
//////////////////////////////////////////////////////////

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR lpCmdLine,
				   int nCmdShow )
{
	g_hInst = hInst;

#ifdef _DEBUG
	g_bShowStats = TRUE;
	g_bFullScreen = FALSE;
#else
	g_bShowStats = FALSE;
	g_bFullScreen = TRUE;
#endif

	if( !Initialize() )
		return 0;
	
	return GameLoop();
}