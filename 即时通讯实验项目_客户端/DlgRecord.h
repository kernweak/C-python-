#pragma once
#include "afxcmn.h"
#include"DlgChatMain.h"


// CDlgRecord 对话框

class CDlgRecord : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRecord)

public:
	CDlgRecord(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgRecord();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listRecord;
	void UpdateList();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
};
