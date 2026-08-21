#include "pch.h"
#include "PropertyBindingSampleWindow.xaml.h"
#if __has_include("PropertyBindingSampleWindow.g.cpp")
#include "PropertyBindingSampleWindow.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	void PropertyBindingSampleWindow::RadioButtons_SelectionChanged(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const&)
	{
		switch (sender.as<winrt::Microsoft::UI::Xaml::Controls::RadioButtons>().SelectedIndex())
		{
			case 0: TitleBarHeight(winrt::Microsoft::UI::Windowing::TitleBarHeightOption::Standard); break;
			case 1: TitleBarHeight(winrt::Microsoft::UI::Windowing::TitleBarHeightOption::Tall); break;
			case 2: TitleBarHeight(winrt::Microsoft::UI::Windowing::TitleBarHeightOption::Collapsed); break;
			default: break;
		}
	}
}
