// MapEdit.h : main header file for the MAPEDIT application
//

#if !defined(AFX_MAPEDIT_H__F88439BD_5FC8_11D4_9BDF_F3709EB2C913__INCLUDED_)
#define AFX_MAPEDIT_H__F88439BD_5FC8_11D4_9BDF_F3709EB2C913__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMapEditApp:
// See MapEdit.cpp for the implementation of this class
//

class CMapEditApp : public CWinApp
{
public:
	CMapEditApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapEditApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMapEditApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPEDIT_H__F88439BD_5FC8_11D4_9BDF_F3709EB2C913__INCLUDED_)
