#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"


using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::UWPExample::implementation
{

	void MainPage::NavigationView_SelectionChanged(
		winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, 
		winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args)
	{
		auto tag = args.SelectedItem().as<winrt::hstring>();
		ContentFrame().Navigate(s_page[tag]);
	}

}
