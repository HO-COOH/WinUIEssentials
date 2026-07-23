#include "pch.h"
#include "WindowCaptionButtonWithWorkaround.h"
#if __has_include("WindowCaptionButtonWithWorkaround.g.cpp")
#include "WindowCaptionButtonWithWorkaround.g.cpp"
#endif

namespace winrt::UWPExample::implementation
{
	WindowCaptionButtonWithWorkaround::WindowCaptionButtonWithWorkaround()
	{
		winrt::Windows::ApplicationModel::Core::CoreApplication::GetCurrentView().TitleBar().ExtendViewIntoTitleBar(true);
		auto titlebar = winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().TitleBar();
		titlebar.ButtonBackgroundColor(winrt::Windows::UI::Colors::Transparent());
		titlebar.ButtonInactiveBackgroundColor(winrt::Windows::UI::Colors::Transparent());
	}
}
