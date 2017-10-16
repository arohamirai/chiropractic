#include "StdAfx.h"
#include "InitGdiplus.h"

#include "StdAfx.h"

CInitGdiplus::CInitGdiplus(void)
{
	 GdiplusStartup(&m_GdiplusToken, &gdiplusStartupInput, NULL);
}

CInitGdiplus::~CInitGdiplus(void)
{
	GdiplusShutdown(m_GdiplusToken);
}
