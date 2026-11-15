#pragma once
#include "HwndHelper.hpp"

class ModalWindowBase
{
	winrt::Microsoft::UI::Xaml::Window::Closed_revoker m_closedRevoker;
protected:
	winrt::weak_ref<winrt::Microsoft::UI::Xaml::Window> m_parent;

public:
	void SetModal(this auto&& self, winrt::Microsoft::UI::Xaml::Window const& parent)
	{
		self.m_parent = parent;
		self.m_closedRevoker = self.Closed(winrt::auto_revoke, [&self](auto&&...) {
			if (auto parent = self.m_parent.get())
				parent.Activate();
		});

		SetWindowLongPtr(GetHwnd(self), GWLP_HWNDPARENT, reinterpret_cast<LONG_PTR>(GetHwnd(parent)));
		self.AppWindow().Presenter().as<winrt::Microsoft::UI::Windowing::OverlappedPresenter>().IsModal(true);
	}
};