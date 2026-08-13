#pragma once

#include "MainPage.g.h"
#include <unordered_map>
#include "NavigationHelper.h"

namespace winrt::UWPExample::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        void NavigationView_SelectionChanged(
            winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender,
            winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);

        static winrt::hstring WindowTitle();
        void FooterMenuItemsHost_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void AutoSuggestBox_QuerySubmitted(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs const& args);
        void AutoSuggestBox_TextChanged(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args);
    private:
        NavigationHelper m_navigationHelper;
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
