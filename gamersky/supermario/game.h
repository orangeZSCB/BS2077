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


#ifndef _GAME_H
#define _GAME_H

#include "input.h"
#include "mytime.h"

#define SCREEN_W			640
#define SCREEN_H			480


extern CInput g_input;
extern BOOL g_bShowStats;
extern BOOL g_bPaused;
extern CTime g_lasttime;
extern BOOL g_darken;

BOOL InitGame();
void PauseGame();
BOOL LoadBitmaps();
void ReleaseBitmaps();
void RestoreBitmaps();
BOOL LoadPalette( char *fname, PALETTEENTRY ape[] );
void UpdateFrame();


#endif
