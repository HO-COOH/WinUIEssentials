#include "pch.h"
#include "AcrylicBackdropsPage.xaml.h"
#if __has_include("AcrylicBackdropsPage.g.cpp")
#include "AcrylicBackdropsPage.g.cpp"
#endif


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	void AcrylicBackdropsPage::CreateDefaultAcrylicButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		WinUI3Example::DefaultAcrylicWindow{}.Activate();
	}

	void AcrylicBackdropsPage::CreateStandardAcrylicButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Microsoft::UI::Xaml::Window window;
		window.SystemBackdrop(winrt::Microsoft::UI::Xaml::Media::DesktopAcrylicBackdrop{});
		window.Activate();
	}

	void AcrylicBackdropsPage::CreateAcrylicButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		WinUI3Example::CustomAcrylicWindow{}.Activate();
	}

}
