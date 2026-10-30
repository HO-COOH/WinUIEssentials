#include "pch.h"
#include "ModernWindowCaptionButtonToolTipPage.xaml.h"
#if __has_include("ModernWindowCaptionButtonToolTipPage.g.cpp")
#include "ModernWindowCaptionButtonToolTipPage.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	void ModernWindowCaptionButtonToolTipPage::OriginalWinUI3WindowButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::OriginalWinUI3Window{}.Activate();
	}

	void ModernWindowCaptionButtonToolTipPage::OriginalWinUI3WindowExtendedButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::OriginalWinUI3Window window;
		window.ExtendsContentIntoTitleBar(true);
		window.Activate();
	}

	void ModernWindowCaptionButtonToolTipPage::OriginalWinUI3WindowWithModernToolTipButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::OriginalWinUI3WindowWithModernToolTip{ Animate().IsOn() }.Activate();
	}

	void ModernWindowCaptionButtonToolTipPage::OriginalWinUI3WindowExtendedWithModernToolTipButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::OriginalWinUI3WindowExtendedWithModernToolTip{ Animate().IsOn() }.Activate();
	}
}
