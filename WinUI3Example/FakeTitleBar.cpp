#include "pch.h"
#include "FakeTitleBar.h"
#if __has_include("FakeTitleBar.g.cpp")
#include "FakeTitleBar.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
    winrt::Microsoft::UI::Xaml::DependencyProperty FakeTitleBar::s_titleProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Title",
            winrt::xaml_typename<winrt::hstring>(),
            winrt::xaml_typename<class_type>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(L"Fake title"), nullptr }
        );
    winrt::hstring FakeTitleBar::Title()
    {
        return winrt::unbox_value<winrt::hstring>(GetValue(TitleProperty()));
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty FakeTitleBar::TitleProperty()
    {
        return s_titleProperty;
    }
}
