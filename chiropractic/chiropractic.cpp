
// chiropractic.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "chiropractic.h"
#include "chiropracticDlg.h"
#include "Register.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CchiropracticApp

BEGIN_MESSAGE_MAP(CchiropracticApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CchiropracticApp ����

CchiropracticApp::CchiropracticApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CchiropracticApp ����

CchiropracticApp theApp;


// CchiropracticApp ��ʼ��

BOOL CchiropracticApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	// ��֤ע����
	unsigned long s1, s2;
	char sel;
	sel = '1';
	CString MyCpuID, CPUID1, CPUID2;
	__asm {
		mov eax, 01h
		xor edx, edx
		cpuid
		mov s1, edx
		mov s2, eax
	}
	//CPUID1.Format("%08X%08X",s1,s2);
	CPUID1.Format(TEXT("%08X%08X"), s1, s2);
	__asm {
		mov eax, 03h
		xor ecx, ecx
		xor edx, edx
		cpuid
		mov s1, edx
		mov s2, ecx
	} 
	CPUID2.Format(TEXT("%08X%08X"), s1, s2);

	MyCpuID = CPUID1 + CPUID2;
	DWORD ser;
	TCHAR namebuf[128];
	TCHAR filebuf[128];
	::GetVolumeInformation(TEXT("c:\\"), namebuf, 128, &ser, 0, 0, filebuf, 128);
	CString strdisk;
	strdisk.Format(TEXT("%d"), ser);
	CString strmachine;
	strmachine = MyCpuID.Mid(13, 5); //��MyCpuID�ĵ�13λ��ʼȡ5��
	strmachine += strdisk.Mid(3, 5);//��strdisk�ĵ�3λ��ʼȡ5��,�ϲ����ɻ�����

	CString reg,res;
	CString code[16] = { TEXT("ad"),TEXT("eh"),TEXT("im"),TEXT("np"),TEXT("ru"),TEXT("vy"),TEXT("zc"),TEXT("gk"),
		TEXT("pt"),TEXT("xb"),TEXT("fj"),TEXT("ox"),TEXT("wa"),TEXT("ei"),TEXT("nr"),TEXT("qu") };
	strmachine.MakeLower();
	int num = 0;
	for (int i = 0; i<10; i++)
	{
		char p = strmachine.GetAt(i);
		if (p >= 'a'&&p <= 'f')
			num = p - 'a' + 10;
		else
			num = p - '0';
		CString tmp = code[num];
		reg += tmp;
	}
	reg.MakeUpper();
	res = reg.Mid(0, 5) + reg.Mid(5, 5) + reg.Mid(10, 5) + reg.Mid(15, 5);

	CFile file;
	CFileException e;
	CString resfile = _T("");
	if (file.Open(_T("lisense.dat"), CFile::modeRead, &e))
	{
		CArchive ar(&file, CArchive::load);
		ar >> resfile;
		file.Close();
	}
	else
	{
		file.Abort();
	}

	if (resfile != res)
	{
		CRegister regDlg;
		regDlg.m_machineNumber = strmachine.MakeUpper();
		regDlg.m_res = res;
		INT_PTR ret = regDlg.DoModal();
		if (ret != IDOK)
			return;	
	}
	CchiropracticDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

