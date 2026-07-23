#include "pch.h"
#include "WindowCaptionButtonThemeWorkaroundPage.h"
#if __has_include("WindowCaptionButtonThemeWorkaroundPage.g.cpp")
#include "WindowCaptionButtonThemeWorkaroundPage.g.cpp"
#endif
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.ViewManagement.h>

namespace winrt::UWPExample::implementation
{
	template<typename Page>
	static void createWindowWithPage()
	{
		auto newView = winrt::Windows::ApplicationModel::Core::CoreApplication::CreateNewView();
		newView.Dispatcher().RunAsync({}, [] {
			auto window = winrt::Windows::UI::Xaml::Window::Current();
			window.Content(Page{});
			window.Activate();

			winrt::Windows::UI::ViewManagement::ApplicationViewSwitcher::TryShowAsStandaloneAsync(
				winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Id()
			);
		});
	}

	void WindowCaptionButtonThemeWorkaroundPage::CreateWorkaroundWindowButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		createWindowWithPage<winrt::UWPExample::WindowCaptionButtonWithWorkaround>();
	}

	void WindowCaptionButtonThemeWorkaroundPage::CompareWindowsButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		createWindowWithPage<winrt::UWPExample::DefaultWindowBrokenCaptionButton>();
		createWindowWithPage<winrt::UWPExample::WindowCaptionButtonWithWorkaround>();
	}

	void WindowCaptionButtonThemeWorkaroundPage::CreateDefaultWindowButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		createWindowWithPage<winrt::UWPExample::DefaultWindowBrokenCaptionButton>();
	}

}
