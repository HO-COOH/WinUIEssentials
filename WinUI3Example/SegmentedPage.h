#pragma once

#include "SegmentedPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct SegmentedPage : SegmentedPageT<SegmentedPage>
    {
        SegmentedPage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        static winrt::Microsoft::UI::Xaml::Controls::ListViewSelectionMode ConvertToSelectionMode(winrt::Windows::Foundation::IInspectable value);
        static winrt::Microsoft::UI::Xaml::HorizontalAlignment ConvertToHorizontalAlignment(winrt::Windows::Foundation::IInspectable value);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct SegmentedPage : SegmentedPageT<SegmentedPage, implementation::SegmentedPage>
    {
    };
}
