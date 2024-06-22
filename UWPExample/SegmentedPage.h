#pragma once

#include "SegmentedPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct SegmentedPage : SegmentedPageT<SegmentedPage>
    {
        SegmentedPage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        static winrt::Windows::UI::Xaml::Controls::ListViewSelectionMode ConvertToSelectionMode(winrt::Windows::Foundation::IInspectable value);
        static winrt::Windows::UI::Xaml::HorizontalAlignment ConvertToHorizontalAlignment(winrt::Windows::Foundation::IInspectable value);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct SegmentedPage : SegmentedPageT<SegmentedPage, implementation::SegmentedPage>
    {
    };
}
