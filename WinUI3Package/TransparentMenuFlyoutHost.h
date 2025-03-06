#pragma once
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Windowing.h>
#include "TransparentWindow.h"

/**
 * @brief A transparent 1*1 window for hosting a MenuFlyout for the taskbar icon
 */
class TransparentMenuFlyoutHost
{
	winrt::WinUI3Package::TransparentWindow m_dummyWindow;
	winrt::Microsoft::UI::Windowing::AppWindow m_appWindow;
	winrt::Microsoft::UI::Xaml::Controls::Frame m_dummyFrame;

public:
	TransparentMenuFlyoutHost(std::nullptr_t);

	TransparentMenuFlyoutHost();

	TransparentMenuFlyoutHost& operator=(TransparentMenuFlyoutHost&&) noexcept = default;

	void Move(POINT p);

	operator winrt::Microsoft::UI::Xaml::FrameworkElement() const
	{ 
		return m_dummyFrame; 
	}

	operator bool() const
	{
		return m_dummyWindow != nullptr;
	}

	~TransparentMenuFlyoutHost();
};
