// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <WebView2Helper.hpp>
#include <HwndHelper.hpp>
#include <wil/cppwinrt.h>
#include <LayoutUpdateAwaiter.hpp>
#include <winrt/Microsoft.UI.Xaml.Media.h>

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	HWND MainWindow::Hwnd;

	MainWindow::MainWindow()
	{
		Hwnd = GetHwnd(*this);
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
			ComponentsList().ItemsSource(nullptr);
			return;
		}

		if (auto tag = args.SelectedItemContainer().Tag())
			ContentFrame().Navigate(winrt::unbox_value<winrt::Windows::UI::Xaml::Interop::TypeName>(tag));
	}

	void winrt::WinUI3Example::implementation::MainWindow::ExitItem_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		//ExitProcess(0);
		MainIcon().Remove();
		winrt::Microsoft::UI::Xaml::Application::Current().Exit();
	}


	static void CloseAllWebViews(winrt::Microsoft::UI::Xaml::DependencyObject const& root)
	{
		if (auto webview = root.try_as<winrt::Microsoft::UI::Xaml::Controls::WebView2>())
		{
			webview.Close();
			return;
		}
		auto count = winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetChildrenCount(root);
		for (int i = 0; i < count; ++i)
			CloseAllWebViews(winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetChild(root, i));
	}

	void MainWindow::WindowEx_Closed(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::WindowEventArgs const&)
	{
		CloseAllWebViews(Content());
		MainIcon().Remove();
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


	winrt::Windows::Foundation::IAsyncAction MainWindow::MoreButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		auto target = PageSourceContentButton();
		auto button = MoreButton();

		button.IsHitTestVisible(false);
		target.IsHitTestVisible(false);

		button.ReleasePointerCaptures();
		winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(button, L"Normal", false);
		winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(target, L"Normal", false);

		if (target.Visibility() == winrt::Microsoft::UI::Xaml::Visibility::Collapsed)
		{
			target.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			co_await LayoutUpdateAwaiter{ target };
		}

		m_sourceButtonAnimations.CreateForwardPass(button, target);
		m_sourceButtonAnimations.Play();
	}

	void MainWindow::PageSourceContentButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	winrt::Windows::Foundation::Uri MainWindow::GetXamlUrl(winrt::hstring const& name)
	{
		return winrt::Windows::Foundation::Uri{ std::format(L"https://github.com/HO-COOH/WinUIEssentials/blob/master/WinUI3Package/{}.xaml", name) };
	}

}
