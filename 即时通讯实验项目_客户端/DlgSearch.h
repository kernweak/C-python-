#pragma once


// CDlgSearch 对话框

class CDlgSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSearch)

public:
	CDlgSearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSearch();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strSearch;
	afx_msg void OnBnClickedOk();
};
