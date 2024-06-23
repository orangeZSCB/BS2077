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

#include <stdio.h>
#include "plane.h"

void TRACE( char *format, ... );

CPlane::~CPlane()
{
	if( m_tiles )
		delete []m_tiles;
	if( m_surface )
		delete []m_surface;
}


BOOL CPlane::Create( FILE *fp, CBitmap *pbmTile )
{
	m_x = 0;
	m_pbmTile = pbmTile;
	fscanf( fp, "%d", &m_width );
	fscanf( fp, "%d", &m_height );
	int size = m_width * m_height;
	
	m_tiles = new char[size];
	char *p = m_tiles;
	int i, j, dummy;
	for( i = 0; i < m_height; i ++ )
		for( j = 0; j < m_width; j ++ )
		{
			fscanf( fp, "%d", &dummy );
			*p ++ = (char)dummy - 1;
		}

	m_surface = new char[size];
	p = m_surface;
	for( i = 0; i < m_height; i ++ )
		for( j = 0; j < m_width; j ++ )
		{
			fscanf( fp, "%d", &dummy );
			*p ++ = (char)dummy - 1;
		}

	return TRUE;
}



void CPlane::SetSurface( int x, int y, char surf )
{
	int i = y * m_width + x;
	m_surface[i] = surf;

	char tile;
	switch( surf )
	{
	case SURF_NONE:
		tile = -1;
		break;
	case SURF_SOLID:
		tile = 18;
		break;
	default:
		return;
	}

	m_tiles[i] = tile;
}


void CPlane::IncrementX( int delta )
{
	m_x += delta;
	if( m_x > m_width * TILE_W - 640 )
		m_x = m_width * TILE_W - 640;
}


BOOL CPlane::Collide( int width, int height, float startx, float starty, 
					  float endx, float endy, COLLISION *col )
{
	int x1, x2, y1, y2;
	if( endx > startx )
	{
		x1 = (int)startx / TILE_W;
		x2 = (int)(endx + width) / TILE_W;
	}
	else
	{
		x1 = (int)endx / TILE_W;
		x2 = (int)(startx + width) / TILE_W;
	}
	if( endy > starty )
	{
		y1 = (int)starty / TILE_H;
		y2 = (int)(endy + height) / TILE_H;
	}
	else
	{
		y1 = (int)endy / TILE_H;
		y2 = (int)(starty + height) / TILE_H;
	}

	col->frac = 2;

	for( int x = x1; x <= x2; x ++ )
	{
		for( int y = y1; y <= y2; y ++ )
		{
			if( x < 0 || x >= m_width ||
				y < 0 || y >= m_height )
				continue;

			char surf = m_surface[y*m_width+x];
			if( surf == SURF_NONE )
				continue;

			BOX box;
			box.minx = (float)(x * TILE_W);
			box.miny = (float)(y * TILE_H);
			box.maxx = box.minx + TILE_W;
			box.maxy = box.miny + TILE_H;
			box.minx -= width;
			box.miny -= height;
			
			if( Intersect( startx, starty, endx, endy, box, col ) )
			{
				col->contents = surf;
				col->tilex = x;
				col->tiley = y;
			}
		}
	}

	return (col->frac <= 1 ? TRUE : FALSE);
}




void CPlane::Draw()
{
	int min = m_x / TILE_W;
	int max = min + 20;
	int leftx = m_x - min * TILE_W;

	for( int i = 0; i < m_height; i ++ )
	{
		int x = 0;
		for( int j = min; j <= max; j ++ )
		{
			int n = i * m_width + j;
			if( m_tiles[n] >= 0 )
			{
				RECT rc;
				rc.left = (m_tiles[n] % 16) * TILE_W;
				rc.top = (m_tiles[n] / 16) * TILE_H;
				rc.right = rc.left + TILE_W;
				rc.bottom = rc.top + TILE_H;
				if( j == min )
					rc.left += leftx;
				else if( j == max )
					rc.right -= TILE_W - leftx;

				m_pbmTile->Draw( x, i*TILE_H, rc );
			}
			if( j == min )
				x += TILE_W - leftx;
			else
				x += TILE_W;
		}
	}
}



BOOL Intersect( float startx, float starty, float endx, float endy,
			    BOX &box, COLLISION *col )
{
	float minx = box.minx + 10;
	float miny = box.miny + 6;
	float maxx = box.maxx;
	float maxy = box.maxy;
	float frac, sectx, secty;
	BOOL ret = FALSE;

	startx += 5;
	endx += 5;
	starty += 3;
	endy += 3;
	
	if( startx != endx )
	{
		if( endx > startx )
			sectx = minx;
		else
			sectx = maxx;
		
		frac = (sectx - startx) / (endx - startx);
		
		if( frac >= 0 && frac <= 1 )
		{
			secty = starty + (endy - starty) * frac;
			if( secty >= miny && secty <= maxy &&
				frac < col->frac )
			{
				ret = TRUE;
				col->type = COL_VERT;
				col->frac = frac;
				if( endx > startx )
					sectx --;
				else
					sectx ++;
				col->sectx = sectx;
				col->secty = secty;
			}
		}
	}
	
	if( starty != endy )
	{
		if( endy > starty )
			secty = miny;
		else
			secty = maxy;
		
		frac = (secty - starty) / (endy - starty);
		
		if( frac >= 0 && frac <= 1 )
		{
			sectx = startx + (endx - startx) * frac;
			if( sectx >= minx && sectx <= maxx && 
				frac < col->frac )
			{
				ret = TRUE;
				col->type = COL_HORZ;
				col->frac = frac;
				if( endy > starty )
					secty --;
				else
					secty ++;
				col->sectx = sectx;
				col->secty = secty;
			}
		}
	}

	if( ret )
	{
		col->sectx -= 5;
		col->secty -= 3;
	}
	return ret;
}
