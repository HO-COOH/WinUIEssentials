#include "pch.h"
#include "ExperimentPage.xaml.h"
#if __has_include("ExperimentPage.g.cpp")
#include "ExperimentPage.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{

	void ExperimentPage::TestWindowBtn_Click(
		winrt::Windows::Foundation::IInspectable const&,
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::TestWindow{}.Activate();
	}

	void ExperimentPage::SelfDrawnWindowButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::EntranceAnimationDemo{}.Activate();
	}

	void ExperimentPage::CreateNonResizableBtn_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::NormalNonResizableWindow{}.Activate();
	}

	void ExperimentPage::CreateNonResizableWithWorkaroundBtn_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::NonResizableWindowWithWorkaround{}.Activate();
	}

	void ExperimentPage::FlipWindowButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::FlipWindow{}.Activate();
	}

}
