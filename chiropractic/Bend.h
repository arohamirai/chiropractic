#pragma once


// CBend 对话框

class CBend : public CDialogEx
{
	DECLARE_DYNAMIC(CBend)

public:
	CBend(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBend();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG7 };
#endif



public:
	CString m_strBend;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton2();
};
