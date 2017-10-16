#pragma once


// CParameter 对话框

class CParameter : public CDialogEx
{
	DECLARE_DYNAMIC(CParameter)

public:
	CParameter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CParameter();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_dWidth;
	double m_dHeight;
};
