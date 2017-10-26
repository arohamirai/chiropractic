// Register.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "chiropractic.h"
#include "Register.h"
#include "afxdialogex.h"


// CRegister �Ի���

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


// CRegister ��Ϣ�������


void CRegister::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (m_res != m_registerNumber)
	{
		MessageBox(_T("ע���벻��ȷ��"));
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
		MessageBox(_T("ע��ɹ���"));
	}
		

	CDialogEx::OnOK();
}


BOOL CRegister::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
