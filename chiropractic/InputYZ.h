#pragma once


// CInputYZ 对话框

class CInputYZ : public CDialogEx
{
	DECLARE_DYNAMIC(CInputYZ)

public:
	CInputYZ(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInputYZ();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

public:
	bool m_bLuxs_yz[6];
	int m_total_yz;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedOk();
};
