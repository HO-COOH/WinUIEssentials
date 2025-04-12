#pragma once

#include "FakeTitleBar.g.h"
#include <TemplateControlHelper.hpp>

namespace winrt::WinUI3Example::implementation
{
    struct FakeTitleBar : FakeTitleBarT<FakeTitleBar>
    {
        FakeTitleBar()
        {
            DefaultStyleKey(winrt::box_value(winrt::xaml_typename<class_type>()));
        }

        winrt::hstring Title();
        static winrt::Microsoft::UI::Xaml::DependencyProperty TitleProperty();
    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_titleProperty;
        //winrt::hstring m_title{ L"Fake window" };
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct FakeTitleBar : FakeTitleBarT<FakeTitleBar, implementation::FakeTitleBar>
    {
    };
}
