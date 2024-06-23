// MapEditDoc.cpp : implementation of the CMapEditDoc class
//

#include "stdafx.h"
#include "MapEdit.h"

#include "MapEditDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapEditDoc

IMPLEMENT_DYNCREATE(CMapEditDoc, CDocument)

BEGIN_MESSAGE_MAP(CMapEditDoc, CDocument)
	//{{AFX_MSG_MAP(CMapEditDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapEditDoc construction/destruction

CMapEditDoc::CMapEditDoc()
{
	m_width = 40;
	m_height = 15;
	m_darken = FALSE;
	m_tiles = NULL;
	m_surface = NULL;
}

CMapEditDoc::~CMapEditDoc()
{
	if( m_tiles )
		delete []m_tiles;
}

BOOL CMapEditDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_darken = FALSE;

	if( m_tiles )
		delete []m_tiles;
	if( m_surface )
		delete []m_surface;
	
	int size = m_width * m_height;
	m_tiles = new char[size];
	m_surface = new char[size];
	memset( m_tiles, -1, size );
	memset( m_surface, -1, size );

	for( int i = 0; i < 3; i ++ )
		m_ghostlist[i].Destroy();

	return TRUE;
}


void CMapEditDoc::Resize( int width )
{
	char *old;
	int i, j;
	
	// resize tiles array
	old = new char[m_width * m_height];
	memcpy( old, m_tiles, m_width * m_height );
	
	delete []m_tiles;
	m_tiles = new char[width*m_height];

	for( i = 0; i < m_height; i ++ )
		for( j = 0; j < width; j ++ )
		{
			if( j < m_width )
				m_tiles[i*width+j] = old[i*m_width+j];
			else
				m_tiles[i*width+j] = -1;
		}
	delete []old;


	// resize surface array
	old = new char[m_width * m_height];
	memcpy( old, m_surface, m_width * m_height );
	
	delete []m_surface;
	m_surface = new char[width*m_height];

	for( i = 0; i < m_height; i ++ )
		for( j = 0; j < width; j ++ )
		{
			if( j < m_width )
				m_surface[i*width+j] = old[i*m_width+j];
			else
				m_surface[i*width+j] = -1;
		}
	delete []old;

	m_width = width;

	// refresh ghostlist
	for( i = 0; i < 3; i ++ )
		m_ghostlist[i].Refresh( m_width * 32 );

	SetModifiedFlag();
}


/////////////////////////////////////////////////////////////////////////////
// CMapEditDoc serialization

void CMapEditDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMapEditDoc diagnostics

#ifdef _DEBUG
void CMapEditDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMapEditDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapEditDoc commands

BOOL CMapEditDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	FILE *fp = fopen( lpszPathName, "wa" );
	if( !fp )
		return FALSE;

	m_darken = m_darken ? 1 : 0;
	fprintf( fp, "%d\n\n", m_darken );

	fprintf( fp, "%d\n", m_width );
	fprintf( fp, "%d\n\n", m_height );

	int k;
	
	// write tile data
	k = 0;
	for( int i = 0; i < m_height; i ++ )
	{
		for( int j = 0; j < m_width; j ++ )
		{
			fprintf( fp, "%-4d", (int)(m_tiles[k++] + 1) );
		}
		fprintf( fp, "\n" );
	}
	fprintf( fp, "\n\n" );
	
	// write surface data
	k = 0;
	for( i = 0; i < m_height; i ++ )
	{
		for( int j = 0; j < m_width; j ++ )
		{
			fprintf( fp, "%-4d", (int)(m_surface[k++] + 1) );
		}
		fprintf( fp, "\n" );
	}
	fprintf( fp, "\n" );


	// write ghosts data
	for( i = 0; i < 3; i ++ )
	{
		m_ghostlist[i].Write( fp );
		fprintf( fp, "\n" );
	}
	
	fclose( fp );
	SetModifiedFlag( FALSE );
	return TRUE;

//	return CDocument::OnSaveDocument(lpszPathName);
}

BOOL CMapEditDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
//	if (!CDocument::OnOpenDocument(lpszPathName))
//		return FALSE;

	FILE *fp = fopen( lpszPathName, "ra" );
	if( !fp )
		return FALSE;
	
	fscanf( fp, "%d", &m_darken );
	
	fscanf( fp, "%d", &m_width );
	fscanf( fp, "%d", &m_height );
	
	int len = m_width * m_height;
	int i, dummy;
	
	// resize array
	delete []m_tiles;
	delete []m_surface;
	m_tiles = new char[len];
	m_surface = new char[len];

	// read tile data
	for( i = 0; i < len; i ++ )
	{
		fscanf( fp, "%d", &dummy );
		m_tiles[i] = (char)dummy - 1;
	}

	// read surface data
	for( i = 0; i < len; i ++ )
	{
		fscanf( fp, "%d", &dummy );
		m_surface[i] = (char)dummy - 1;
	}

	// read ghost data
	for( i = 0; i < 3; i ++ )
	{
		int len;
		fscanf( fp, "%d", &len );
		m_ghostlist[i].Read( fp, len );
	}

	fclose( fp );
	SetModifiedFlag( FALSE );

	return TRUE;
}
