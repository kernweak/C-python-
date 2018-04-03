// DlgChatMain.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ʱͨѶʵ����Ŀ_�ͻ���.h"
#include "DlgChatMain.h"
#include "afxdialogex.h"

// CDlgChatMain �Ի���

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


// CDlgChatMain ��Ϣ�������


BOOL CDlgChatMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//���ô��ڱ���Ϊ�û��ǳ�
	//������¼��m_pClient->m_szName��һ�����ֵ�����캯���ڳ�ʼ��
	CString strTitle(m_pClient->m_szName);
	SetWindowText(strTitle.GetBuffer());
	//���ô����������ɼ�
	ModifyStyleEx(0, WS_EX_APPWINDOW);
	//�����û��б�
	m_listName.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listName.InsertColumn(0, L"�����б�", 0, 100);
	//ʹ����Ϣѡ��ģ�Ͱ�socket�͵�ǰ�Ի���
	WSAAsyncSelect(m_pClient->m_sClient, m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
	m_pClient->Send(ANONYMOUS, m_pClient->m_szName, strlen(m_pClient->m_szName) + 1);
	return TRUE;
}

void CDlgChatMain::OnBtnProcSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_strSend.IsEmpty()) {
		//���Ϊ�ղ�����
		return;
	}
	CStringA str = CW2A(m_strSend.GetBuffer(), CP_THREAD_ACP);//���ַ�ת���ַ�
	m_pClient->Send(CHAT, str.GetBuffer(), str.GetLength() + 1);
	//��ʾ���Լ��ĶԻ�����
	m_strShow += "��˵";
	m_strShow += m_strSend;
	m_strShow += "\r\n";
	//�ѷ�����������Ϊ��
	m_strSend.Empty();
	UpdateData(FALSE);

}


afx_msg LRESULT CDlgChatMain::OnMySocket(WPARAM wParam, LPARAM lParam)
{
	//wparam��socket
	//lparam��word���¼�
	//lparam��word�Ǵ�����
	SOCKET s = wParam;
	WORD wEvent = WSAGETSELECTEVENT(lParam);
	WORD wErrorCode = WSAGETSELECTERROR(lParam);
	//���ж��Ƿ�����������¼���������������
	if (wErrorCode) {
		exit(0);
		MessageBox(L"�������");
		CDialogEx::OnClose();
	}
	switch (wEvent) {
	case FD_READ:
	{
		char *szRecv = m_pClient->Recv();
		if (szRecv == nullptr) {
			if (m_pClient->m_pObjUpdate) {
				//�����û��б��õ�
				//�ж��û��Ǽ��뻹���˳�
				//RecvForUpdateUserList�������ش���
				//InsertOrDeleteUser(*m_pClient->m_pObjUpdate);
				delete m_pClient->m_pObjUpdate;
				m_pClient->m_pObjUpdate = nullptr;
			}
			else if (m_pClient->m_pObjOne2One) {
				//1��1�����õ�
				//RecvForOne2one�������ش���
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
		//����˽�Ĵ���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	//˫���Ŀհ�����
	if (pNMItemActivate->iItem == -1)return;
	//�½�1v1����Ի���
	CDlgOne2One *pDlg = new CDlgOne2One;
	pDlg->Create(IDD_DIALOG1, this);//�ѵ�ǰ����ָ��Ϊ˽�Ĵ��ڵĸ�����
	//���ô��ڱ���ΪҪ�����Ŀ���û�����
	CString strTitle = m_listName.GetItemText(pNMItemActivate->iItem, 0);
	pDlg->SetWindowTextW(strTitle.GetBuffer());
	//�Ѹ�˽�Ĵ�����ӵ��Լ���˽��MAP������
	m_map[strTitle] = pDlg;
}
