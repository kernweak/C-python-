// DlgChatMain.cpp : 实现文件
//

#include "stdafx.h"
#include "即时通讯实验项目_客户端.h"
#include "DlgChatMain.h"
#include "afxdialogex.h"

// CDlgChatMain 对话框

IMPLEMENT_DYNAMIC(CDlgChatMain, CDialogEx)

CDlgChatMain::CDlgChatMain(CWnd* pParent /*=NULL*/)
	//: CDialogEx(IDD_DIALOG1, pParent)
	: CDialogEx(IDD_DLGANONYMOUS, pParent)
	, m_strShow(_T(""))
	, m_strSend(_T(""))
{

}

CDlgChatMain::~CDlgChatMain()
{
}

CDlgChatMain::CDlgChatMain(CClientSocket * pClient, CWnd * pParent)
	:CDialogEx(IDD_DLGANONYMOUS,pParent),m_pClient(pClient)
{
}

void CDlgChatMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_listName);
	DDX_Text(pDX, IDC_EDIT2, m_strShow);
	DDX_Text(pDX, IDC_EDIT1, m_strSend);
}


BEGIN_MESSAGE_MAP(CDlgChatMain, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgChatMain::OnBtnProcSend)
	ON_MESSAGE(WM_SOCKET, &CDlgChatMain::OnMySocket)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CDlgChatMain::OnNMDblclkList1)
END_MESSAGE_MAP()


// CDlgChatMain 消息处理程序


BOOL CDlgChatMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//设置窗口标题为用户昵称
	//匿名登录是m_pClient->m_szName是一个随机值，构造函数内初始化
	CString strTitle(m_pClient->m_szName);
	SetWindowText(strTitle.GetBuffer());
	//设置窗口任务栏可见
	ModifyStyleEx(0, WS_EX_APPWINDOW);
	//在线用户列表
	m_listName.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listName.InsertColumn(0, L"在线列表", 0, 100);
	//使用消息选择模型绑定socket和当前对话框
	WSAAsyncSelect(m_pClient->m_sClient, m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
	m_pClient->Send(ANONYMOUS, m_pClient->m_szName, strlen(m_pClient->m_szName) + 1);
	return TRUE;
}

void CDlgChatMain::OnBtnProcSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strSend.IsEmpty()) {
		//如果为空不发送
		return;
	}
	CStringA str = CW2A(m_strSend.GetBuffer(), CP_THREAD_ACP);//宽字符转多字符
	m_pClient->Send(CHAT, str.GetBuffer(), str.GetLength() + 1);
	//显示在自己的对话框上
	m_strShow += "你说";
	m_strShow += m_strSend;
	m_strShow += "\r\n";
	//把发送内容设置为空
	m_strSend.Empty();
	UpdateData(FALSE);

}


afx_msg LRESULT CDlgChatMain::OnMySocket(WPARAM wParam, LPARAM lParam)
{
	//wparam是socket
	//lparam低word是事件
	//lparam高word是错误码
	SOCKET s = wParam;
	WORD wEvent = WSAGETSELECTEVENT(lParam);
	WORD wErrorCode = WSAGETSELECTERROR(lParam);
	//先判断是否有网络错误事件发生，有则跳过
	if (wErrorCode) {
		exit(0);
		MessageBox(L"网络错误！");
		CDialogEx::OnClose();
	}
	switch (wEvent) {
	case FD_READ:
	{
		char *szRecv = m_pClient->Recv();
		if (szRecv == nullptr) {
			if (m_pClient->m_pObjUpdate) {
				//更新用户列表用到
				//判断用户是加入还是退出
				//RecvForUpdateUserList函数返回处理
				//InsertOrDeleteUser(*m_pClient->m_pObjUpdate);
				delete m_pClient->m_pObjUpdate;
				m_pClient->m_pObjUpdate = nullptr;
			}
			else if (m_pClient->m_pObjOne2One) {
				//1对1聊天用到
				//RecvForOne2one函数返回处理
				ChatForOne2One(*m_pClient->m_pObjOne2One);
				delete m_pClient->m_pObjOne2One;
				m_pClient->m_pObjOne2One = nullptr;
			}
			return 0;
		}
		UpdateData(TRUE);
		m_strShow += szRecv;
		m_strShow += "\r\n";
		UpdateData(FALSE);

	}
	 default:
		break;
	}
	return 0;
}


void CDlgChatMain::ChatForOne2One(CHATONE2ONE & objOne2One)
{
	CString strName(objOne2One.szName);
	CString strContent(objOne2One.szContent);
	if (m_map.find(strName) == m_map.end()) {
		//创建私聊窗口
		CDlgOne2One *pDlg = new CDlgOne2One;
		pDlg->Create(IDD_DIALOG1, this);
		pDlg->SetWindowTextW(strName.GetBuffer());
		m_map[strName] = pDlg;
		pDlg->m_strShow += strName + L":" + strContent;
		pDlg->m_strShow += "\r\n";
		pDlg->UpdateData(FALSE);
		pDlg->ShowWindow(SW_SHOW);
	}
}

void CDlgChatMain::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	//双击的空白区域
	if (pNMItemActivate->iItem == -1)return;
	//新建1v1聊天对话框
	CDlgOne2One *pDlg = new CDlgOne2One;
	pDlg->Create(IDD_DIALOG1, this);//把当前窗口指定为私聊窗口的父窗口
	//设置窗口标题为要聊天的目标用户名称
	CString strTitle = m_listName.GetItemText(pNMItemActivate->iItem, 0);
	pDlg->SetWindowTextW(strTitle.GetBuffer());
	//把该私聊窗口添加到自己的私聊MAP表里面
	m_map[strTitle] = pDlg;
}
