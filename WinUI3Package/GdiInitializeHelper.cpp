#include "pch.h"
#include "GdiInitializeHelper.h"

#pragma comment(lib, "gdiplus.lib")

GdiInitializeHelper::GdiInitializeHelper()
{
	Gdiplus::GdiplusStartup(&gdiPlusToken, &gdiPlusStartupInput, nullptr);
}

GdiInitializeHelper::~GdiInitializeHelper()
{
	Gdiplus::GdiplusShutdown(gdiPlusToken);
}

void GdiInitializeHelper::Initialize()
{
	static GdiInitializeHelper s_helper;
}
