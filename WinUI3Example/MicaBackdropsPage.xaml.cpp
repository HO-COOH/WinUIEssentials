#include "pch.h"
#include "MicaBackdropsPage.xaml.h"
#if __has_include("MicaBackdropsPage.g.cpp")
#include "MicaBackdropsPage.g.cpp"
#endif


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	void MicaBackdropsPage::CreateDefaultMicaButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		WinUI3Example::DefaultMicaWindow{}.Activate();
	}

	void MicaBackdropsPage::CreateStandardMicaButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Microsoft::UI::Xaml::Window window;
		window.SystemBackdrop(winrt::Microsoft::UI::Xaml::Media::MicaBackdrop{});
		window.Activate();
	}

	void MicaBackdropsPage::CreateMicaButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		WinUI3Example::CustomMicaWindow{}.Activate();
	}

	void MicaBackdropsPage::CreateMicaWithFallbackButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUI3Example::MicaBackdropWithFallbackWindow{}.Activate();
	}
}
