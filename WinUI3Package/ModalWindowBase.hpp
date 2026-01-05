#pragma once
#include "HwndHelper.hpp"

template<typename WindowImplementation>
class ModalWindowBase
{
	winrt::Microsoft::UI::Xaml::Window::Closed_revoker m_closedRevoker;
	constexpr auto& getSelf()
	{
		return *static_cast<WindowImplementation*>(this);
	}

protected:
	winrt::Microsoft::UI::Xaml::Window m_parent{ nullptr };

public:
	void SetModal(winrt::Microsoft::UI::Xaml::Window const& parent)
	{
		m_parent = parent;
		m_closedRevoker = getSelf().Closed(winrt::auto_revoke, [this](auto&&...) {
			m_parent.Activate();
		});

		SetWindowLongPtr(GetHwnd(getSelf()), GWLP_HWNDPARENT, reinterpret_cast<LONG_PTR>(GetHwnd(parent)));
		auto appWindow = getSelf().AppWindow();
		appWindow.Presenter().as<winrt::Microsoft::UI::Windowing::OverlappedPresenter>().IsModal(true);
		appWindow.Show();
	}
};