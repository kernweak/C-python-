
// ��ʱͨѶʵ����Ŀ_�ͻ���Dlg.h : ͷ�ļ�
//

#pragma once
#include"ClientScoket.h"
#include"DlgChatMain.h"

// C��ʱͨѶʵ����Ŀ_�ͻ���Dlg �Ի���
class C��ʱͨѶʵ����Ŀ_�ͻ���Dlg : public CDialogEx
{
// ����
public:
	C��ʱͨѶʵ����Ŀ_�ͻ���Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD___DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	CString m_strPass;
	CClientSocket m_client;
	afx_msg void OnBtnProcAnony();
	afx_msg void OnBtnProcRegister();
	afx_msg void OnBtnProcLogin();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
