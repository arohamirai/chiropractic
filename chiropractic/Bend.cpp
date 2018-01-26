// Bend.cpp : 实现文件
//

#include "stdafx.h"
#include "chiropractic.h"
#include "Bend.h"
#include "afxdialogex.h"


// CBend 对话框

IMPLEMENT_DYNAMIC(CBend, CDialogEx)

CBend::CBend(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG7, pParent)
{

}

CBend::~CBend()
{
}

void CBend::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBend, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CBend::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CBend::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CBend::OnBnClickedButton2)
END_MESSAGE_MAP()


// CBend 消息处理程序


void CBend::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strBend = _T("L");
	CDialogEx::OnOK();
}

void CBend::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strBend = _T("R");
	CDialogEx::OnOK();
}
void CBend::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
