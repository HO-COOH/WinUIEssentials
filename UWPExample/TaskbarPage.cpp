#include "pch.h"
#include "TaskbarPage.h"
#if __has_include("TaskbarPage.g.cpp")
#include "TaskbarPage.g.cpp"
#endif
#include <winrt/Windows.UI.Core.h>
//#include <WindowHelper.hpp>

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::UWPExample::implementation
{
	void TaskbarPage::ComboBox_SelectionChanged(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
	{
		//auto const index = sender.as<winrt::Windows::UI::Xaml::Controls::ComboBox>().SelectedIndex();

		//Taskbar::ProgressState state{};
		//switch (index)
		//{
		//case 0: state = Taskbar::ProgressState::NoProgress; break;
		//case 1: state = Taskbar::ProgressState::Indeterminate; break;
		//case 2: state = Taskbar::ProgressState::Normal; break;
		//case 3: state = Taskbar::ProgressState::Error; break;
		//default: state = Taskbar::ProgressState::Paused; break;
		//}
		//auto hwnd = GetHwnd(winrt::Windows::UI::Core::CoreWindow::GetForCurrentThread());
		//Taskbar::SetProgressState(hwnd, state);
		//Taskbar::SetProgressValue(hwnd, 50);
	}

}
