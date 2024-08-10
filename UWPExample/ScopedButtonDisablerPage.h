#pragma once

#include "ScopedButtonDisablerPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct ScopedButtonDisablerPage : ScopedButtonDisablerPageT<ScopedButtonDisablerPage>
    {
        ScopedButtonDisablerPage() = default;

        winrt::Windows::Foundation::IAsyncAction ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
        winrt::Windows::Foundation::IAsyncAction ButtonWithScopeDisabler_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct ScopedButtonDisablerPage : ScopedButtonDisablerPageT<ScopedButtonDisablerPage, implementation::ScopedButtonDisablerPage>
    {
    };
}
