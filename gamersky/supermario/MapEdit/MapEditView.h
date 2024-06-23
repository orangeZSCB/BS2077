// MapEditView.h : interface of the CMapEditView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPEDITVIEW_H__F88439C5_5FC8_11D4_9BDF_F3709EB2C913__INCLUDED_)
#define AFX_MAPEDITVIEW_H__F88439C5_5FC8_11D4_9BDF_F3709EB2C913__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMapEditDoc;
class CMapEditView : public CScrollView
{
protected: // create from serialization only
	CMapEditView();
	void Property();

	DECLARE_DYNCREATE(CMapEditView)

// Attributes
public:
	CMapEditDoc* GetDocument();

// Operations
public:
	int m_tilex, m_tiley;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapEditView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMapEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	UINT	m_object;
	CBitmap m_bmTiles;
	CBitmap m_bmGhosts[3];

	char GetTile( int x, int y );
	void SetTile( int x, int y, char tile );
	char GetSurface( int x, int y );
	void SetSurface( int x, int y, char surf );

// Generated message map functions
protected:
	//{{AFX_MSG(CMapEditView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEditMapwidth();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	void OnSelectObject( UINT nID );
	void OnUpdateObject( CCmdUI *pCmdUI );

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MapEditView.cpp
inline CMapEditDoc* CMapEditView::GetDocument()
   { return (CMapEditDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPEDITVIEW_H__F88439C5_5FC8_11D4_9BDF_F3709EB2C913__INCLUDED_)
