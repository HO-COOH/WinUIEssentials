#include "pch.h"
#include "TransparentBackdrop.h"
#if __has_include("TransparentBackdrop.g.cpp")
#include "TransparentBackdrop.g.cpp"
#endif
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include "HwndHelper.hpp"
#include <dwmapi.h>
#include "WindowsVersion.hpp"
#include <winrt/Microsoft.UI.Interop.h>

namespace winrt::WinUI3Package::implementation
{
    void TransparentBackdrop::OnTargetConnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop connectedTarget, winrt::Microsoft::UI::Xaml::XamlRoot xamlRoot)
    {
        configureDwm(GetHwnd(xamlRoot));
        base_type::OnTargetConnected(connectedTarget, xamlRoot);
    }

    void TransparentBackdrop::OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop connectedTarget)
    {
        connectedTarget.SystemBackdrop(nullptr);
        base_type::OnTargetDisconnected(connectedTarget);
    }

    void TransparentBackdrop::configureDwm(HWND hwnd)
    {
        DWM_BLURBEHIND param;
        param.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
        param.fEnable = true;
        param.hRgnBlur = CreateRectRgn(-2, -2, -1, -1);
        DwmEnableBlurBehindWindow(hwnd, &param);
        OSVERSIONINFOEXW version{};
        RtlGetVersion(&version);
        if (version.dwBuildNumber >= 22000)
        {
            auto round = DWMWCP_DONOTROUND;
            winrt::check_hresult(DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &round, sizeof(round)));
        }
    }
}
