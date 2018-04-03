// DlgOne2One.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ʱͨѶʵ����Ŀ_�ͻ���.h"
#include "DlgOne2One.h"
#include "afxdialogex.h"


// CDlgOne2One �Ի���

IMPLEMENT_DYNAMIC(CDlgOne2One, CDialogEx)

CDlgOne2One::CDlgOne2One(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_strShow(_T(""))
	, m_strSend(_T(""))
{

}

CDlgOne2One::~CDlgOne2One()
{
}

void CDlgOne2One::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strShow);
	DDX_Text(pDX, IDC_EDIT2, m_strSend);
}


BEGIN_MESSAGE_MAP(CDlgOne2One, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgOne2One::OnBtnProcSend)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgOne2One ��Ϣ�������


void CDlgOne2One::OnBtnProcSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_strSend.IsEmpty()) {
		return;
	}
	CString strOne2One;
	GetWindowText(strOne2One);
	strOne2One += L":" + m_strSend;
	CStringA str = CW2A(strOne2One.GetBuffer(), CP_THREAD_ACP);
	CDlgChatMain *pParaent = (CDlgChatMain*)GetParent();

}


void CDlgOne2One::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnClose();
	ShowWindow(SW_HIDE);
}
