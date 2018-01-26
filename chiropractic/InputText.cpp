// InputText.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "chiropractic.h"
#include "InputText.h"
#include "afxdialogex.h"


// CInputText �Ի���

IMPLEMENT_DYNAMIC(CInputText, CDialogEx)

CInputText::CInputText(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, m_strText(_T(""))
{

}

CInputText::~CInputText()
{
}

void CInputText::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strText);
}


BEGIN_MESSAGE_MAP(CInputText, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInputText::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputText ��Ϣ�������


void CInputText::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
