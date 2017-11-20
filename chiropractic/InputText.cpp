// InputText.cpp : 实现文件
//

#include "stdafx.h"
#include "chiropractic.h"
#include "InputText.h"
#include "afxdialogex.h"


// CInputText 对话框

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


// CInputText 消息处理程序


void CInputText::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
