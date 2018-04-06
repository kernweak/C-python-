#pragma once
#include "DlgChatMain.h"

// CDlgOne2One �Ի���

class CDlgOne2One : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOne2One)

public:
	CDlgOne2One(SOCKET sClient, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgOne2One();
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strShow;
	CString m_strSend;
	CString m_strTitle;
	SOCKET m_sClient;
	afx_msg void OnBtnProcSend();
	afx_msg void OnClose();
	CString m_FilePath;
	afx_msg void OnBnClickedBtnSendfile();
	HANDLE fileThread;
};
