#pragma once

#include "SettingsExpanderItemStyleSelector.g.h"

namespace winrt::PackageRoot::implementation
{
    struct SettingsExpanderItemStyleSelector : SettingsExpanderItemStyleSelectorT<SettingsExpanderItemStyleSelector>
    {
        SettingsExpanderItemStyleSelector() = default;

        winrt::WinUINamespace::UI::Xaml::Style DefaultStyle();
        void DefaultStyle(winrt::WinUINamespace::UI::Xaml::Style value);

        winrt::WinUINamespace::UI::Xaml::Style ClickableStyle();
        void ClickableStyle(winrt::WinUINamespace::UI::Xaml::Style value);

        winrt::WinUINamespace::UI::Xaml::Style SelectStyleCore(
            winrt::Windows::Foundation::IInspectable item,
            winrt::WinUINamespace::UI::Xaml::DependencyObject container);

    private:
        winrt::WinUINamespace::UI::Xaml::Style m_defaultStyle{ nullptr };
        winrt::WinUINamespace::UI::Xaml::Style m_clickableStyle{ nullptr };
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct SettingsExpanderItemStyleSelector : SettingsExpanderItemStyleSelectorT<SettingsExpanderItemStyleSelector, implementation::SettingsExpanderItemStyleSelector>
    {
    };
}
