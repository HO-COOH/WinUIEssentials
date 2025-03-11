#include "pch.h"
#include "NonResizableWindowWhiteBorderWorkaround.h"
#if __has_include("NonResizableWindowWhiteBorderWorkaround.g.cpp")
#include "NonResizableWindowWhiteBorderWorkaround.g.cpp"
#endif
#include "WinUIEssentialError.hpp"
#include "HwndHelper.hpp"
namespace winrt::WinUI3Package::implementation
{
    winrt::Microsoft::UI::Xaml::Window NonResizableWindowWhiteBorderWorkaround::Window()
    {
        throw GetterNotImplemented{ L"NonResizableWindowWhiteBorderWorkaround.Window" };
    }

    void NonResizableWindowWhiteBorderWorkaround::Window(winrt::Microsoft::UI::Xaml::Window const& value)
    {
        auto const hwnd = GetHwnd(value);
        SetWindowLongPtr(hwnd, GWL_STYLE, GetWindowLongPtr(hwnd, GWL_STYLE) & ~WS_DLGFRAME);
    }
}
