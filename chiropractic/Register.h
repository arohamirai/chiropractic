#pragma once


// CRegister �Ի���

class CRegister : public CDialogEx
{
	DECLARE_DYNAMIC(CRegister)

public:
	CRegister(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegister();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_machineNumber;
	CString m_registerNumber;
	CString m_res;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
