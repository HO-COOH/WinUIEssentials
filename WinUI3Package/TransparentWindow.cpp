#include "pch.h"
#include "TransparentWindow.h"
#if __has_include("TransparentWindow.g.cpp")
#include "TransparentWindow.g.cpp"
#endif
#include "HwndHelper.hpp"
#include <dwmapi.h>
#include "WindowsVersion.hpp"
namespace winrt::WinUI3Package::implementation
{
    TransparentWindow::TransparentWindow()
    {
        configureAppWindow(AppWindow());
        SystemBackdrop(WinUI3Package::TransparentBackdrop{});
    }
    void TransparentWindow::configureAppWindow(winrt::Microsoft::UI::Windowing::AppWindow const& appWindow)
    {
        auto presenter = appWindow.Presenter().as<winrt::Microsoft::UI::Windowing::OverlappedPresenter>();
        presenter.SetBorderAndTitleBar(false, false);
        presenter.IsResizable(false);

    }
}
