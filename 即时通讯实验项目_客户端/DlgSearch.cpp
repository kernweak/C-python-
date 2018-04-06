// DlgSearch.cpp : 实现文件
//

#include "stdafx.h"
#include "即时通讯实验项目_客户端.h"
#include "DlgSearch.h"
#include "afxdialogex.h"


// CDlgSearch 对话框

IMPLEMENT_DYNAMIC(CDlgSearch, CDialogEx)

CDlgSearch::CDlgSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_strSearch(_T(""))
{

}

CDlgSearch::~CDlgSearch()
{
}

void CDlgSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strSearch);
}


BEGIN_MESSAGE_MAP(CDlgSearch, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgSearch::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSearch 消息处理程序


void CDlgSearch::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
