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
	void WindowedContentDialogPage::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUI3Example::ExampleDialog dialog;
		dialog.SetParent(MainWindow::MainWindowInstance, true, true);
		//dialog.Activate();
		dialog.ShowAsync();
	}
}
