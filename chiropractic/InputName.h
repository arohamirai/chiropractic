#pragma once


// CInputName �Ի���

class CInputName : public CDialogEx
{
	DECLARE_DYNAMIC(CInputName)

public:
	CInputName(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputName();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	afx_msg void OnBnClickedOk();
};
