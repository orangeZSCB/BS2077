#if !defined(AFX_MAPWIDTHDLG_H__F88439D4_5FC8_11D4_9BDF_F3709EB2C913__INCLUDED_)
#define AFX_MAPWIDTHDLG_H__F88439D4_5FC8_11D4_9BDF_F3709EB2C913__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapWidthDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMapWidthDlg dialog

class CMapWidthDlg : public CDialog
{
// Construction
public:
	CMapWidthDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMapWidthDlg)
	enum { IDD = IDD_MAPWIDTH };
	int		m_width;
	BOOL	m_bDarken;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapWidthDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMapWidthDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPWIDTHDLG_H__F88439D4_5FC8_11D4_9BDF_F3709EB2C913__INCLUDED_)
