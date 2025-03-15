// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <WebView2Helper.hpp>
#include <HwndHelper.hpp>

//#include <dwmapi.h>
//#pragma comment(lib, "gdi32.lib")
//#pragma comment(lib, "dwmapi.lib")
//#include <../WinUI3Package/HwndHelper.hpp>


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	HWND MainWindow::Hwnd;

	MainWindow::MainWindow()
	{
		Hwnd = GetHwnd(*this);
		InitializeComponent();
		if (!WebView2Helper::IsWebView2Installed())
			InstallWebView2Dialog().ShowAsync();
		MainIcon().Show();
	}



	void MainWindow::NavigationView_SelectionChanged(
		winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender,
		winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args)
	{
		if (args.IsSettingsSelected())
		{
			ContentFrame().Navigate(winrt::xaml_typename<WinUI3Example::AboutPage>());
			return;
		}

		auto tag = args.SelectedItem().as<winrt::hstring>();
		ContentFrame().Navigate(s_page[tag]);
	}

	winrt::guid MainWindow::IconGuid()
	{
		// {733204C1-9F66-4E4E-A24C-CEA34294DA39}
		return
		{ 0x733204c1, 0x9f66, 0x4e4e, { 0xa2, 0x4c, 0xce, 0xa3, 0x42, 0x94, 0xda, 0x39 } };
	}
}
