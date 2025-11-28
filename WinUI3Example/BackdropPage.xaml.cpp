#include "pch.h"
#include "BackdropPage.xaml.h"
#if __has_include("BackdropPage.g.cpp")
#include "BackdropPage.g.cpp"
#endif


namespace winrt::WinUI3Example::implementation
{

	void BackdropPage::CreateDefaultAcrylicButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		WinUI3Example::DefaultAcrylicWindow{}.Activate();
	}


	void BackdropPage::CreateStandardAcrylicButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Microsoft::UI::Xaml::Window window;
		window.SystemBackdrop(winrt::Microsoft::UI::Xaml::Media::DesktopAcrylicBackdrop{});
		window.Activate();
	}

	void BackdropPage::CreateAcrylicButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		WinUI3Example::CustomAcrylicWindow{}.Activate();
	}


	void BackdropPage::CreateDefaultMicaButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		WinUI3Example::DefaultMicaWindow{}.Activate();
	}


	void BackdropPage::CreateStandardMicaButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Microsoft::UI::Xaml::Window window;
		window.SystemBackdrop(winrt::Microsoft::UI::Xaml::Media::MicaBackdrop{});
		window.Activate();
	}


	void BackdropPage::CreateMicaButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		WinUI3Example::CustomMicaWindow{}.Activate();
	}

	void BackdropPage::CreateTransparentButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		WinUI3Example::TransparentWindowDemo{}.Activate();
	}


	void BackdropPage::CreateNotifyButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		//WinUI3Package::RoundedAnimatedAcrylicWindowWithShadow{}.Activate();
	}

	void BackdropPage::CreateMicaWithFallbackButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUI3Example::MicaBackdropWithFallbackWindow{}.Activate();
	}
}
