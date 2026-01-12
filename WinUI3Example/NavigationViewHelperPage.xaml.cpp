#include "pch.h"
#include "NavigationViewHelperPage.xaml.h"
#if __has_include("NavigationViewHelperPage.g.cpp")
#include "NavigationViewHelperPage.g.cpp"
#endif

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	void NavigationViewHelperPage::pane8PositionLeft_Checked(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		if (nvSample8())
			nvSample8().PaneDisplayMode(winrt::Microsoft::UI::Xaml::Controls::NavigationViewPaneDisplayMode::Left);
	}

	void NavigationViewHelperPage::pane8PositionTop_Checked(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		if (nvSample8())
			nvSample8().PaneDisplayMode(winrt::Microsoft::UI::Xaml::Controls::NavigationViewPaneDisplayMode::Top);
	}

	void NavigationViewHelperPage::pane8PositionLeftCompact_Checked(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		if (nvSample8())
			nvSample8().PaneDisplayMode(winrt::Microsoft::UI::Xaml::Controls::NavigationViewPaneDisplayMode::LeftCompact);
	}

	void NavigationViewHelperPage::pane9PositionLeft_Checked(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		if (nvSample9())
			nvSample9().PaneDisplayMode(winrt::Microsoft::UI::Xaml::Controls::NavigationViewPaneDisplayMode::Left);
	}

	void NavigationViewHelperPage::pane9PositionTop_Checked(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		if (nvSample9())
			nvSample9().PaneDisplayMode(winrt::Microsoft::UI::Xaml::Controls::NavigationViewPaneDisplayMode::Top);
	}

	void NavigationViewHelperPage::pane9PositionLeftCompact_Checked(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		if (nvSample9())
			nvSample9().PaneDisplayMode(winrt::Microsoft::UI::Xaml::Controls::NavigationViewPaneDisplayMode::LeftCompact);
	}
}
