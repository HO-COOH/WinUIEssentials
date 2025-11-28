#include "pch.h"
#include "TransparentMenuFlyoutHost.h"
#include <winrt/Microsoft.UI.Windowing.h>
#include "HwndHelper.hpp"
TransparentMenuFlyoutHost::TransparentMenuFlyoutHost(std::nullptr_t) : 
	m_dummyWindow{nullptr},
	m_appWindow{nullptr},
	m_dummyFrame{nullptr}
{
}

TransparentMenuFlyoutHost::TransparentMenuFlyoutHost() : m_appWindow{m_dummyWindow.AppWindow()}
{
	try 
	{
		m_appWindow.Presenter().as<winrt::Microsoft::UI::Windowing::OverlappedPresenter>().IsAlwaysOnTop(true);
		m_appWindow.IsShownInSwitchers(false); //this call might fail when explorer.exe crashes
		//See https://github.com/microsoft/microsoft-ui-xaml/issues/8596
	}
	catch (...)
	{

	}
	m_dummyFrame.RequestedTheme(winrt::Microsoft::UI::Xaml::ElementTheme::Dark);
	m_dummyWindow.Content(m_dummyFrame);
	auto const dummyHwnd = GetHwnd(m_dummyWindow);
	SetWindowLongPtr(dummyHwnd, GWL_STYLE, WS_POPUP);
	SetWindowPos(dummyHwnd, nullptr, 0, 0, 1, 1, SWP_NOMOVE | SWP_NOACTIVATE);
	m_dummyWindow.Activated([this](auto&, winrt::Microsoft::UI::Xaml::WindowActivatedEventArgs const& arg) {
		if (arg.WindowActivationState() == winrt::Microsoft::UI::Xaml::WindowActivationState::Deactivated)
			m_appWindow.Hide();
	});
}

void TransparentMenuFlyoutHost::Move(POINT p)
{
	m_appWindow.Move({ p.x, p.y });
	m_dummyWindow.Activate();
}

TransparentMenuFlyoutHost::~TransparentMenuFlyoutHost()
{
	if (m_dummyWindow)
		m_dummyWindow.Close();
}
