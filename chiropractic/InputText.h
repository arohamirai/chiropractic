#pragma once


// CInputText �Ի���

class CInputText : public CDialogEx
{
	DECLARE_DYNAMIC(CInputText)

public:
	CInputText(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputText();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strText;
	afx_msg void OnBnClickedOk();
};
