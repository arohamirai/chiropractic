// InputYZ.cpp : 实现文件
//

#include "stdafx.h"
#include "chiropractic.h"
#include "InputYZ.h"
#include "afxdialogex.h"


// CInputYZ 对话框

IMPLEMENT_DYNAMIC(CInputYZ, CDialogEx)

CInputYZ::CInputYZ(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG5, pParent)
{
	m_bLuxs_yz[0] = false;
}

CInputYZ::~CInputYZ()
{
}

void CInputYZ::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInputYZ, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CInputYZ::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CInputYZ::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CInputYZ::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CInputYZ::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CInputYZ::OnBnClickedButton5)
	ON_BN_CLICKED(IDOK, &CInputYZ::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputYZ 消息处理程序


void CInputYZ::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bLuxs_yz[1] = true;
}


void CInputYZ::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bLuxs_yz[2] = true;
}


void CInputYZ::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bLuxs_yz[3] = true;
}


void CInputYZ::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bLuxs_yz[4] = true;
}


void CInputYZ::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bLuxs_yz[5] = true;
}


void CInputYZ::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_total_yz = 0;
	for (int i = 0; i <= 5; i++)	// 5条腰椎
	{
		if (m_bLuxs_yz[i] == true)
			m_total_yz += 1;
	}
	CDialogEx::OnOK();
}
