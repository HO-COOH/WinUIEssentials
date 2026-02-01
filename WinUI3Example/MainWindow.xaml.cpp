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

#include "ToastPage.xaml.h"
#include "CursorControllerPage.xaml.h"
#include "ConvertersPage.xaml.h"
#include "BadgePage.xaml.h"
#include "TaskbarPage.xaml.h"
#include "TriggersPage.xaml.h"
#include "GroupBoxPage.xaml.h"
#include "SettingsCardPage.xaml.h"
#include "SettingsExpanderPage.xaml.h"
#include "DependentValuePage.xaml.h"
#include "MarqueeTextPage.xaml.h"
#include "GlyphsPage.xaml.h"
#include "TitleBarPage.xaml.h"
#include "ProgressBarExPage.xaml.h"
#include "WindowExPage.xaml.h"
#include "SegmentedPage.h"
#include "UriPage.xaml.h"
#include "BackdropPage.xaml.h"
#include "ShimmerPage.xaml.h"
#include "SwitchPresenterPage.xaml.h"
#include "ExperimentPage.xaml.h"
#include "TaskbarIconPage.xaml.h"
#include "ThemeListenerPage.xaml.h"
#include "ScopedButtonDisablerPage.xaml.h"
#include "InitializeWithWindowHelperPage.xaml.h"
#include "ModernStandardWindowContextMenuPage.xaml.h"
#include "ExtensionsPage.xaml.h"
#include "ComboBoxHelperPage.xaml.h"
#include "WrapPanelPage.xaml.h"
#include "AutoSuggestBoxHelperPage.xaml.h"
#include "ModalWindowPage.xaml.h"
#include "ToolTipHelperPage.xaml.h"
#include "CommandBarHelperPage.xaml.h"
#include "CaptionButtonThemeWorkaroundPage.xaml.h"
#include "NonResizableWindowWhiteBorderWorkaroundPage.xaml.h"
#include "NonMaximizableWindowWorkaroundPage.xaml.h"
#include "DatePickerHelperPage.xaml.h"
#include "TimePickerHelperPage.xaml.h"
#include "FlyoutHelperPage.xaml.h"
#include "CalendarDatePickerWorkaroundPage.xaml.h"
#include "NavigationViewHelperPage.xaml.h"
#include "RevealFocusPage.xaml.h"
#include "TenMicaPage.xaml.h"

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
			ComponentsList().ItemsSource(nullptr);
			return;
		}

		if (auto tag = args.SelectedItem().try_as<winrt::hstring>())
		{
			ContentFrame().Navigate(getPageType(*tag));
			
			// Check if the page type has a static Components member
			bool componentsFound = false;
			iteratePageType(*tag, [&](auto type)
			{
				using T = typename decltype(type)::type;
				
				// Check if T has a static Components member
				if constexpr (requires { T::Components(); })
				{
					ComponentsList().ItemsSource(winrt::single_threaded_vector(T::Components()));
					componentsFound = true;
				}
			});
			
			if (!componentsFound)
			{
				ComponentsList().ItemsSource(nullptr);
			}
		}
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

    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> MainWindow::Pages()
    {
        std::vector<winrt::Windows::Foundation::IInspectable> pages;
        pages.reserve(static_cast<size_t>(boost::hana::value(boost::hana::size(s_page))));
        boost::hana::for_each(s_page, [&](auto const& p)
        {
            pages.push_back(winrt::box_value(boost::hana::first(p)));
        });
        return winrt::single_threaded_vector(std::move(pages));
    }

    winrt::Windows::UI::Xaml::Interop::TypeName MainWindow::getPageType(winrt::hstring const& key)
    {
        winrt::Windows::UI::Xaml::Interop::TypeName result;
        iteratePageType(key, [&](auto type)
        {
            using T = typename decltype(type)::type;
            result = winrt::xaml_typename<typename T::class_type>();
        });
        return result;
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
