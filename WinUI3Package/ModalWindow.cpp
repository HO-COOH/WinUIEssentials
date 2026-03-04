#include "pch.h"
#include "ModalWindow.h"
#if __has_include("ModalWindow.g.cpp")
#include "ModalWindow.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	ModalWindow::ModalWindow(winrt::Microsoft::UI::Xaml::Window const& parent)
	{
		SetModal(parent);
		AppWindow().Show();
	}
}
