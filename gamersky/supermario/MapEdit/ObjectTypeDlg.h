#if !defined(AFX_OBJECTTYPEDLG_H__C1C0FC25_6138_11D4_9BDF_BBC1B604EC13__INCLUDED_)
#define AFX_OBJECTTYPEDLG_H__C1C0FC25_6138_11D4_9BDF_BBC1B604EC13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ObjectTypeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CObjectTypeDlg dialog

class CObjectTypeDlg : public CDialog
{
// Construction
public:
	CObjectTypeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CObjectTypeDlg)
	enum { IDD = IDD_OBJECTTYPE };
	int		m_nObjectType;
	BOOL	m_bHidden;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectTypeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CObjectTypeDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTTYPEDLG_H__C1C0FC25_6138_11D4_9BDF_BBC1B604EC13__INCLUDED_)
