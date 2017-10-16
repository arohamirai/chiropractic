#pragma once


// CInputName 对话框

class CInputName : public CDialogEx
{
	DECLARE_DYNAMIC(CInputName)

public:
	CInputName(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInputName();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	afx_msg void OnBnClickedOk();
};
