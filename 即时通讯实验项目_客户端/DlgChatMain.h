#pragma once
#include "ClientScoket.h"
#include"DlgOne2One.h"
#include <winsock2.h>
#include <process.h>
#include <stdio.h>
#include<string>  
#include<iostream>  
#include<map> 
#include "afxcmn.h"
using namespace std;
#define WM_SOCKET WM_USER +1 
// CDlgChatMain �Ի���

class CDlgChatMain : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgChatMain)

public:
	CDlgChatMain(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgChatMain();
	CDlgChatMain(CClientSocket *pClient, CWnd* pParent = NULL);

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGANONYMOUS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	BOOL m_bLogin = FALSE;
	afx_msg void OnBtnProcSend();
	CClientSocket *m_pClient;//���¼�������ǵ�¼���洫������
	CListCtrl m_listName;//list�ؼ��������û��б�
protected:
	afx_msg LRESULT OnMySocket(WPARAM wParam, LPARAM lParam);
public:
	CString m_strShow;//Ⱥ�ı༭��
	CString m_strSend;//������Ϣ��
	map<CString, CDialogEx*>m_map;
	void ChatForOne2One(CHATONE2ONE &objOne2One);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
