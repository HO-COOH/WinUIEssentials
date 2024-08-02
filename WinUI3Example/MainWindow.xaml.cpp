// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
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
	}

	void MainWindow::NavigationView_SelectionChanged(
		winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender,
		winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args)
	{
		auto tag = args.SelectedItem().as<winrt::hstring>();
		ContentFrame().Navigate(s_page[tag]);
	}
}
