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

#ifndef _PLANE_H
#define _PLANE_H


#include "bitmap.h"
#include <stdio.h>

#define TILE_W	32
#define TILE_H	32

enum{ COL_HORZ, COL_VERT };		// for collision detection
enum
{
	SURF_NONE = -1,
	SURF_SOLID,
	SURF_BRICK,
	SURF_COIN,
	SURF_MUSHROOM,
};

struct BOX
{
	float minx, miny;
	float maxx, maxy;
};

class CSprite;
struct COLLISION
{
	int tilex, tiley;
	char contents;
	int type;
	float frac;
	float sectx, secty;
	CSprite *sprite;
};


class CPlane
{
public:
	~CPlane();
	BOOL Create( FILE *fp, CBitmap *bm );
	void Draw();
	
	void SetSurface( int x, int y, char surf );
	void IncrementX( int delta );
	BOOL Collide( int width, int height, float startx, float starty, 
		float endx, float endy, COLLISION *col );

	int		m_x;
	int		m_width;
	int		m_height;
	char	*m_tiles;
	char	*m_surface;		// for collision detection
	
	CBitmap *m_pbmTile;
};


BOOL Intersect( float startx, float starty, float endx, float endy, BOX &box, COLLISION *col );


#endif
