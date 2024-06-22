#include "pch.h"
#include "BadgePage.h"
#if __has_include("BadgePage.g.cpp")
#include "BadgePage.g.cpp"
#endif
#include <winrt/Windows.UI.Notifications.h>
#include <BadgeGlyphs.hpp>

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::UWPExample::implementation
{
	void BadgePage::ComboBox_SelectionChanged(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
	{
		winrt::Windows::UI::Notifications::BadgeUpdateManager::CreateBadgeUpdaterForApplication()
			.Update(BadgeGlyphs::MakeBadgeNotification(sender.as<winrt::Windows::UI::Xaml::Controls::ComboBox>().SelectedItem().as<winrt::hstring>().data()));
	}




	void BadgePage::Button_Click(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		try
		{
			winrt::Windows::UI::Notifications::BadgeUpdateManager::CreateBadgeUpdaterForApplication()
				.Update(BadgeGlyphs::MakeBadgeNotification(std::stoi(NumberValue().Text().data())));
		}
		catch (...)
		{

		}
	}

}
