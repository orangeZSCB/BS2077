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

#ifndef _SPRITE_H
#define _SPRITE_H


#include "bitmap.h"
#include "mytime.h"

enum DIRECTION { SAME = -1, LEFT, RIGHT };
enum ACTION { NONE, STILL, WALK, CROUCH, JUMP, STOP, SLIDE, DEAD, UPSIDEDOWN };
enum{ GHOST, WALKTURTLE, FLYTURTLE, COIN, MUSHROOM, FLOWER, BULLET };

struct SPRITE_BM			// sprite bitmap
{
	ACTION		action;
	DIRECTION	dir;
};


struct BOX;
struct COLLISION;
class CSprite
{
public:
	~CSprite();
	void Create( int type, float x, float y, int w, int h, int nBitmaps, CBitmap *pbmSprite );
	
	void BitBlt( ACTION action, DIRECTION dir );
	void SetBitmap();
	void AdvanceBitmap();
	void CheckBottom();
	void ChangeDirection();
	void SetAction( ACTION action, DIRECTION dir = SAME );
	BOOL Collide( float startx, float starty, CSprite *sprite, COLLISION *col );

	virtual void GetBox( BOX &box );
	virtual void Move( float time );
	virtual void Draw( int planex );


	int		m_type;
	BOOL	m_active;		// just for ghost
	float	m_x;
	float	m_y;
	int		m_width;
	int		m_height;
	BOOL	m_onground;
	int		m_nBitmaps;
	int		m_count;
	int		m_curBitmap;
	SPRITE_BM *m_sbm;
	DIRECTION m_dir;
	ACTION	m_action;
	float	m_xv;
	float	m_yv;
	float	m_xa;
	float	m_ya;
	float	m_relSwitch;
	float	m_absSwitch;

	CBitmap *m_pbmSprite;

	CSprite *m_next;
};


class CSpriteList
{
public:
	CSpriteList(){ m_head = 0; }
	~CSpriteList(){ Destroy(); }
	
	void Add( CSprite *sprite );
	void Delete( CSprite *sprite );
	void Destroy();

	CSprite *m_head;
};



class CCoin : public CSprite
{
public:
	virtual void Move( float time );
};


class CBullet : public CSprite
{
public:
	virtual void Move( float time );
};

class CExplode : public CSprite
{
public:
	virtual void Move( float time );
};


class CMushroom : public CSprite
{
public:
	virtual void Move( float time );
};



class CPlayer : public CSprite
{
public:
	void GrowUp();
	void Shrink();
	void Shield();
	void BeenHit();
	void Fire();
	
	void Move( float time, BYTE input );
	virtual void Draw( int planex );


	int m_life;
	BOOL m_hasbullet;
	BOOL m_shield;
	BOOL m_show;
	CTime m_shieldTime;
};


class CGhost : public CSprite
{
public:
	virtual void GetBox( BOX &box );
	virtual void Move( float time );
};


class CWalkTurtle : public CGhost
{
public:
	virtual void Move( float time );
};


class CFlyTurtle : public CWalkTurtle
{
public:
	virtual void Move( float time );
	virtual void Draw( int planex );
};



void AddCoin( int tilex, int tiley );
void AddGhost( float x, float y );
void AddTurtle( int type, float x, float y );


#endif
