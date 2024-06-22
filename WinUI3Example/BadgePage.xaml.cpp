// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "BadgePage.xaml.h"
#if __has_include("BadgePage.g.cpp")
#include "BadgePage.g.cpp"
#endif
#include <winrt/Windows.UI.Notifications.h>
#include <BadgeGlyphs.hpp>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	void BadgePage::ComboBox_SelectionChanged(
		winrt::Windows::Foundation::IInspectable const& sender,
		winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
	{
		winrt::Windows::UI::Notifications::BadgeUpdateManager::CreateBadgeUpdaterForApplication()
			.Update(BadgeGlyphs::MakeBadgeNotification(sender.as<winrt::Microsoft::UI::Xaml::Controls::ComboBox>().SelectedItem().as<winrt::hstring>().data()));
	}




	void BadgePage::Button_Click(
		winrt::Windows::Foundation::IInspectable const& sender,
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
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
