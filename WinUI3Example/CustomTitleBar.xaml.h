#pragma once
#include "CustomTitleBar.g.h"

namespace winrt::WinUI3Example::implementation
{
    //If WindowEx is used within the same project you need winrt::Microsoft::UI::Xaml::Markup::ComponentConnectorT<CustomTitleBarT<CustomTitleBar>>
    struct CustomTitleBar : CustomTitleBarT<CustomTitleBar>
    {
        CustomTitleBar();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void AppTitleBar_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct CustomTitleBar : CustomTitleBarT<CustomTitleBar, implementation::CustomTitleBar>
    {
    };
}
