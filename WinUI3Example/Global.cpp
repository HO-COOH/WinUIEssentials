#include "pch.h"
#include "Global.h"

HWND& MainHwnd()
{
    static HWND s_instance;
    return s_instance;
}
