#pragma once
#include <microsoft.ui.xaml.window.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.h>
#include <winrt/Microsoft.UI.Interop.h>
#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Microsoft.UI.Content.h>

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

inline HWND GetHwnd(winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot)
{
    //On 1.7.250208002-preview1 this no longer works
    //HWND hwnd = (HWND)connectedTarget
    //    .as<winrt::Microsoft::UI::Xaml::Hosting::DesktopWindowXamlSource>()
    //    .SiteBridge()
    //    .SiteView()
    //    .EnvironmentView()
    //    .AppWindowId()
    //    .Value;
    return reinterpret_cast<HWND>(xamlRoot.ContentIslandEnvironment().AppWindowId().Value);
}