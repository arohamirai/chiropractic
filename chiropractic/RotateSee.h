#pragma once


// CRotateSee 对话框

class CRotateSee : public CDialogEx
{
	DECLARE_DYNAMIC(CRotateSee)

public:
	CRotateSee(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRotateSee();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

public:
	CString m_strRotate;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
