#include "pch.h"
#include "ModalWindowPage.xaml.h"
#if __has_include("ModalWindowPage.g.cpp")
#include "ModalWindowPage.g.cpp"
#endif
#include "App.xaml.h"
#include "MainWindow.xaml.h"

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	void ModalWindowPage::Button_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::SampleModalWindow{ MainWindow::Window }.Activate();
	}

}
