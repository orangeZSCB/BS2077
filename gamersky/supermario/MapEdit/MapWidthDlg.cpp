// MapWidthDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapEdit.h"
#include "MapWidthDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapWidthDlg dialog


CMapWidthDlg::CMapWidthDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMapWidthDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMapWidthDlg)
	m_width = 0;
	m_bDarken = FALSE;
	//}}AFX_DATA_INIT
}


void CMapWidthDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapWidthDlg)
	DDX_Text(pDX, IDC_WIDTH, m_width);
	DDV_MinMaxInt(pDX, m_width, 20, 2000);
	DDX_Check(pDX, IDC_DARKEN, m_bDarken);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMapWidthDlg, CDialog)
	//{{AFX_MSG_MAP(CMapWidthDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapWidthDlg message handlers

BOOL CMapWidthDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_WIDTH)->SetFocus();

	return FALSE;
}
