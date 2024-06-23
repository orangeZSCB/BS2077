// MapEditView.cpp : implementation of the CMapEditView class
//

#include "stdafx.h"
#include "MapEdit.h"

#include "MapEditDoc.h"
#include "MapEditView.h"
#include "MapWidthDlg.h"
#include "ObjectTypeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum
{ 
	BRICK1, BRICK2, BRICK3, GRASS, CLOUD, HILL, MARK, TUBE, BUILDING,
	GHOST1, GHOST2, GHOST3,
};

enum
{
	SURF_NONE = -1,
	SURF_SOLID,
	SURF_BRICK,
	SURF_COIN,
	SURF_MUSHROOM,
};

const int TILE_W = 32;
const int TILE_H = 32;


CSize GetSize( UINT object )
{
	int w, h;

	switch( object )
	{
	case BRICK1:
	case BRICK2:
	case BRICK3:
	case MARK:
		w = 1;
		h = 1;
		break;

	case GRASS:
		w = 3;
		h = 1;
		break;

	case CLOUD:
	case HILL:
		w = 3;
		h = 2;
		break;

	case TUBE:
		w = 2;
		h = 2;
		break;

	case GHOST1:
		w = h = 1;
		break;

	case GHOST2:
	case GHOST3:
		w = 1;
		h = 2;
		break;

	case BUILDING:
		w = h = 5;
		break;
	}
	
	return CSize(w * TILE_W, h * TILE_H );
}


/////////////////////////////////////////////////////////////////////////////
// CMapEditView

IMPLEMENT_DYNCREATE(CMapEditView, CScrollView)

BEGIN_MESSAGE_MAP(CMapEditView, CScrollView)
	//{{AFX_MSG_MAP(CMapEditView)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_EDIT_MAPWIDTH, OnEditMapwidth)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE( ID_BRICK1, ID_GHOST3, OnSelectObject )
	ON_UPDATE_COMMAND_UI_RANGE( ID_BRICK1, ID_GHOST3, OnUpdateObject )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapEditView construction/destruction

CMapEditView::CMapEditView()
{
	m_object = BRICK1;
	m_tilex = 0;
	m_tiley = 0;

	m_bmTiles.LoadBitmap( IDB_TILES );
	m_bmGhosts[0].LoadBitmap( IDB_GHOST1 );
	m_bmGhosts[1].LoadBitmap( IDB_GHOST2 );
	m_bmGhosts[2].LoadBitmap( IDB_GHOST3 );
}

CMapEditView::~CMapEditView()
{

}

BOOL CMapEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMapEditView drawing

void CMapEditView::OnDraw(CDC* pDC)
{
	CMapEditDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDC dcMem;
	CBitmap bitmap, *pbmOld;
	dcMem.CreateCompatibleDC( pDC );
	bitmap.CreateCompatibleBitmap( pDC, 640, 480 );
	pbmOld = (CBitmap *)dcMem.SelectObject( &bitmap );
	dcMem.FillSolidRect( 0, 0, 640, 480, RGB(107,136,255) );
	
	int planex = GetScrollPosition().x;
	
	// draw tiles
	CDC dcTiles;
	dcTiles.CreateCompatibleDC( pDC );
	CBitmap *pbmOld1 = (CBitmap *)dcTiles.SelectObject( &m_bmTiles );
	int min = planex / TILE_W;
	int max = min + 20;
	int leftx = planex - min * TILE_W;
	int width = pDoc->m_width;
	int height = pDoc->m_height;
	char *tiles = pDoc->m_tiles;
	
	for( int i = 0; i < height; i ++ )
	{
		int destx = 0;
		for( int j = min; j <= max; j ++ )
		{
			int tile = tiles[i * width + j];
			if( tile >= 0 )
			{
				int desty = i * TILE_H;
				int srcx = (tile % 16) * TILE_W;
				int srcy = (tile / 16) * TILE_H;
				int w = TILE_W;
				int h = TILE_H;
				if( j == min )
					srcx += leftx;
				else if( j == max )
					w = leftx;
				
				dcMem.BitBlt( destx, desty, w, h, &dcTiles, srcx, srcy, SRCCOPY );
			}
			if( j == min )
				destx += TILE_W - leftx;
			else
				destx += TILE_W;
		}
	}
	dcTiles.SelectObject( pbmOld1 );
	dcTiles.DeleteDC();
	
	// draw ghosts
	for( i = 0; i < 3; i ++ )
		pDoc->m_ghostlist[i].Draw( &dcMem, &m_bmGhosts[i], planex );


	// draw focus rect
	CBrush *pbrOld = (CBrush *)dcMem.SelectStockObject( NULL_BRUSH );
	RECT rc;
	CSize size = GetSize( m_object );
	rc.left = m_tilex * TILE_W - planex;
	rc.right = rc.left + size.cx;
	rc.top = m_tiley * TILE_H;
	rc.bottom = rc.top + size.cy;
	dcMem.Rectangle( &rc );

	pDC->BitBlt( planex, 0, 640, 480, &dcMem, 0, 0, SRCCOPY );
	dcMem.SelectObject( pbmOld );
	dcMem.SelectObject( pbrOld );
}


void CMapEditView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	sizeTotal.cx = GetDocument()->m_width * TILE_W;
	sizeTotal.cy = GetDocument()->m_height * TILE_H;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CMapEditView diagnostics

#ifdef _DEBUG
void CMapEditView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMapEditView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMapEditDoc* CMapEditView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapEditDoc)));
	return (CMapEditDoc*)m_pDocument;
}
#endif //_DEBUG


char CMapEditView::GetTile( int x, int y )
{
	int width = GetDocument()->m_width;
	int height = GetDocument()->m_height;
	if( x >= 0 && x < width &&
		y >= 0 && y < height )
	{
		return GetDocument()->m_tiles[y*width+x];
	}
	return -1;
}

void CMapEditView::SetTile( int x, int y, char tile )
{
	int width = GetDocument()->m_width;
	int height = GetDocument()->m_height;
	if( x >= 0 && x < width &&
		y >= 0 && y < height )
	{
		GetDocument()->m_tiles[y*width+x] = tile;
		GetDocument()->SetModifiedFlag();
	}
}


char CMapEditView::GetSurface( int x, int y )
{
	int width = GetDocument()->m_width;
	int height = GetDocument()->m_height;
	if( x >= 0 && x < width &&
		y >= 0 && y < height )
	{
		return GetDocument()->m_surface[y*width+x];
	}
	return -1;
}


void CMapEditView::SetSurface( int x, int y, char surf )
{
	int width = GetDocument()->m_width;
	int height = GetDocument()->m_height;
	if( x >= 0 && x < width &&
		y >= 0 && y < height )
	{
		GetDocument()->m_surface[y*width+x] = surf;
		GetDocument()->SetModifiedFlag();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMapEditView message handlers

void CMapEditView::OnSelectObject( UINT nID )
{
	m_object = nID - ID_BRICK1;
}

void CMapEditView::OnUpdateObject( CCmdUI *pCmdUI )
{
	pCmdUI->SetCheck( pCmdUI->m_nID - ID_BRICK1 == m_object );
}

void CMapEditView::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC( &dc );
	dc.DPtoLP( &point );

	int tilex = point.x / TILE_W;
	int tiley = point.y / TILE_H;
	if( tilex != m_tilex || tiley != m_tiley )
	{
		m_tilex = tilex;
		m_tiley = tiley;
		Invalidate( FALSE );
	}
	
	CScrollView::OnMouseMove(nFlags, point);
}


void CMapEditView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	int x = m_tilex * TILE_W;
	int y = m_tiley * TILE_H;
	if( m_object == GHOST2 || m_object == GHOST3 )
		y += 16;
	if( m_object == GHOST1 ||
		m_object == GHOST2 ||
		m_object == GHOST3 )
	{
		int i = m_object - GHOST1;
		GetDocument()->m_ghostlist[i].Delete( x, y );
	}
	else
	{
		if( GetSurface( m_tilex, m_tiley ) == SURF_BRICK &&
			GetTile( m_tilex, m_tiley+1 ) == 20 )
			SetTile( m_tilex, m_tiley+1, 0 );

		SetTile( m_tilex, m_tiley, -1 );
		SetSurface( m_tilex, m_tiley, SURF_NONE );
	}

	Invalidate( FALSE );
	
	CScrollView::OnRButtonDown(nFlags, point);
}

void CMapEditView::OnEditMapwidth() 
{
	CMapWidthDlg dlg;
	int &width = GetDocument()->m_width;
	int &height = GetDocument()->m_height;
	BOOL &darken = GetDocument()->m_darken;
	dlg.m_width = width;
	dlg.m_bDarken = darken;
	
	if( dlg.DoModal() == IDOK )
	{
		if( dlg.m_width < width &&
			AfxMessageBox(IDS_WARNING, MB_YESNO) == IDNO )
			return;
		
		if( dlg.m_width != width )
		{
			GetDocument()->Resize( dlg.m_width );
			CSize sizeTotal;
			sizeTotal.cx = width * TILE_W;
			sizeTotal.cy = height * TILE_H;
			SetScrollSizes(MM_TEXT, sizeTotal);
		}
		darken = dlg.m_bDarken;
		GetDocument()->SetModifiedFlag();
	}
}


void CMapEditView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if( nFlags & MK_CONTROL )
	{
		Property();
		return;
	}
	

	int &x = m_tilex;
	int &y = m_tiley;

	switch( m_object )
	{
	case BRICK1:
		if( GetSurface( x, y - 1 ) != SURF_BRICK )
			SetTile( x, y, 0 );
		else
			SetTile( x, y, 20 );

		if( GetTile( x, y + 1 ) == 0 )
			SetTile( x, y + 1, 20 );

		SetSurface( x, y, SURF_BRICK );
		break;

	case BRICK2:
		SetTile( x, y, 1 );
		SetSurface( x, y, SURF_SOLID );
		break;

	case BRICK3:
		SetTile( x, y, 19 );
		SetSurface( x, y, SURF_SOLID );
		break;

	case GRASS:
		SetTile( x, y, 2 );
		SetTile( x + 1, y, 3 );
		SetTile( x + 2, y, 4 );
		break;

	case CLOUD:
		SetTile( x + 1, y, 8 );
		SetTile( x, y + 1, 5 );
		SetTile( x + 1, y + 1, 6 );
		SetTile( x + 2, y + 1, 7 );
		break;

	case HILL:
		SetTile( x + 1, y, 12 );
		SetTile( x, y + 1, 9 );
		SetTile( x + 1, y + 1, 10 );
		SetTile( x + 2, y + 1, 11 );
		break;

	case MARK:		// question mark
		SetTile( x, y, 13 );
		SetSurface( x, y, SURF_COIN );
		break;

	case TUBE:
		SetTile( x, y, 16 );
		SetTile( x + 1, y, 17 );
		SetTile( x, y + 1, 14 );
		SetTile( x + 1, y + 1, 15 );
		
		SetSurface( x, y, SURF_SOLID );
		SetSurface( x + 1, y, SURF_SOLID );
		SetSurface( x, y + 1, SURF_SOLID );
		SetSurface( x + 1, y + 1, SURF_SOLID );
		break;

	case GHOST1:
	case GHOST2:
	case GHOST3:
		{
			int i = m_object - GHOST1;
			int spritex = x * TILE_W;
			int spritey = y * TILE_H;
			if( m_object == GHOST2 || m_object == GHOST3 )
				spritey += 16;
			
			GetDocument()->m_ghostlist[i].Add( spritex, spritey );
			GetDocument()->SetModifiedFlag();
		}
		break;

	case BUILDING:
		SetTile( x + 1, y, 26 );
		SetTile( x + 2, y, 26 );
		SetTile( x + 3, y, 26 );
		SetTile( x + 1, y + 1, 24 );
		SetTile( x + 2, y + 1, 20 );
		SetTile( x + 3, y + 1, 25 );
		SetTile( x, y + 2, 26 );
		SetTile( x + 1, y + 2, 23 );
		SetTile( x + 2, y + 2, 23 );
		SetTile( x + 3, y + 2, 23 );
		SetTile( x + 4, y + 2, 26 );
		SetTile( x, y + 3, 20 );
		SetTile( x + 1, y + 3, 20 );
		SetTile( x + 2, y + 3, 22 );
		SetTile( x + 3, y + 3, 20 );
		SetTile( x + 4, y + 3, 20 );
		SetTile( x, y + 4, 20 );
		SetTile( x + 1, y + 4, 20);
		SetTile( x + 2, y + 4, 21 );
		SetTile( x + 3, y + 4, 20 );
		SetTile( x + 4, y + 4, 20 );
		break;
	}
	Invalidate( FALSE );
	
	CScrollView::OnLButtonDown(nFlags, point);
}



void CMapEditView::Property() 
{
	char tile = GetTile( m_tilex, m_tiley );
	char surf = GetSurface( m_tilex, m_tiley );

	if( tile == 13 )		// question mark
	{
		CObjectTypeDlg dlg;
		dlg.m_nObjectType = GetSurface( m_tilex, m_tiley ) - SURF_COIN;
		if( dlg.DoModal() == IDOK )
		{
			if( dlg.m_bHidden )
				SetTile( m_tilex, m_tiley, -1 );
			SetSurface( m_tilex, m_tiley, dlg.m_nObjectType + SURF_COIN );
		}
	}
	else if( surf == SURF_BRICK )
	{
		CObjectTypeDlg dlg;
		if( surf == SURF_NONE )
			dlg.m_nObjectType = -1;
		else
			dlg.m_nObjectType = surf - SURF_COIN;
		if( dlg.DoModal() == IDOK )
		{
			int object = dlg.m_nObjectType;
			if( object == -1 )
				SetSurface( m_tilex, m_tiley, SURF_NONE );
			else
				SetSurface( m_tilex, m_tiley, object + SURF_COIN );
		}
	}
}
