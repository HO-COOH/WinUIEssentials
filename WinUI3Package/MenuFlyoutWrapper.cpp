#include "pch.h"
#include "MenuFlyoutWrapper.h"

void MenuFlyoutWrapper::showImpl()
{
	m_menu.ShowAt(m_menuHost.GetFrame());
}

MenuFlyoutWrapper::MenuFlyoutWrapper(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& flyout) : m_menu{flyout}
{
	m_menu.ShouldConstrainToRootBounds(false);
}

void MenuFlyoutWrapper::Show(POINT p)
{
	//if (!m_dummyWindow)
	//{
	//	m_dummyFrame = {};
	//	m_dummyWindow = {};

	//	m_dummyWindow.Content(m_dummyFrame);
	//	m_dummyWindow.Activate();

	//	m_dummyFrame.Loaded([this](auto&&...)
	//		{
	//			showImpl();
	//		});
	//}
	//else
	//	showImpl();

	m_menuHost.Move(p);
	showImpl();
}
