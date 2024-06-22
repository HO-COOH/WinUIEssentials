#pragma once
#include <microsoft.ui.xaml.window.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.h>
#include <winrt/Microsoft.UI.Interop.h>
#include <winrt/Microsoft.UI.Windowing.h>

inline HWND GetHwnd(winrt::Microsoft::UI::Xaml::Window window)
{
    HWND hwnd{};
    window.as<IWindowNative>()->get_WindowHandle(&hwnd);
    return hwnd;
}

inline winrt::Microsoft::UI::Windowing::AppWindow GetAppWindow(HWND hwnd)
{
    return winrt::Microsoft::UI::Windowing::AppWindow::GetFromWindowId(
        winrt::Microsoft::UI::GetWindowIdFromWindow(hwnd)
    );
}
