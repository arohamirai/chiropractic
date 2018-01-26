// RotateSee.cpp : 实现文件
//

#include "stdafx.h"
#include "chiropractic.h"
#include "RotateSee.h"
#include "afxdialogex.h"


// CRotateSee 对话框

IMPLEMENT_DYNAMIC(CRotateSee, CDialogEx)

CRotateSee::CRotateSee(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG6, pParent)
{
	m_strRotate = _T("");
}

CRotateSee::~CRotateSee()
{
}

void CRotateSee::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRotateSee, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CRotateSee::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CRotateSee::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CRotateSee::OnBnClickedButton3)
	ON_BN_CLICKED(IDCANCEL, &CRotateSee::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CRotateSee::OnBnClickedOk)
END_MESSAGE_MAP()


// CRotateSee 消息处理程序


void CRotateSee::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strRotate = _T("L");
	CDialogEx::OnOK();
}


void CRotateSee::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strRotate = _T("R");
	CDialogEx::OnOK();
}


void CRotateSee::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strRotate = _T("");
	CDialogEx::OnOK();
}


void CRotateSee::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CRotateSee::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
