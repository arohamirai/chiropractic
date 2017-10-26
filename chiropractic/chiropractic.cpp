
// chiropractic.cpp : 定义应用程序的类行为。
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


// CchiropracticApp 构造

CchiropracticApp::CchiropracticApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CchiropracticApp 对象

CchiropracticApp theApp;


// CchiropracticApp 初始化

BOOL CchiropracticApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	// 验证注册码
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
	strmachine = MyCpuID.Mid(13, 5); //从MyCpuID的第13位开始取5个
	strmachine += strdisk.Mid(3, 5);//从strdisk的第3位开始取5个,合并生成机器码

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
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

