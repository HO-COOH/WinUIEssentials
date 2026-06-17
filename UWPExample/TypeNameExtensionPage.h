#pragma once

#include "TypeNameExtensionPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct TypeNameExtensionPage : TypeNameExtensionPageT<TypeNameExtensionPage>
    {
        TypeNameExtensionPage() = default;
        void NavigationView_SelectionChanged(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct TypeNameExtensionPage : TypeNameExtensionPageT<TypeNameExtensionPage, implementation::TypeNameExtensionPage>
    {
    };
}
