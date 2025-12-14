// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <WebView2Helper.hpp>
#include <HwndHelper.hpp>

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	HWND MainWindow::Hwnd;
	winrt::Microsoft::UI::Xaml::Window MainWindow::Window{ nullptr };
	WinUI3Example::MainWindow MainWindow::MainWindowInstance{ nullptr };

	MainWindow::MainWindow()
	{
		Hwnd = GetHwnd(*this);
		Window = *this;
		MainWindowInstance = *this;
		ExtendsContentIntoTitleBar(true);
		InitializeComponent();
		if (!WebView2Helper::IsWebView2Installed())
			InstallWebView2Dialog().ShowAsync();
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

		if (auto tag = args.SelectedItem().try_as<winrt::hstring>())
			ContentFrame().Navigate(s_page[*tag]);
	}

	winrt::guid MainWindow::IconGuid()
	{
		// {733204C1-9F66-4E4E-A24C-CEA34294DA39}
		return
		{ 0x733204c1, 0x9f66, 0x4e4e, { 0xa2, 0x4c, 0xce, 0xa3, 0x42, 0x94, 0xda, 0x39 } };
	}

	void winrt::WinUI3Example::implementation::MainWindow::ExitItem_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		ExitProcess(0);
	}


	void MainWindow::WindowEx_Activated(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::WindowActivatedEventArgs const& args)
	{
		TitleBarTextBlock().Opacity(args.WindowActivationState() == winrt::Microsoft::UI::Xaml::WindowActivationState::Deactivated ? 0.5f : 1.0f);
	}

	void MainWindow::FooterMenuItemsHost_Loaded(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		auto itemsRepeater = sender.as<winrt::Microsoft::UI::Xaml::Controls::ItemsRepeater>();
		auto items = itemsRepeater.ItemsSource().as<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable>>();
		auto settingsButton = items.GetAt(1).as<winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem>();
		settingsButton.Content(winrt::box_value(L"About"));
	}

}
