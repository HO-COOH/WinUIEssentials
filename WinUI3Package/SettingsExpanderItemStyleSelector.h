#pragma once

#include "SettingsExpanderItemStyleSelector.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct SettingsExpanderItemStyleSelector : SettingsExpanderItemStyleSelectorT<SettingsExpanderItemStyleSelector>
    {
        SettingsExpanderItemStyleSelector() = default;

        winrt::Microsoft::UI::Xaml::Style DefaultStyle();
        void DefaultStyle(winrt::Microsoft::UI::Xaml::Style value);

        winrt::Microsoft::UI::Xaml::Style ClickableStyle();
        void ClickableStyle(winrt::Microsoft::UI::Xaml::Style value);

        winrt::Microsoft::UI::Xaml::Style SelectStyleCore(
            winrt::Windows::Foundation::IInspectable item,
            winrt::Microsoft::UI::Xaml::DependencyObject container);

    private:
        winrt::Microsoft::UI::Xaml::Style m_defaultStyle{ nullptr };
        winrt::Microsoft::UI::Xaml::Style m_clickableStyle{ nullptr };
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct SettingsExpanderItemStyleSelector : SettingsExpanderItemStyleSelectorT<SettingsExpanderItemStyleSelector, implementation::SettingsExpanderItemStyleSelector>
    {
    };
}
