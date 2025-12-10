#pragma once

#include "TestBackdropSwitch.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TestBackdropSwitch : TestBackdropSwitchT<TestBackdropSwitch>
    {
        TestBackdropSwitch()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);
        void ComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TestBackdropSwitch : TestBackdropSwitchT<TestBackdropSwitch, implementation::TestBackdropSwitch>
    {
    };
}
