#include "pch.h"
#include "WindowedContentDialogPage.xaml.h"
#if __has_include("WindowedContentDialogPage.g.cpp")
#include "WindowedContentDialogPage.g.cpp"
#endif
#include "MainWindow.xaml.h"


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	winrt::fire_and_forget WindowedContentDialogPage::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		//WinUI3Example::ExampleDialog dialog;
		//dialog.SetParent(MainWindow::MainWindowInstance, true, true);
		//co_await dialog.ShowAsync();

		WinUI3Package::WindowedContentDialog dialog;

		auto content = dialog.ContentDialogContent();
		content.Title(box_value(winrt::hstring(L"Title")));
		content.Content(winrt::box_value(L"Content"));
		content.PrimaryButtonText(winrt::hstring(L"PrimaryButton"));
		content.SecondaryButtonText(winrt::hstring(L"SecondaryButton"));
		content.CloseButtonText(winrt::hstring(L"CloseButton"));
		content.DefaultButton(Microsoft::UI::Xaml::Controls::ContentDialogButton::Primary);

		dialog.HasTitleBar(true);

		WinUI3Package::UnderlaySystemBackdropOptions BackdropOptions = {};

		dialog.UnderlaySystemBackdrop(BackdropOptions);

		co_await dialog.ShowAsync(MainWindow::MainWindowInstance);

	}
}
