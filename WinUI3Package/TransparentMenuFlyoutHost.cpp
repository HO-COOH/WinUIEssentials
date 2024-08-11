#include "pch.h"
#include "TransparentMenuFlyoutHost.h"
#include <winrt/Microsoft.UI.Windowing.h>
TransparentMenuFlyoutHost::TransparentMenuFlyoutHost(std::nullptr_t) : 
	m_dummyWindow{nullptr},
	m_dummyFrame{nullptr}
{
}

TransparentMenuFlyoutHost::TransparentMenuFlyoutHost()
{
	auto appWindow = m_dummyWindow.AppWindow();
	try 
	{
		appWindow.IsShownInSwitchers(false);
	}
	catch (...)
	{

	}
	m_dummyWindow.Content(m_dummyFrame);
	m_dummyWindow.Activate();
}

void TransparentMenuFlyoutHost::Move(POINT p)
{
 	m_dummyWindow.AppWindow().MoveAndResize({ p.x, p.y, 1, 1 });
}
