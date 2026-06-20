#include "pch.h"
#include "HostBackdropWindow.xaml.h"
#if __has_include("HostBackdropWindow.g.cpp")
#include "HostBackdropWindow.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	HostBackdropWindow::HostBackdropWindow()
	{
		ExtendsContentIntoTitleBar(true);
	}
}
