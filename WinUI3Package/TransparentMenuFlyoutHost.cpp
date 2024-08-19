#include "pch.h"
#include "TransparentMenuFlyoutHost.h"
#include <winrt/Microsoft.UI.Windowing.h>
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
		m_appWindow.IsShownInSwitchers(false);
	}
	catch (...)
	{

	}
	m_dummyFrame.RequestedTheme(winrt::Microsoft::UI::Xaml::ElementTheme::Dark);
	m_dummyWindow.Content(m_dummyFrame);
	m_appWindow.Resize({ 1,1 });
	m_dummyWindow.Activate();
}

void TransparentMenuFlyoutHost::Move(POINT p)
{
	m_appWindow.MoveAndResize({ p.x, p.y, 1, 1 });
}

TransparentMenuFlyoutHost::~TransparentMenuFlyoutHost()
{
	m_dummyWindow.Close();
}
