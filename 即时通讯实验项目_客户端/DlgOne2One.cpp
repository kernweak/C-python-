// DlgOne2One.cpp : 实现文件
//

#include "stdafx.h"
#include "即时通讯实验项目_客户端.h"
#include "DlgOne2One.h"
#include "afxdialogex.h"


// CDlgOne2One 对话框

IMPLEMENT_DYNAMIC(CDlgOne2One, CDialogEx)

CDlgOne2One::CDlgOne2One(SOCKET sClient, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_strShow(_T(""))
	, m_strSend(_T(""))
	, m_FilePath(_T(""))
	,m_sClient(sClient)
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
	DDX_Text(pDX, IDC_MFCEDITBROWSE1, m_FilePath);
}


BEGIN_MESSAGE_MAP(CDlgOne2One, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgOne2One::OnBtnProcSend)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgOne2One::OnBnClickedBtnSendfile)
END_MESSAGE_MAP()


// CDlgOne2One 消息处理程序


void CDlgOne2One::OnBtnProcSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strSend.IsEmpty()) {
		return;
	}
	CString strOne2One;
	GetWindowText(strOne2One);
	strOne2One += L":" + m_strSend;
	CStringA str = CW2A(strOne2One.GetBuffer(), CP_THREAD_ACP);
	CDlgChatMain *pParaent = (CDlgChatMain*)GetParent();
	pParaent->m_pClient->Send(ONE2ONE, str.GetBuffer(), str.GetLength() + 1);
	//显示在自己的对话框上
	m_strShow += "你说：";
	m_strShow += m_strSend;
	m_strShow += "\r\n";
	//发送内容置空
	m_strSend.Empty();
	UpdateData(FALSE);

}


void CDlgOne2One::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
	ShowWindow(SW_HIDE);
}


DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	CDlgOne2One* pDlg = (CDlgOne2One*)lpParam;
	SOCKET client = pDlg->m_sClient;
	CString strOne2One;
	pDlg->GetWindowText(strOne2One);
	CString strTemp = strOne2One + L":";
	CString strBuf;
	CDlgChatMain *pParent = (CDlgChatMain*)pDlg->GetParent();
	int nPos = pDlg->m_FilePath.ReverseFind('\\');
	CString fileName = pDlg->m_FilePath.Right(pDlg->m_FilePath.GetLength() - nPos - 1);
	strOne2One += L":" + fileName;
	CStringA str = CW2A(strOne2One.GetBuffer(), CP_THREAD_ACP);
	pParent->m_pClient->Send(FILETRANS, str.GetBuffer(), str.GetLength() + 1, client);
	std::fstream file;
	TCHAR* filePath = pDlg->m_FilePath.GetBuffer();
	file.open(filePath, std::ios::in | std::ios::binary);
	if (file.is_open())
		MessageBox(NULL, L"打开成功", L"FASDF", MB_OK);
	char buf[1024] = {};
	//显示在自己的对话框上
	while (!file.eof())
	{
		strBuf = strTemp;
		file.read(buf, 1024);
		strBuf += buf;
		str = CW2A(strBuf.GetBuffer(), CP_THREAD_ACP);
		pParent->m_pClient->Send(FILETRANS, str.GetBuffer(), str.GetLength() + 1, client);
		Sleep(50);
	}
	strBuf = strTemp;
	strBuf += "over";
	str = CW2A(strBuf.GetBuffer(), CP_THREAD_ACP);
	pParent->m_pClient->Send(FILETRANS, str.GetBuffer(), str.GetLength() + 1, client);
	MessageBox(NULL, L"发送成功！", L"提示", MB_OK);
	return TRUE;
}

void CDlgOne2One::OnBnClickedBtnSendfile()
{
	UpdateData(TRUE);
	if (m_FilePath.IsEmpty())
	{
		return;
	}
	fileThread = AfxBeginThread((AFX_THREADPROC)ThreadProc, (LPVOID)this);
	WaitForSingleObject(fileThread, -1);
}
