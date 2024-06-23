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


#include "../game.h"
#include <sys/time.h>
#include <vgagl.h>
#include <vga.h>
#include <vgakeyboard.h>
#include <stdio.h>


GraphicsContext *g_frontbuffer;
GraphicsContext *g_backbuffer;

void TRACE( char *format, ... )
{
	
}

float GetTime()
{
	struct timeval time;
	gettimeofday( &time, NULL );
	return (time.tv_sec + (float)time.tv_usec/1e6);
}

void SetPalette( PALETTEENTRY ape[] )
{
	for( int i = 0; i < 256; i ++ )
	{
		int r = ape[i].peRed >> 2;
		int g = ape[i].peGreen >> 2;
		int b = ape[i].peBlue >> 2;
		gl_setpalettecolor( i, r, g, b );
	}
}


void FlipScreen()
{
	gl_copyscreen( g_frontbuffer );
}


void ClearBackground()
{
	gl_clearscreen( 16 );
}


void OutputText( int x, int y, char *text )
{
	gl_printf( 0, 0, text );
}


int main()
{
	g_bShowStats = TRUE;

	printf( "Initialize graphics...\n" );
	vga_init();
	
	printf( "Setting Display Mode 640x480x8...\n" );
	int mode = G640x480x256;
	vga_setmode( mode );
	gl_setcontextvga( mode );

	g_frontbuffer  = gl_allocatecontext();
	gl_getcontext( g_frontbuffer );
	gl_setcontextvgavirtual( mode );
	g_backbuffer = gl_allocatecontext();
	gl_getcontext( g_backbuffer );
	gl_setcontext( g_backbuffer );

	printf( "Init Font...\n" );
	gl_setfont( 8, 8, gl_font8x8 );
	gl_setwritemode( FONT_COMPRESSED | WRITEMODE_OVERWRITE |
					WRITEMODE_MASKED );
	gl_setfontcolors( 0, 255 );

	if( !LoadBitmaps() ||
		!InitGame() )
	{
		printf( "InitGame() error\n" );
		return 1;
	}
	
	g_lasttime.GetTime();
	
	// game loop
	while( TRUE )
	{
		if( keyboard_keypressed(SCANCODE_BREAK) )
			PauseGame();
		else if( keyboard_keypressed(SCANCODE_ESCAPE) )
			break;
		
		if( !g_bPaused )
			UpdateFrame();
	}

	gl_clearscreen(0);
	vga_setmode(0);
	return 0;
}
