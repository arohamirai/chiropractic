#pragma once


// CParameter �Ի���

class CParameter : public CDialogEx
{
	DECLARE_DYNAMIC(CParameter)

public:
	CParameter(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CParameter();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_dWidth;
	double m_dHeight;
};
