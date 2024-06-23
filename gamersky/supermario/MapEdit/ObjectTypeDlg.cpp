// ObjectTypeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapEdit.h"
#include "ObjectTypeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjectTypeDlg dialog


CObjectTypeDlg::CObjectTypeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CObjectTypeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CObjectTypeDlg)
	m_nObjectType = -1;
	m_bHidden = FALSE;
	//}}AFX_DATA_INIT
}


void CObjectTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjectTypeDlg)
	DDX_Radio(pDX, IDC_COIN, m_nObjectType);
	DDX_Check(pDX, IDC_HIDDEN, m_bHidden);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CObjectTypeDlg, CDialog)
	//{{AFX_MSG_MAP(CObjectTypeDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjectTypeDlg message handlers
