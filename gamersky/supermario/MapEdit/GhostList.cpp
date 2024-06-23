// List.cpp: implementation of the CGhostList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapEdit.h"
#include "GhostList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGhostList::CGhostList()
{
	m_head = NULL;
	m_len = 0;
}

CGhostList::~CGhostList()
{
	Destroy();
}


void CGhostList::Add( int x, int y )
{
	GHOST *ghost = new GHOST;
	ghost->x = x;
	ghost->y = y;

	ghost->next = m_head;
	m_head = ghost;

	m_len ++;
}


BOOL CGhostList::Delete( int x, int y )
{
	GHOST *prev = NULL;
	for( GHOST *ghost = m_head; ghost; ghost = ghost->next )
	{
		if( ghost->x == x && ghost->y == y )
		{
			if( prev )
				prev->next = ghost->next;
			else
				m_head = ghost->next;

			delete ghost;
			m_len --;
			return TRUE;
		}
		prev = ghost;
	}
	return FALSE;
}


void CGhostList::Destroy()
{
	while( m_head )
	{
		GHOST *save = m_head;
		m_head = m_head->next;
		delete save;
	}
	m_len = 0;
}


void CGhostList::Read( FILE *fp, int len )
{
	Destroy();

	for( int i = 0; i < len; i ++ )
	{
		int x, y;
		fscanf( fp, "%d", &x );
		fscanf( fp, "%d", &y );
		Add( x, y );
	}
	m_len = len;
}


void CGhostList::Write( FILE *fp )
{
	fprintf( fp, "%d\n", m_len );
	for( GHOST *ghost = m_head; ghost; ghost = ghost->next )
		fprintf( fp, "%d   %d\n", ghost->x, ghost->y );
}


void CGhostList::Draw( CDC *pDC, CBitmap *pbmGhost, int planex )
{
	CDC dcMem;
	dcMem.CreateCompatibleDC( pDC );
	CBitmap *pbmOld = (CBitmap *)dcMem.SelectObject( pbmGhost );

	for( GHOST *ghost = m_head; ghost; ghost = ghost->next )
	{
		int x = ghost->x - planex;
		int y = ghost->y;
		if( x + 32 > 0 && x < 640 )
		{
			BITMAP bm;
			pbmGhost->GetObject( sizeof(bm), &bm );
			int w = bm.bmWidth;
			int h = bm.bmHeight;
			pDC->BitBlt( x, y, w, h, &dcMem, 0, 0, SRCCOPY );
		}
	}

	dcMem.SelectObject( pbmOld );
}



void CGhostList::Refresh( int width )
{
	GHOST *save;
	GHOST *prev = NULL;
	for( GHOST *ghost = m_head; ghost; ghost = save )
	{
		save = ghost->next;
		
		if( ghost->x > width )
		{
			if( prev )
				prev->next = ghost->next;
			else
				m_head = ghost->next;
			delete ghost;
			m_len --;
		}
		prev = ghost;
	}
}