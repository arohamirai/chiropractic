#pragma once


// CBend �Ի���

class CBend : public CDialogEx
{
	DECLARE_DYNAMIC(CBend)

public:
	CBend(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBend();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG7 };
#endif



public:
	CString m_strBend;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton2();
};
