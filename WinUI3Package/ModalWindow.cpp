#include "pch.h"
#include "ModalWindow.h"
#if __has_include("ModalWindow.g.cpp")
#include "ModalWindow.g.cpp"
#endif
#include "include/HwndHelper.hpp"
#include <winrt/Microsoft.UI.Windowing.h>

namespace winrt::WinUI3Package::implementation
{
	ModalWindow::ModalWindow(winrt::Microsoft::UI::Xaml::Window const& parent) : m_owner(parent)
	{
		m_closedRevoker = Closed(winrt::auto_revoke, { this, &ModalWindow::OnClosed });

		SetWindowLongPtr(GetHwnd(*this), GWLP_HWNDPARENT, reinterpret_cast<LONG_PTR>(GetHwnd(parent)));
		auto appWindow = AppWindow();
		appWindow.Presenter().as<winrt::Microsoft::UI::Windowing::OverlappedPresenter>().IsModal(true);
		appWindow.Show();
	}

	void ModalWindow::OnClosed(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::WindowEventArgs const&)
	{
		if (m_owner)
		{
			m_owner.Activate();
		}
	}
}
