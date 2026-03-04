#include "pch.h"
#include "TenMicaBackdropWindow.xaml.h"
#if __has_include("TenMicaBackdropWindow.g.cpp")
#include "TenMicaBackdropWindow.g.cpp"
#endif

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	TenMicaBackdropWindow::TenMicaBackdropWindow()
	{
		ExtendsContentIntoTitleBar(true);
	}
}
