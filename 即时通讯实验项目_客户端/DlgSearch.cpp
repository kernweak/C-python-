// DlgSearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ʱͨѶʵ����Ŀ_�ͻ���.h"
#include "DlgSearch.h"
#include "afxdialogex.h"


// CDlgSearch �Ի���

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


// CDlgSearch ��Ϣ�������


void CDlgSearch::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
