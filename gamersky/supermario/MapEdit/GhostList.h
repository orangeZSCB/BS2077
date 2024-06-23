// List.h: interface for the CGhostList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIST_H__74432861_6160_11D4_9BDF_AA6D41E8ED13__INCLUDED_)
#define AFX_LIST_H__74432861_6160_11D4_9BDF_AA6D41E8ED13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct GHOST
{
	int x, y;
	GHOST *next;
};


class CGhostList  
{
public:
	CGhostList();
	~CGhostList();
	
	void Add( int x, int y );
	BOOL Delete( int x, int y );
	void Destroy();

	void Read( FILE *fp, int len );
	void Write( FILE *fp );
	void Draw( CDC *pDC, CBitmap *pbmGhost, int planex );
	void Refresh( int width );

private:
	GHOST *m_head;
	int m_len;
};


#endif // !defined(AFX_LIST_H__74432861_6160_11D4_9BDF_AA6D41E8ED13__INCLUDED_)
