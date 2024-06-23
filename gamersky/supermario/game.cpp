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


#include "sprite.h"
#include "plane.h"
#include "sound.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include "mytime.h"


CBitmap		g_bmTile;
CBitmap		g_bmPlayer;
CBitmap		g_bmGhost;
CBitmap		g_bmTurtle;
CBitmap		g_bmCoin;
CBitmap		g_bmMushroom;
CBitmap		g_bmDebris;
CBitmap		g_bmBullet;
CBitmap		g_bmExplode;
CBitmap		g_bmFlower;

CPlane		g_plane;
CPlayer		g_player;
CSpriteList	g_sprites;

CInput		g_input;

BOOL		g_bPaused;
BOOL		g_bShowStats;
int			g_level;
BOOL		g_darken;
CTime		g_lasttime;


void TRACE( char *format, ... );
void SetPalette( PALETTEENTRY ape[] );
void ClearBackground();
void OutputText( int x, int y, char *text );
void FlipScreen();

/*
 * LoadPalette
 *
 * Create a DirectDrawPalette from a palette file
 *
 * if the palette files cant be found, make a default 332 palette
 */
BOOL LoadPalette( char *fname, PALETTEENTRY ape[] )
{
	FILE *fp;
	
    struct  {
        DWORD           dwRiff;
        DWORD           dwFileSize;
        DWORD           dwPal;
        DWORD           dwData;
        DWORD           dwDataSize;
        WORD            palVersion;
        WORD            palNumEntries;
    }   header;

    header.dwRiff = 0;

    if( fname )
    {
        fp = fopen( fname, "rb" );

        if( fp )
            fread( &header, sizeof(header), 1, fp );
    }

    /*
     * if the file is not a palette file, or does not exist
     * default to a 332 palette
     */
    if (header.dwRiff != 0x46464952 || // 'RIFF'
        header.dwPal  != 0x204C4150 || // 'PAL '
        header.dwData != 0x61746164 || // 'data'
        header.palVersion != 0x0300 ||
        header.palNumEntries > 256  ||
        header.palNumEntries < 1)
    {
        TRACE( "Can't open palette file, using default 332." );

        for( int i = 0; i < 256; i++ )
        {
            ape[i].peRed   = (BYTE)(((i >> 5) & 0x07) * 255 / 7);
            ape[i].peGreen = (BYTE)(((i >> 2) & 0x07) * 255 / 7);
            ape[i].peBlue  = (BYTE)(((i >> 0) & 0x03) * 255 / 3);
            ape[i].peFlags = (BYTE)0;
        }
		return FALSE;
    }

	fread( ape, sizeof(PALETTEENTRY), 256, fp );
	fclose( fp );

	return TRUE;

} /* LoadPalette */



void PauseGame()
{
	g_bPaused = !g_bPaused;
	if( g_bPaused )
	{
#ifdef _WIN32
		PauseMidi();
#endif
	}
	else
	{
#ifdef _WIN32
		ResumeMidi();
#endif
		g_lasttime.GetTime();
	}
}




const float PLAYER_STARTX = 64;
const float PLAYER_STARTY = 383;


BOOL InitLevel( BOOL reinit )
{
	g_sprites.Destroy();
	
	// open map file
	char filename[64];
	sprintf( filename, "level/level%d.dat", g_level );
	FILE *fp = fopen( filename, "ra" );
	if( !fp )
	{
		g_level = 1;
		sprintf( filename, "level/level%d.dat", g_level );
		fp = fopen( filename, "ra" );
		if( !fp )
			return FALSE;
	}

	// see if the scene is darken
	fscanf( fp, "%d", &g_darken );

	// create plane
	g_plane.Create( fp, &g_bmTile );

	// read ghost data...
	int num, x, y, i;
	
	fscanf( fp, "%d", &num );		// ghost
	for( i = 0; i < num; i ++ )
	{
		fscanf( fp, "%d", &x );
		fscanf( fp, "%d", &y );
		AddGhost( (float)x, (float)y );
	}

	fscanf( fp, "%d", &num );		// walking turtle
	for( i = 0; i < num; i ++ )
	{
		fscanf( fp, "%d", &x );
		fscanf( fp, "%d", &y );
		AddTurtle( WALKTURTLE, (float)x, (float)y );
	}

	fscanf( fp, "%d", &num );		// flying turtle
	for( i = 0; i < num; i ++ )
	{
		fscanf( fp, "%d", &x );
		fscanf( fp, "%d", &y );
		AddTurtle( FLYTURTLE, (float)x, (float)y );
	}

	fclose( fp );

	
	// reset player
	if( reinit )
	{
		g_player.m_type = 0;		// child
		g_player.m_width = 32;
		g_player.m_height = 32;
		g_player.m_hasbullet = FALSE;
	}
	g_player.m_x = PLAYER_STARTX;
	g_player.m_y = PLAYER_STARTY;
	if( g_player.m_type == 1 )
		g_player.m_y -= 32;

	g_player.m_xv = g_player.m_yv = 0;
	g_player.m_xa = g_player.m_ya = 0;
	g_player.m_onground = TRUE;
	g_player.m_shield = FALSE;
	g_player.SetAction( STILL, RIGHT );

	// Set Palette
	PALETTEENTRY ape[256];
	if( !g_darken )
		LoadPalette( "bright.pal", ape );
	else
		LoadPalette( "darken.pal", ape );
	SetPalette( ape );

#ifdef _WIN32
	if( !g_darken )
		PlayMidi( "sound/back1.mid" );
	else
		PlayMidi( "sound/back2.mid" );
#endif
	return TRUE;
}



BOOL InitGame()
{
	g_input.Create();

	// init player
	g_player.Create( 0, PLAYER_STARTX, PLAYER_STARTY, 32, 32, 14, &g_bmPlayer );
	g_player.BitBlt( STILL, RIGHT );
	g_player.BitBlt( WALK, RIGHT );
	g_player.BitBlt( WALK, RIGHT );
	g_player.BitBlt( WALK, RIGHT );
	g_player.BitBlt( STOP, RIGHT );
	g_player.BitBlt( JUMP, RIGHT );
	g_player.BitBlt( DEAD, RIGHT );
	g_player.BitBlt( SLIDE, RIGHT );
	g_player.BitBlt( STILL, LEFT );
	g_player.BitBlt( WALK, LEFT );
	g_player.BitBlt( WALK, LEFT );
	g_player.BitBlt( WALK, LEFT );
	g_player.BitBlt( STOP, LEFT );
	g_player.BitBlt( JUMP, LEFT );

	return InitLevel( TRUE );
}


BOOL LoadBitmaps()
{
	g_bmTile.Load( "graphics/tile.bmp" );
	g_bmPlayer.Load( "graphics/player.bmp" );
	g_bmCoin.Load( "graphics/coin.bmp" );
	g_bmMushroom.Load( "graphics/mushroom.bmp" );
	g_bmDebris.Load( "graphics/debris.bmp" );
	g_bmGhost.Load( "graphics/ghost.bmp" );
	g_bmTurtle.Load( "graphics/turtle.bmp" );
	g_bmBullet.Load( "graphics/bullet.bmp" );
	g_bmExplode.Load( "graphics/explode.bmp" );
	g_bmFlower.Load( "graphics/flower.bmp" );

	return TRUE;
}


#ifdef _WIN32
void ReleaseBitmaps()
{
	g_bmTile.Release();
	g_bmPlayer.Release();
	g_bmCoin.Release();
	g_bmMushroom.Release();
	g_bmDebris.Release();
	g_bmGhost.Release();
	g_bmTurtle.Release();
	g_bmBullet.Release();
	g_bmExplode.Release();
	g_bmFlower.Release();
}

void RestoreBitmaps()
{
	g_bmTile.Restore( "graphics\\tile.bmp" );
	g_bmPlayer.Restore( "graphics\\player.bmp" );
	g_bmCoin.Restore( "graphics\\coin.bmp" );
	g_bmMushroom.Restore( "graphics\\mushroom.bmp" );
	g_bmDebris.Restore( "graphics\\debris.bmp" );
	g_bmGhost.Restore( "graphics\\ghost.bmp" );
	g_bmTurtle.Restore( "graphics\\turtle.bmp" );
	g_bmBullet.Restore( "graphics\\bullet.bmp" );
	g_bmExplode.Restore( "graphics\\explode.bmp" );
	g_bmFlower.Restore( "graphics\\flower.bmp" );
}
#endif



void ProcessInput( float time )
{
	BYTE input;
	g_input.GetKey( input );

	g_player.Move( time, input );


	CSprite *save;
	for( CSprite *sprite=g_sprites.m_head; sprite; sprite = save )
	{
		save = sprite->m_next;
		
		// see if ghost can now started?
		if( !sprite->m_active && sprite->m_x < g_player.m_x + 640 )
			sprite->m_active = TRUE;
		
		sprite->Move( time );
		if( sprite->m_active &&	
			(sprite->m_y + sprite->m_height < 0 ||
			sprite->m_y > 480 || sprite->m_x < 0 ||
			sprite->m_x < g_plane.m_x - 640 ||
			sprite->m_x > g_plane.m_x + 1280 ||
			sprite->m_x > g_plane.m_width*TILE_W) )
		{
			// if ghost is too faraway from us, delete it
			g_sprites.Delete( sprite );
		}
	}

	// see if player is dead
	if( g_player.m_action == DEAD && g_player.m_y > 480 )
		InitLevel( TRUE );

	// if we go through the level
	if( g_player.m_x > g_plane.m_width*TILE_W )
	{
		g_level ++;
		InitLevel( FALSE );
	}
}


void ShowFPS()
{
	static int frame;
	static float fps;
	static CTime lasttime;

	frame ++;
	CTime thistime;
	thistime.GetTime();
	float time = thistime - lasttime;
	if( time > 1 )
	{
		fps = frame / time;
		frame = 0;
		lasttime = thistime;
	}
	
	if( g_bShowStats )
	{
		char buf[255];
		sprintf( buf, "FPS: %.2f", fps );
		OutputText( 10, 10, buf );
	}
}


void UpdateFrame()
{
	CTime thistime;
	thistime.GetTime();
	float time = thistime - g_lasttime;
	g_lasttime = thistime;
	if( time > 0.05f )
		time = 0.05f;
	
	ProcessInput( time );
	
	ClearBackground();

	g_plane.Draw();

	int planex = g_plane.m_x;

	for( CSprite *sprite=g_sprites.m_head; sprite; sprite = sprite->m_next )
		sprite->Draw( planex );

	g_player.Draw( planex );

	ShowFPS();
	FlipScreen();
}
