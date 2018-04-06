
// 即时通讯实验项目_客户端Dlg.h : 头文件
//

#pragma once
#include"ClientScoket.h"
#include"DlgChatMain.h"

// C即时通讯实验项目_客户端Dlg 对话框
class C即时通讯实验项目_客户端Dlg : public CDialogEx
{
// 构造
public:
	C即时通讯实验项目_客户端Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD___DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
