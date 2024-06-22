#pragma once

#include "SettingsExpanderItemStyleSelector.g.h"

namespace winrt::UWPPackage::implementation
{
    struct SettingsExpanderItemStyleSelector : SettingsExpanderItemStyleSelectorT<SettingsExpanderItemStyleSelector>
    {
        SettingsExpanderItemStyleSelector() = default;

        winrt::Windows::UI::Xaml::Style DefaultStyle();
        void DefaultStyle(winrt::Windows::UI::Xaml::Style value);

        winrt::Windows::UI::Xaml::Style ClickableStyle();
        void ClickableStyle(winrt::Windows::UI::Xaml::Style value);

        winrt::Windows::UI::Xaml::Style SelectStyleCore(
            winrt::Windows::Foundation::IInspectable item,
            winrt::Windows::UI::Xaml::DependencyObject container);

    private:
        winrt::Windows::UI::Xaml::Style m_defaultStyle{ nullptr };
        winrt::Windows::UI::Xaml::Style m_clickableStyle{ nullptr };
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct SettingsExpanderItemStyleSelector : SettingsExpanderItemStyleSelectorT<SettingsExpanderItemStyleSelector, implementation::SettingsExpanderItemStyleSelector>
    {
    };
}
