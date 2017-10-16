// Parameter.cpp : 实现文件
//

#include "stdafx.h"
#include "chiropractic.h"
#include "Parameter.h"
#include "afxdialogex.h"


// CParameter 对话框

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
END_MESSAGE_MAP()


// CParameter 消息处理程序
