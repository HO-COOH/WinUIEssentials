#include "pch.h"
#include "DefaultWindowBrokenCaptionButton.h"
#if __has_include("DefaultWindowBrokenCaptionButton.g.cpp")
#include "DefaultWindowBrokenCaptionButton.g.cpp"
#endif

namespace winrt::UWPExample::implementation
{
	DefaultWindowBrokenCaptionButton::DefaultWindowBrokenCaptionButton()
	{
		winrt::Windows::ApplicationModel::Core::CoreApplication::GetCurrentView().TitleBar().ExtendViewIntoTitleBar(true);
		auto titlebar = winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().TitleBar();
		titlebar.ButtonBackgroundColor(winrt::Windows::UI::Colors::Transparent());
		titlebar.ButtonInactiveBackgroundColor(winrt::Windows::UI::Colors::Transparent());
	}
}
