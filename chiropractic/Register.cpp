// Register.cpp : 实现文件
//

#include "stdafx.h"
#include "chiropractic.h"
#include "Register.h"
#include "afxdialogex.h"


// CRegister 对话框

IMPLEMENT_DYNAMIC(CRegister, CDialogEx)

CRegister::CRegister(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, m_machineNumber(_T(""))
	, m_registerNumber(_T(""))
{

}

CRegister::~CRegister()
{
}

void CRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_machineNumber);
	DDX_Text(pDX, IDC_EDIT2, m_registerNumber);
}


BEGIN_MESSAGE_MAP(CRegister, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRegister::OnBnClickedOk)
END_MESSAGE_MAP()


// CRegister 消息处理程序


void CRegister::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_res != m_registerNumber)
	{
		MessageBox(_T("注册码不正确！"));
		return;
	}
	else
	{
		CFile file;
		CFileException e;
		CString resfile = _T("");
		if (file.Open(_T("lisense.dat"), CFile::modeCreate | CFile::modeWrite, &e))
		{
			CArchive ar(&file, CArchive::store);
			ar << m_registerNumber;
			ar.Flush();
			file.Close();
		}
		else
			file.Abort();
		MessageBox(_T("注册成功！"));
	}
		

	CDialogEx::OnOK();
}


BOOL CRegister::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
