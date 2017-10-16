// InputName.cpp : 实现文件
//

#include "stdafx.h"
#include "chiropractic.h"
#include "InputName.h"
#include "afxdialogex.h"


// CInputName 对话框

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


// CInputName 消息处理程序




void CInputName::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CDialogEx::OnOK();
}
