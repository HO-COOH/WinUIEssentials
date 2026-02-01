#pragma once

#include "FakeTitleBar.g.h"
#include <TemplateControlHelper.hpp>

namespace winrt::WinUI3Example::implementation
{
    struct FlipWindow;

    struct FakeTitleBar : FakeTitleBarT<FakeTitleBar>
    {
        FakeTitleBar();

        void OnApplyTemplate();

        winrt::hstring Title();
        void Title(winrt::hstring const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty TitleProperty();

        FlipWindow* ParentWindow{};
    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_titleProperty;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct FakeTitleBar : FakeTitleBarT<FakeTitleBar, implementation::FakeTitleBar>
    {
    };
}
