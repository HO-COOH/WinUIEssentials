#include "pch.h"
#include "FakeTitleBar.h"
#if __has_include("FakeTitleBar.g.cpp")
#include "FakeTitleBar.g.cpp"
#endif
#include "FlipWindow.xaml.h"

namespace winrt::WinUI3Example::implementation
{
    winrt::Microsoft::UI::Xaml::DependencyProperty FakeTitleBar::s_titleProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Title",
            winrt::xaml_typename<winrt::hstring>(),
            winrt::xaml_typename<class_type>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(L"Fake title"), nullptr }
        );

    FakeTitleBar::FakeTitleBar()
    {
        DefaultStyleKey(winrt::box_value(winrt::xaml_typename<class_type>()));
    }

    void FakeTitleBar::OnApplyTemplate()
    {
        base_type::OnApplyTemplate();
        auto CloseButton = GetTemplateChild(L"CloseButton").as<winrt::Microsoft::UI::Xaml::Controls::Button>();
        CloseButton.Click([this](auto&&...) {ParentWindow->Close(); });
    }

    winrt::hstring FakeTitleBar::Title()
    {
        return winrt::unbox_value<winrt::hstring>(GetValue(TitleProperty()));
    }

    void FakeTitleBar::Title(winrt::hstring const& value)
    {
        SetValue(TitleProperty(), winrt::box_value(value));
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty FakeTitleBar::TitleProperty()
    {
        return s_titleProperty;
    }
}
