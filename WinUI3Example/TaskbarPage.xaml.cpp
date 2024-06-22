// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "TaskbarPage.xaml.h"
#if __has_include("TaskbarPage.g.cpp")
#include "TaskbarPage.g.cpp"
#endif
#include <Taskbar.hpp>
#include "Global.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    TaskbarPage::TaskbarPage()
    {
        InitializeComponent();
    }

	void TaskbarPage::ComboBox_SelectionChanged(
		winrt::Windows::Foundation::IInspectable const& sender,
		winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
	{
		auto const index = sender.as<winrt::Microsoft::UI::Xaml::Controls::ComboBox>().SelectedIndex();

		Taskbar::ProgressState state{};
		switch (index)
		{
		case 0: state = Taskbar::ProgressState::NoProgress; break;
		case 1: state = Taskbar::ProgressState::Indeterminate; break;
		case 2: state = Taskbar::ProgressState::Normal; break;
		case 3: state = Taskbar::ProgressState::Error; break;
		default: state = Taskbar::ProgressState::Paused; break;
		}
		Taskbar::SetProgressState(MainHwnd(), state);
		
	}


	void TaskbarPage::Slider_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
	{
		Taskbar::SetProgressValue(MainHwnd(), ProgressSlider().Value());
	}
}
