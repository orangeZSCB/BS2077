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
#include "input.h"

extern CPlane g_plane;
extern CPlayer g_player;
extern CSpriteList g_sprites;
extern CBitmap g_bmGhost;
extern CBitmap g_bmTurtle;
extern CBitmap g_bmCoin;
extern CBitmap g_bmMushroom;
extern CBitmap g_bmDebris;
extern CBitmap g_bmBullet;
extern CBitmap g_bmExplode;
extern CBitmap g_bmFlower;

const float GRAVITY = 1200;

inline float fabs(float x){ return (x > 0 ? x : -x); }


void AddCoin( int tilex, int tiley )
{
	CSprite *sprite = new CCoin;
	float x = (float)(tilex * TILE_W + 8);
	float y = (float)(tiley * TILE_H - 20);

	sprite->Create( COIN, x, y, 16, 32, 3, &g_bmCoin );
	sprite->BitBlt( NONE, RIGHT );
	sprite->BitBlt( NONE, RIGHT );
	sprite->BitBlt( NONE, RIGHT );
	sprite->SetAction( NONE, RIGHT );
	sprite->m_ya = GRAVITY;
	sprite->m_yv = -500;
	g_sprites.Add( sprite );
}


void AddGhost( float x, float y )
{
	CSprite *sprite = new CGhost;
	sprite->Create( GHOST, x, y, 32, 32, 6, &g_bmGhost );
	sprite->BitBlt( WALK, RIGHT );
	sprite->BitBlt( WALK, RIGHT );
	sprite->BitBlt( WALK, LEFT );
	sprite->BitBlt( WALK, LEFT );
	sprite->BitBlt( DEAD, RIGHT );
	sprite->BitBlt( UPSIDEDOWN, RIGHT );
	sprite->SetAction( WALK, LEFT );
	sprite->m_xv = -75;
	sprite->m_active = FALSE;
	g_sprites.Add( sprite );
}


void AddTurtle( int type, float x, float y )
{
	CSprite *sprite;
	if( type == WALKTURTLE )
		sprite = new CWalkTurtle;
	else
		sprite = new CFlyTurtle;
	sprite->Create( type, x, y, 32, 48, 6, &g_bmTurtle );
	sprite->BitBlt( WALK, RIGHT );
	sprite->BitBlt( WALK, RIGHT );
	sprite->BitBlt( WALK, LEFT );
	sprite->BitBlt( WALK, LEFT );
	sprite->BitBlt( DEAD, RIGHT );
	sprite->BitBlt( UPSIDEDOWN, RIGHT );
	sprite->SetAction( WALK, LEFT );
	sprite->m_active = FALSE;
	if( type == WALKTURTLE )
		sprite->m_xv = -80;
	else
	{
		sprite->m_onground = FALSE;
		sprite->m_xv = -50;
		sprite->m_ya = GRAVITY/2;
	}
	g_sprites.Add( sprite );
}


void AddMushroom( int tilex, int tiley )
{
	CSprite *sprite = new CMushroom;
	float x = (float)(tilex * TILE_W);
	float y = (float)(tiley * TILE_H - 33);

	sprite->Create( MUSHROOM, x, y, 32, 32, 1, &g_bmMushroom );
	sprite->BitBlt( NONE, RIGHT );
	sprite->SetAction( NONE, RIGHT );
	sprite->m_ya = GRAVITY;
	sprite->m_yv = -100;
	sprite->m_xv = 85;
	g_sprites.Add( sprite );
}


void AddFlower( int tilex, int tiley )
{
	CSprite *sprite = new CSprite;
	float x = (float)(tilex * TILE_W);
	float y = (float)(tiley * TILE_H - 33);

	sprite->Create( FLOWER, x, y, 32, 32, 1, &g_bmFlower );
	sprite->BitBlt( NONE, RIGHT );
	sprite->SetAction( NONE, RIGHT );
	g_sprites.Add( sprite );
}


void AddDebris( int tilex, int tiley )
{
	CSprite *sprite[4];
	float x = (float)(tilex * TILE_W + 16);
	float y = (float)(tiley * TILE_H + 16);
	for( int i = 0; i < 4; i ++ )
	{
		sprite[i] = new CSprite;
		sprite[i]->Create( COIN, x, y, 16, 16, 4, &g_bmDebris );
		sprite[i]->BitBlt( NONE, RIGHT );
		sprite[i]->BitBlt( NONE, RIGHT );
		sprite[i]->BitBlt( NONE, RIGHT );
		sprite[i]->BitBlt( NONE, RIGHT );
		sprite[i]->SetAction( NONE, RIGHT );
		sprite[i]->m_ya = GRAVITY;
		g_sprites.Add( sprite[i] );
	}

	float xv = 100;
	sprite[0]->m_xv = -xv;
	sprite[0]->m_yv = -500;
	sprite[1]->m_xv = xv;
	sprite[1]->m_yv = -500;
	sprite[2]->m_xv = -xv;
	sprite[2]->m_yv = -200;
	sprite[3]->m_xv = xv;
	sprite[3]->m_yv = -200;
}


void AddExplode( float x, float y )
{
	CSprite *sprite = new CExplode;
	sprite->Create( COIN, x, y, 32, 32, 3, &g_bmExplode );
	sprite->BitBlt( NONE, RIGHT );
	sprite->BitBlt( NONE, RIGHT );
	sprite->BitBlt( NONE, RIGHT );
	sprite->SetAction( NONE, RIGHT );

	g_sprites.Add( sprite );
}


CSprite::~CSprite()
{
	if( m_sbm )
		delete []m_sbm;
}


void CSprite::Create( int type, float x, float y, int width, int height,
					  int nBitmaps, CBitmap *pbmSprite )
{
	m_type = type;
	m_active = TRUE;
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_onground = TRUE;
	
	m_xv = 0;
	m_yv = 0;
	m_xa = 0;
	m_ya = 0;
	
	m_count = 0;
	m_nBitmaps = nBitmaps;
	m_curBitmap = 0;
	m_relSwitch = 0;
	m_absSwitch = 10;

	m_sbm = new SPRITE_BM[nBitmaps];
	m_pbmSprite = pbmSprite;
	m_next = NULL;
}


void CSprite::BitBlt( ACTION action, DIRECTION dir )
{
	m_sbm[m_count].action = action;
	m_sbm[m_count].dir = dir;
	m_count ++;
}


void CSprite::SetBitmap()
{
	int c = 0;
	while( m_sbm[c].action != m_action ||
		   m_sbm[c].dir != m_dir )
		c ++;
	m_curBitmap = c;
}

void CSprite::ChangeDirection()
{
	if( m_dir == LEFT )
		m_dir = RIGHT;
	else
		m_dir = LEFT;
	
	SetBitmap();
}


void CSprite::SetAction( ACTION action, DIRECTION dir )
{
	m_action = action;
	if( dir != SAME )
		m_dir = dir;
	SetBitmap();
}


void CSprite::AdvanceBitmap()
{
	int c = m_curBitmap + 1;
	if( c >= m_nBitmaps )
		SetBitmap();
	else
	{
		if( m_sbm[c].action != m_action ||
			m_sbm[c].dir != m_dir )
			SetBitmap();
		else
			m_curBitmap = c;
	}
}


void CSprite::GetBox( BOX &box )
{
	box.minx = m_x;
	box.miny = m_y;
	box.maxx = box.minx + m_width;
	box.maxy = m_y + m_height;
}


BOOL CSprite::Collide( float startx, float starty, CSprite *sprite, COLLISION *col )
{
	BOX box;
	sprite->GetBox( box );
	box.minx -= m_width;
	box.miny -= m_height;

	return Intersect( startx, starty, m_x, m_y, box, col );
}


void CSprite::Move( float time )
{
	m_xv += m_xa * time;
	m_yv += m_ya * time;
	
	m_x += m_xv * time;
	m_y += m_yv * time;

	if( m_xv )
		m_relSwitch += fabs(m_xv) * time;
	else
		m_relSwitch += fabs(m_yv) * time;
	
	if( m_relSwitch >= m_absSwitch )
	{
		m_relSwitch = 0;
		AdvanceBitmap();
	}
}


void CSprite::CheckBottom()
{
	if( m_onground )
	{
		COLLISION col;
		if( !g_plane.Collide( m_width, m_height, m_x, m_y, m_x, m_y+2, &col ) )
		{
			m_onground = FALSE;
			m_ya = GRAVITY;
			m_xa = 0;
		}
	}
}


void CSprite::Draw( int planex )
{
	int x = (int)m_x - planex;
	int y = (int)m_y;

	if( x + m_width < 0 || x > 640 ||
		y + m_height < 0 || y > 480 )
		return;

	RECT rc;
	rc.left = m_curBitmap * m_width;
	rc.top = 0;
	rc.right = rc.left + m_width;
	rc.bottom = rc.top + m_height;
	if( x < 0 )
	{
		rc.left += -x;
		x = 0;
	}
	else if( x + m_width > 640 )
		rc.right -= x + m_width - 640;
	if( y < 0 )
	{
		rc.top += -y;
		y = 0;
	}
	else if( y + m_height > 480 )
		rc.bottom -= y + m_height - 480;

	m_pbmSprite->Draw( x, y, rc );
}




void CSpriteList::Add( CSprite *sprite )
{
	sprite->m_next = m_head;
	m_head = sprite;
}


void CSpriteList::Delete( CSprite *sprite )
{
	CSprite *prev = NULL;
	for( CSprite *p = m_head; p; p = p->m_next )
	{
		if( p == sprite )
		{
			CSprite *save = p;
			if( prev )
				prev->m_next = p->m_next;
			else
				m_head = p->m_next;
			delete save;
			break;
		}
		prev = p;
	}
}


void CSpriteList::Destroy()
{
	while( m_head )
	{
		CSprite *save = m_head->m_next;
		delete m_head;
		m_head = save;
	}
}



void CCoin::Move( float time )
{
	CSprite::Move( time );
	
	if( m_yv > 0 )
		g_sprites.Delete( this );
}


void CBullet::Move( float time )
{
	float startx = m_x;
	float starty = m_y;
	CSprite::Move( time );

	COLLISION col;
	g_plane.Collide(m_width, m_height, startx, starty, m_x, m_y, &col);
	col.sprite = NULL;
	for( CSprite *sprite=g_sprites.m_head; sprite; sprite = sprite->m_next )
	{
		if( sprite->m_action == UPSIDEDOWN )
			continue;
		
		if( sprite->m_type == GHOST && sprite->m_action != DEAD ||
			sprite->m_type == WALKTURTLE ||
			sprite->m_type == FLYTURTLE )
		{
			if( Collide(startx, starty, sprite, &col) )
				col.sprite = sprite;
		}
	}

	if( col.frac <= 1 )
	{
		m_x = col.sectx;
		m_y = col.secty;
		
		if( !col.sprite )
		{
			if( col.type == COL_HORZ )	// bullet hit ground
				m_yv = -m_yv;			// bounce it like a ball
			else						// bullet hit brick
			{
				AddExplode( col.sectx, col.secty );
				g_sprites.Delete( this );
				return;
			}
		}
		else		// bullet hit ghost
		{
			if( m_action != DEAD )
			{
				col.sprite->SetAction( UPSIDEDOWN, RIGHT );
				col.sprite->m_ya = GRAVITY;
				col.sprite->m_yv = -200;
				col.sprite->m_xv = -col.sprite->m_xv;
			}
			AddExplode( col.sectx, col.secty );
			g_sprites.Delete( this );
			return;
		}
	}
}


void CExplode::Move( float time )
{
	AdvanceBitmap();

	if( m_curBitmap == 0 )
		g_sprites.Delete( this );
}


void CMushroom::Move( float time )
{
	float startx = m_x;
	float starty = m_y;
	CSprite::Move( time );

	COLLISION col;
	g_plane.Collide(m_width, m_height, startx, starty, m_x, m_y, &col);
	col.sprite = NULL;
	if( Collide( startx, starty, &g_player, &col ) )
		col.sprite = &g_player;

	if( col.frac <= 1 )
	{
		if( !col.sprite )
		{
			m_x = col.sectx;
			m_y = col.secty;
			
			if( col.type == COL_HORZ )
			{
				m_onground = TRUE;
				m_ya = 0;
				m_yv = 0;
			}
			else
				m_xv = -m_xv;
		}
		else
		{
			g_player.GrowUp();
			g_sprites.Delete( this );
			return;
		}
	}

	CheckBottom();
}



void CPlayer::Shield()
{
	m_shield = TRUE;
	m_show = FALSE;
	m_shieldTime.GetTime();
}


void CPlayer::GrowUp()
{
	if( m_type == 0 )
	{
		m_type = 1;
		m_y -= 32;
		m_height = 64;
		m_shield = FALSE;
	}
}


void CPlayer::Shrink()
{
	m_type = 0;
	m_y += 32;
	m_height = 32;
	m_hasbullet = FALSE;

	Shield();
}


void CPlayer::BeenHit()
{
	if( m_type == 1 )
		Shrink();
	else
	{
		SetAction( DEAD, RIGHT );
		m_yv = -500;
		m_ya = GRAVITY;
		m_xv = 0;
		m_xa = 0;
		m_y -= 10;
		
		m_life --;
	}
}


void CPlayer::Fire()
{
	int count = 0;
	for( CSprite *sprite=g_sprites.m_head; sprite; sprite = sprite->m_next )
	{
		if( sprite->m_type == BULLET )
			count ++;
	}
	if( count >= 2 )		// we can fire 2 bullets at a time
		return;

	
	float x, y, xv, yv;
	y = m_y + 10;
	yv = 200;
	if( m_dir == RIGHT )
	{
		x = m_x + m_width;
		xv = 500;
	}
	else
	{
		x = m_x - 16;
		xv = -500;
	}

	CSprite *bullet = new CBullet;
	bullet->Create( BULLET, x, y, 16, 16, 4, &g_bmBullet );
	bullet->BitBlt( NONE, RIGHT );
	bullet->BitBlt( NONE, RIGHT );
	bullet->BitBlt( NONE, RIGHT );
	bullet->BitBlt( NONE, RIGHT );
	bullet->SetAction( NONE, RIGHT );
	bullet->m_xv = xv;
	bullet->m_yv = yv;
	bullet->m_ya = GRAVITY;
	g_sprites.Add( bullet );
}



void CPlayer::Draw( int planex )
{
	int x = (int)m_x - planex;
	int y = (int)m_y;
	RECT rc;
	rc.left = (m_curBitmap % 8) * m_width;
	rc.top = (m_curBitmap / 8) * m_height;
	if( m_type == 1 )
		rc.top += 64;
	rc.right = rc.left + m_width;
	rc.bottom = rc.top + m_height;
	if( x < 0 )
	{
		rc.left += -x;
		x = 0;
	}
	else if( x + m_width > 640 )
		rc.right -= x + m_width - 640;
	if( y < 0 )
	{
		rc.top += -y;
		y = 0;
	}
	else if( y + m_height > 480 )
		rc.bottom -= y + m_height - 480;

	if( !m_shield || m_show )
		m_pbmSprite->Draw( x, y, rc );

	if( m_shield )
	{
		m_show = !m_show;
		CTime time;
		time.GetTime();
		if( time - m_shieldTime > 3 )
			m_shield = FALSE;
	}
}



void CPlayer::Move( float time, BYTE input )
{
	static BYTE lastinput;

	if( m_action == DEAD )
	{
		CSprite::Move( time );
		return;
	}

	// update position
	float startx = m_x;
	float starty = m_y;
	float xv = m_xv;
	float maxspeed;
	
	if( (input & KEY_ACC) && m_onground )
		maxspeed = 400;
	else
		maxspeed = 250;

	m_xv += m_xa * time;
	m_yv += m_ya * time;
	if( m_xv > maxspeed )
		m_xv = maxspeed;
	else if( m_xv < -maxspeed )
		m_xv = -maxspeed;
	
	m_x += m_xv * time;
	m_y += m_yv * time;
	if( m_x < g_plane.m_x )
		m_x = (float)g_plane.m_x;

	if( xv > 0 && m_xv < 0 ||
		xv < 0 && m_xv > 0 )
	{
		if( m_onground )
		{
			m_xv = 0;
			m_xa = 0;
			SetAction( STILL );
		}
	}

	// animate
	if( m_xv )
		m_relSwitch += fabs(m_xv) * time;
	else
		m_relSwitch += fabs(m_yv) * time;
	
	if( m_relSwitch >= m_absSwitch )
	{
		m_relSwitch = 0;
		AdvanceBitmap();
	}


	// process user input

	if( input & KEY_RIGHT )
	{
		if( m_dir == LEFT )
		{
			if( m_onground )
			{
				ChangeDirection();
				if( m_action != STILL && m_xv < 0 )
				{
					m_xa = 1000;
					SetAction( STOP );
				}
			}
			else
				m_xa = 500;
		}
		else if( !m_onground || m_action == STILL )
		{
			m_xa = 500;
			if( m_action == STILL )
				SetAction( WALK );
		}
	}
	
	else if( input & KEY_LEFT )
	{
		if( m_dir == RIGHT )
		{
			if( m_onground )
			{
				ChangeDirection();
				if( m_action != STILL && m_xv > 0 )
				{
					m_xa = -1000;
					SetAction( STOP );
				}
			}
			else
				m_xa = -500;
		}
		else if( !m_onground || m_action == STILL )
		{
			m_xa = -500;
			if( m_action == STILL )
				SetAction( WALK );
		}
	}
	
	if( m_onground &&				// jump
		(input & KEY_JUMP) && !(lastinput & KEY_JUMP) )
	{
		m_onground = FALSE;
		SetAction( JUMP );
		if( input & KEY_ACC )
			m_yv = -650;
		else
			m_yv = -600;
		m_ya = GRAVITY;
		m_xa = 0;
	}

	if( m_hasbullet && (input & KEY_ACC) && !(lastinput & KEY_ACC) )
		Fire();

	
	if( m_onground &&		// friction
		!(input & KEY_RIGHT) && !(input & KEY_LEFT) )
	{
		if( m_xv > 0 )
			m_xa = -500;
		else if( m_xv < 0 )
			m_xa = 500;
	}

	if( m_action == JUMP && m_yv < 0 &&
		!(input & KEY_JUMP) && (lastinput & KEY_JUMP) )
	{
		m_ya += 1250;
	}



	// collision detection
	
	COLLISION col;
	g_plane.Collide(m_width, m_height, startx, starty, m_x, m_y, &col);
	col.sprite = NULL;
	
	for( CSprite *sprite=g_sprites.m_head; sprite; 
				sprite = sprite->m_next )
	{
		if( sprite->m_action == UPSIDEDOWN )
			continue;
		
		BOOL b = FALSE;
		if( sprite->m_type == GHOST && sprite->m_action != DEAD ||
			sprite->m_type == WALKTURTLE ||
			sprite->m_type == FLYTURTLE ||
			sprite->m_type == MUSHROOM ||
			sprite->m_type == FLOWER )
			b = TRUE;
		
		if( b && Collide(startx, starty, sprite, &col) )
			col.sprite = sprite;
	}

	if( col.frac <= 1 )
	{
		m_x = col.sectx;
		m_y = col.secty;

		if( !col.sprite )		// player hit something(eg. bricks)
		{
			if( col.type == COL_VERT )
			{
				m_xv = 0;
				m_xa = 0;
				if( m_action != JUMP )
					SetAction( STILL );
			}
			else
			{
				if( m_yv > 0 )
				{
					m_onground = TRUE;
					m_yv = 0;
					m_ya = 0;
					if( m_xv == 0 )
						SetAction( STILL );
					else
						SetAction( WALK );
				}
				else
				{
					m_yv = -m_yv/3;
					m_xv /= 2;
					if( col.contents == SURF_BRICK )
					{
						if( m_type == 1 )
						{
							AddDebris( col.tilex, col.tiley );
							g_plane.SetSurface( col.tilex, col.tiley, SURF_NONE );
						}
					}
					else if( col.contents == SURF_COIN ||
							 col.contents == SURF_MUSHROOM )
					{
						g_plane.SetSurface( col.tilex, col.tiley, SURF_SOLID );
						switch( col.contents )
						{
						case SURF_COIN:
							AddCoin( col.tilex, col.tiley );
							break;
						case SURF_MUSHROOM:
							if( m_type == 0 )
								AddMushroom( col.tilex, col.tiley );
							else
								AddFlower( col.tilex, col.tiley );
							break;
						}
					}
				}
			}
		}

		else
		{
			if( col.sprite->m_type == MUSHROOM )
			{
				g_sprites.Delete( col.sprite );
				GrowUp();
			}
			else if( col.sprite->m_type == FLOWER )
			{
				g_sprites.Delete( col.sprite );
				if( m_type == 1 )
					m_hasbullet = TRUE;		// we've got bullet!
				else
					GrowUp();		// just take it as a mushroom
			}
			else if( col.sprite->m_action != DEAD )
			{
				if( m_yv > 0 )
				{
					if( !col.sprite->m_onground )
					{
						col.sprite->m_yv = 150;
						col.sprite->m_ya = GRAVITY;
					}
					m_yv = -150;
					if( col.sprite->m_type == FLYTURTLE )
						col.sprite->m_type = WALKTURTLE;
					else
					{
						col.sprite->SetAction( DEAD, RIGHT );
						col.sprite->m_xv = 0;
					}
				}
				else if( !m_shield )
					BeenHit();
			}
			else	// the dead turtle
			{
				if( col.sprite->m_xv )		// moving
				{
					if( col.type == COL_VERT )
						BeenHit();
					else		// stop it
					{
						col.sprite->m_xv = 0;
						m_yv = -150;		// bounce us up
					}
				}
				else		// kick it off
				{
					if( col.type == COL_HORZ )
						m_y += 3;		// to avoid some odd things happening
					float playerx = m_x + m_width/2;
					float ghostx = col.sprite->m_x + col.sprite->m_width/2;
					if( playerx <= ghostx )
						col.sprite->m_xv = 500;
					else
						col.sprite->m_xv = -500;
				}
			}
		}
	}

	CheckBottom();

	// scroll screen
	int screenx = (int)m_x - g_plane.m_x;
	if( screenx > 288 )
		g_plane.IncrementX( screenx - 288 );

	// see if we fall into channel
	if( g_player.m_y > 480 )
	{
		m_type = 0;
		g_player.BeenHit();
	}

	lastinput = input;
}


void CGhost::GetBox( BOX &box )
{
	CSprite::GetBox( box );
	if( m_type == WALKTURTLE || m_type == FLYTURTLE )
		box.miny += 16;
}


void CGhost::Move( float time )
{
	if( !m_active )
		return;
	
	float startx = m_x;
	float starty = m_y;
	CSprite::Move( time );

	if( m_action == UPSIDEDOWN )
		return;

	COLLISION col;
	g_plane.Collide(m_width, m_height, startx, starty, m_x, m_y, &col);
	col.sprite = NULL;
	
	for( CSprite *sprite=g_sprites.m_head; sprite; 
			sprite = sprite->m_next )
	{
		if( sprite->m_action == UPSIDEDOWN )
			continue;
		
		if( sprite->m_type == GHOST && sprite->m_action != DEAD ||
			sprite->m_type == WALKTURTLE ||
			sprite->m_type == FLYTURTLE )
		{
			if( Collide(startx, starty, sprite, &col) )
				col.sprite = sprite;
		}
	}
		
	if( (g_player.m_action != DEAD) && (!g_player.m_shield) )
	{
		if( Collide(startx, starty, &g_player, &col) )
			col.sprite = &g_player;
	}

	if( col.frac <= 1 )
	{
		m_x = col.sectx;
		m_y = col.secty;
		
		if( col.sprite == &g_player )
		{
			if( col.type == COL_VERT || m_y >= 0 )
				g_player.BeenHit();
		}
		else if( !col.sprite && col.type == COL_HORZ )
		{
			if( m_yv >= 0 )
				m_onground = TRUE;
			m_ya = 0;
			m_yv = 0;
		}
		else
		{
			ChangeDirection();
			m_xv = -m_xv;
		}
	}

	CheckBottom();
}



void CWalkTurtle::Move( float time )
{
	if( !m_active )
		return;	

	if( m_action != DEAD )
	{
		CGhost::Move( time );
		return;
	}

	float startx = m_x;
	float starty = m_y;
	CSprite::Move( time );

	if( m_action == UPSIDEDOWN )
		return;

	COLLISION col;
	g_plane.Collide(m_width, 32, startx, starty+16, m_x, m_y+16, &col);
	col.sprite = NULL;
	
	for( CSprite *sprite=g_sprites.m_head; sprite; 
				sprite = sprite->m_next )
	{
		if( sprite->m_action == UPSIDEDOWN )
			continue;
		
		if( sprite->m_type == GHOST && sprite->m_type != DEAD ||
			sprite->m_type == WALKTURTLE ||
			sprite->m_type == FLYTURTLE )
		{
			if( Collide(startx, starty, sprite, &col) )
				col.sprite = sprite;
		}
	}
	
	if( (g_player.m_action != DEAD) && (!g_player.m_shield) )
	{
		if( Collide(startx, starty, &g_player, &col) )
			col.sprite = &g_player;
	}

	
	if( col.frac <= 1 )
	{
		m_x = col.sectx;
		m_y = col.secty - 16;
		
		if( col.sprite )
		{
			if( col.sprite == &g_player )
				g_player.BeenHit();
			else		// hit other ghost
			{
				col.sprite->SetAction( DEAD, RIGHT );
				col.sprite->SetAction( UPSIDEDOWN, RIGHT );
				col.sprite->m_ya = GRAVITY;
				col.sprite->m_yv = -200;
				col.sprite->m_xv = -col.sprite->m_xv;
			}
		}
		else
		{
			if( col.type == COL_HORZ )
			{
				m_onground = TRUE;
				m_ya = 0;
				m_yv = 0;
			}
			else
				m_xv = -m_xv;
		}
	}

	CheckBottom();
}




void CFlyTurtle::Move( float time )
{
	if( !m_active )
		return;	
	
	if( m_type == WALKTURTLE )
	{
		CWalkTurtle::Move( time );
		return;
	}

	if( m_type == FLYTURTLE )		// I believe I can fly
	{
		if( m_onground )
		{
			m_yv = -350;
			m_ya = GRAVITY/2;
			m_onground = FALSE;
		}
	}

	CGhost::Move( time );
}



void CFlyTurtle::Draw( int planex )
{
	int x = (int)m_x - planex;
	int y = (int)m_y;

	if( x + m_width < 0 || x > 640 ||
		y + m_height < 0 || y > 480 )
		return;

	RECT rc;
	rc.left = m_curBitmap * m_width;
	if( m_type == WALKTURTLE )
		rc.top = 0;
	else
		rc.top = 48;
	rc.right = rc.left + m_width;
	rc.bottom = rc.top + m_height;
	if( x < 0 )
	{
		rc.left += -x;
		x = 0;
	}
	else if( x + m_width > 640 )
		rc.right -= x + m_width - 640;
	if( y < 0 )
	{
		rc.top += -y;
		y = 0;
	}
	else if( y + m_height > 480 )
		rc.bottom -= y + m_height - 480;

	m_pbmSprite->Draw( x, y, rc );
}
