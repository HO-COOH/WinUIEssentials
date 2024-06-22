#pragma once

#include "LineGraphPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct LineGraphPage : LineGraphPageT<LineGraphPage>
    {
        LineGraphPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct LineGraphPage : LineGraphPageT<LineGraphPage, implementation::LineGraphPage>
    {
    };
}
