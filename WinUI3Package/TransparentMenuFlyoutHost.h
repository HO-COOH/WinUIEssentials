#pragma once
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include "TransparentWindow.h"
class TransparentMenuFlyoutHost
{
	winrt::WinUI3Package::TransparentWindow m_dummyWindow;
	//winrt::Microsoft::UI::Xaml::Window m_dummyWindow{ nullptr };
	winrt::Microsoft::UI::Xaml::Controls::Frame m_dummyFrame;

public:
	TransparentMenuFlyoutHost(std::nullptr_t);

	TransparentMenuFlyoutHost();

	void Move(POINT p);
	winrt::Microsoft::UI::Xaml::FrameworkElement GetFrame() { return m_dummyFrame; }
};
