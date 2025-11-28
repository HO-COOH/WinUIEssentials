#pragma once

#include "ScopedButtonDisablerPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ScopedButtonDisablerPage : ScopedButtonDisablerPageT<ScopedButtonDisablerPage>
    {
        ScopedButtonDisablerPage() = default;

        winrt::Windows::Foundation::IAsyncAction ClickHandler(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        winrt::Windows::Foundation::IAsyncAction ButtonWithScopeDisabler_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ScopedButtonDisablerPage : ScopedButtonDisablerPageT<ScopedButtonDisablerPage, implementation::ScopedButtonDisablerPage>
    {
    };
}
