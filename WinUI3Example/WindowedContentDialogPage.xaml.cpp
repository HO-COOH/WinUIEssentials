#include "pch.h"
#include "WindowedContentDialogPage.xaml.h"
#if __has_include("WindowedContentDialogPage.g.cpp")
#include "WindowedContentDialogPage.g.cpp"
#endif
#include "App.xaml.h"


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	winrt::fire_and_forget WindowedContentDialogPage::Button_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{

		WinUI3Package::ModernDialogBox dialog;

		auto content = dialog.DialogContent();
		content.HeaderImage(winrt::Microsoft::UI::Xaml::Media::Imaging::BitmapImage{ winrt::Windows::Foundation::Uri{L"ms-appx:///Assets/StoreLogo.png"} });
		content.Title(box_value(winrt::hstring(L"Title")));
		content.Content(winrt::box_value(L"Content"));
		content.PrimaryButtonText(winrt::hstring(L"PrimaryButton"));
		content.SecondaryButtonText(winrt::hstring(L"SecondaryButton"));
		content.CloseButtonText(winrt::hstring(L"CloseButton"));
		content.DefaultButton(Microsoft::UI::Xaml::Controls::ContentDialogButton::Primary);

		WinUI3Package::UnderlaySystemBackdropOptions BackdropOptions = {};

		dialog.UnderlaySystemBackdrop(BackdropOptions);

		co_await dialog.ShowAsync(App::AppInstance->window);

	}


	winrt::fire_and_forget WindowedContentDialogPage::Button_Click_1(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Microsoft::UI::Xaml::Controls::ContentDialog content;
		content.Title(box_value(winrt::hstring(L"Title")));
		content.Content(winrt::box_value(L"Content"));
		content.PrimaryButtonText(winrt::hstring(L"PrimaryButton"));
		content.SecondaryButtonText(winrt::hstring(L"SecondaryButton"));
		content.CloseButtonText(winrt::hstring(L"CloseButton"));
		content.DefaultButton(Microsoft::UI::Xaml::Controls::ContentDialogButton::Primary);
		co_await WinUI3Package::WindowedContentDialog{ content }.ShowAsync(App::AppInstance->window);
	}

}
