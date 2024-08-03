#pragma once
#include <gdiplus.h>
class GdiInitializeHelper
{
    ULONG_PTR gdiPlusToken;
    Gdiplus::GdiplusStartupInput gdiPlusStartupInput;

    GdiInitializeHelper();
    ~GdiInitializeHelper();
public:

    static void Initialize();
};

