
// chiropractic.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include"InitGdiplus.h"

// CchiropracticApp: 
// �йش����ʵ�֣������ chiropractic.cpp
//

class CchiropracticApp : public CWinApp
{
public:
	CchiropracticApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

	CInitGdiplus m_InitGdiplus;
};

extern CchiropracticApp theApp;