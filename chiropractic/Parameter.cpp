// Parameter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "chiropractic.h"
#include "Parameter.h"
#include "afxdialogex.h"


// CParameter �Ի���

IMPLEMENT_DYNAMIC(CParameter, CDialogEx)

CParameter::CParameter(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_dWidth(0)
	, m_dHeight(0)
{

}

CParameter::~CParameter()
{
}

void CParameter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_dWidth);
	DDX_Text(pDX, IDC_EDIT2, m_dHeight);
}


BEGIN_MESSAGE_MAP(CParameter, CDialogEx)
	ON_BN_CLICKED(IDOK, &CParameter::OnBnClickedOk)
END_MESSAGE_MAP()


// CParameter ��Ϣ�������


void CParameter::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (m_dWidth == 0 || m_dHeight == 0)
		MessageBox(_T("�߶Ȼ���ֵ����Ϊ�㣬���������룡"));
	else
		CDialogEx::OnOK();
}
