#pragma once

#include "SliderHelperPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct SliderHelperPage : SliderHelperPageT<SliderHelperPage>
    {
        SliderHelperPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct SliderHelperPage : SliderHelperPageT<SliderHelperPage, implementation::SliderHelperPage>
    {
    };
}
