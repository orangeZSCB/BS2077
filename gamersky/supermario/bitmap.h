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

#ifndef _BITMAP_H
#define _BITMAP_H

#ifdef _WIN32
#include <ddraw.h>
#else
#include "type.h"
#endif


class CBitmap
{
public:
	CBitmap();
	~CBitmap(){ Release(); }

	void Release();
	void Restore( char *filename );
	BOOL Load( char *filename );
	void SetColorKey();
	void Draw( int x, int y, RECT &rc );
	
private:

#ifdef _WIN32
	LPDIRECTDRAWSURFACE m_pdds;
#else
	int	m_width, m_height;
	BYTE *m_bits;
#endif
};


#endif
