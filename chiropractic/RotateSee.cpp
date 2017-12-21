// RotateSee.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "chiropractic.h"
#include "RotateSee.h"
#include "afxdialogex.h"


// CRotateSee �Ի���

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


// CRotateSee ��Ϣ�������


void CRotateSee::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_strRotate = _T("L");
	CDialogEx::OnOK();
}


void CRotateSee::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_strRotate = _T("R");
	CDialogEx::OnOK();
}


void CRotateSee::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_strRotate = _T("");
	CDialogEx::OnOK();
}


void CRotateSee::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CRotateSee::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
