#pragma once
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>


template<typename T>
static T FindVisualChildByName(winrt::Microsoft::UI::Xaml::DependencyObject const& parent, winrt::hstring const& name)
{
    if (!parent)
        return nullptr;

    auto const childCount = winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetChildrenCount(parent);
    for (int i = 0; i < childCount; ++i)
    {
        auto child = winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetChild(parent, i);
        auto childName = child.GetValue(winrt::Microsoft::UI::Xaml::FrameworkElement::NameProperty()).as<winrt::hstring>();
        if (childName == name)
            return child.as<T>();

        if (auto result = FindVisualChildByName<T>(child, name))
            return result;
    }
    return nullptr;
}