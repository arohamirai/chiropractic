// InputName.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "chiropractic.h"
#include "InputName.h"
#include "afxdialogex.h"


// CInputName �Ի���

IMPLEMENT_DYNAMIC(CInputName, CDialogEx)

CInputName::CInputName(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_strName(_T(""))
{

}

CInputName::~CInputName()
{
}

void CInputName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_strName);
}


BEGIN_MESSAGE_MAP(CInputName, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInputName::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputName ��Ϣ�������




void CInputName::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	CDialogEx::OnOK();
}
