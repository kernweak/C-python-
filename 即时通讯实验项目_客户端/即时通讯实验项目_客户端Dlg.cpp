
// ��ʱͨѶʵ����Ŀ_�ͻ���Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ʱͨѶʵ����Ŀ_�ͻ���.h"
#include "��ʱͨѶʵ����Ŀ_�ͻ���Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C��ʱͨѶʵ����Ŀ_�ͻ���Dlg �Ի���



C��ʱͨѶʵ����Ŀ_�ͻ���Dlg::C��ʱͨѶʵ����Ŀ_�ͻ���Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD___DIALOG, pParent)
	, m_strName(_T(""))
	, m_strPass(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C��ʱͨѶʵ����Ŀ_�ͻ���Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Text(pDX, IDC_EDIT2, m_strPass);
}

BEGIN_MESSAGE_MAP(C��ʱͨѶʵ����Ŀ_�ͻ���Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &C��ʱͨѶʵ����Ŀ_�ͻ���Dlg::OnBtnProcAnony)
	ON_BN_CLICKED(IDC_BUTTON2, &C��ʱͨѶʵ����Ŀ_�ͻ���Dlg::OnBtnProcRegister)
	ON_BN_CLICKED(IDC_BUTTON1, &C��ʱͨѶʵ����Ŀ_�ͻ���Dlg::OnBtnProcLogin)
END_MESSAGE_MAP()


// C��ʱͨѶʵ����Ŀ_�ͻ���Dlg ��Ϣ�������

BOOL C��ʱͨѶʵ����Ŀ_�ͻ���Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C��ʱͨѶʵ����Ŀ_�ͻ���Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C��ʱͨѶʵ����Ŀ_�ͻ���Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C��ʱͨѶʵ����Ŀ_�ͻ���Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C��ʱͨѶʵ����Ŀ_�ͻ���Dlg::OnBtnProcAnony()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!m_client.ConnectServer("127.0.0.1", 1234)) {
		MessageBox(L"���ӷ�����ʧ�ܣ�", L"Error", MB_OK | MB_ICONWARNING);
		return;
	}
	//���ش���
	ShowWindow(SW_HIDE);
	//��ʾ�������촰��
	CDlgChatMain dlgChat(&m_client);//�����Զ���Ĺ��캯��
	dlgChat.DoModal();
	m_client.Close();
	//�˳�
	C��ʱͨѶʵ����Ŀ_�ͻ���Dlg::OnClose();
}



void C��ʱͨѶʵ����Ŀ_�ͻ���Dlg::OnBtnProcRegister()
{	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡ�û���������
	UpdateData(TRUE);
	if (m_strName.IsEmpty()||m_strPass.IsEmpty()) {
		MessageBox(L"�û������붼����Ϊ��!");
		return;
	}
	if (!m_client.ConnectServer("127.0.0.1", 1234)) {
		MessageBox(L"���ӷ�����ʧ�ܣ�", L"Error!", MB_OK | MB_ICONWARNING);
		return;
	}
	//ע���û�������
	CString strSend = m_strName;
	strSend += L":" + m_strPass;
	CStringA str = CW2A(strSend.GetBuffer(), CP_THREAD_ACP);
	m_client.Send(REGISTER, str.GetBuffer(), str.GetLength() + 1);
	//�ȴ�ע����
	char *ret = m_client.Recv();
	if (ret == nullptr) {
		MessageBox(L"ע��ʧ��!");
	}
	else {
		MessageBox(L"ע��ɹ�!");
	}
	//m_client.Close();
	return;
}


void C��ʱͨѶʵ����Ŀ_�ͻ���Dlg::OnBtnProcLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡ�û���������
	UpdateData(TRUE);
	if (m_strName.IsEmpty() || m_strPass.IsEmpty()) {
		MessageBox(L"�û������붼����Ϊ��!");
		return;
	}
	if (!m_client.ConnectServer("127.0.0.1", 1234)) {
		MessageBox(L"���ӷ�����ʧ�ܣ�", L"Error!", MB_OK | MB_ICONWARNING);
		return;
	}
	CString strSend = m_strName;
	strSend += L":" + m_strPass;
	CStringA str = CW2A(strSend.GetBuffer(), CP_THREAD_ACP);
	m_client.Send(LOGIN, str.GetBuffer(), str.GetLength() + 1);
	char *ret = m_client.Recv();
	if (ret == nullptr) {
		MessageBox(L"��¼ʧ��!");
		m_client.Close();
		return;
	}
	//��¼�ɹ�
	//���õ�ǰ��¼�û�����������ʾ���Ǹ��������
	CStringA strShowName = CW2A(m_strName.GetBuffer(), CP_THREAD_ACP);
	strcpy_s(m_client.m_szName, strShowName.GetBuffer());
	//���ص�¼����
	ShowWindow(SW_HIDE);
	//��ʾ���촰��
	CDlgChatMain dlgChat(&m_client);
	dlgChat.m_bLogin = TRUE;//������ģʽ
	dlgChat.DoModal();
	m_client.Close();
	C��ʱͨѶʵ����Ŀ_�ͻ���Dlg::OnClose();
}
