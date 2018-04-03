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
// CDlgChatMain 对话框

class CDlgChatMain : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgChatMain)

public:
	CDlgChatMain(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgChatMain();
	CDlgChatMain(CClientSocket *pClient, CWnd* pParent = NULL);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGANONYMOUS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	BOOL m_bLogin = FALSE;
	afx_msg void OnBtnProcSend();
	CClientSocket *m_pClient;//点登录或匿名是登录界面传进来的
	CListCtrl m_listName;//list控件，在线用户列表
protected:
	afx_msg LRESULT OnMySocket(WPARAM wParam, LPARAM lParam);
public:
	CString m_strShow;//群聊编辑框
	CString m_strSend;//发送消息框
	map<CString, CDialogEx*>m_map;
	void ChatForOne2One(CHATONE2ONE &objOne2One);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
