// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <WebView2Helper.hpp>

//#include <dwmapi.h>
//#pragma comment(lib, "gdi32.lib")
//#pragma comment(lib, "dwmapi.lib")
//#include <../WinUI3Package/HwndHelper.hpp>


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
        if (!WebView2Helper::IsWebView2Installed())
            InstallWebView2Dialog().ShowAsync();

        //auto hwnd = GetHwnd(*this);
        //DWM_BLURBEHIND param;
        //param.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
        //param.fEnable = true;
        //param.hRgnBlur = CreateRectRgn(-2, -2, -1, -1);
        //DwmEnableBlurBehindWindow(hwnd, &param);
    }

	void MainWindow::NavigationView_SelectionChanged(
		winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender,
		winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args)
	{
		auto tag = args.SelectedItem().as<winrt::hstring>();
		ContentFrame().Navigate(s_page[tag]);
	}
}
