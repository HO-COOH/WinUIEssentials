#pragma once

#include "PropertyBindingSampleWindow.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct PropertyBindingSampleWindow : PropertyBindingSampleWindowT<PropertyBindingSampleWindow>
    {
        void RadioButtons_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct PropertyBindingSampleWindow : PropertyBindingSampleWindowT<PropertyBindingSampleWindow, implementation::PropertyBindingSampleWindow>
    {
    };
}
