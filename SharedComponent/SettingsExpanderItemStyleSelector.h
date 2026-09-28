#pragma once

#include "SettingsExpanderItemStyleSelector.g.h"

namespace winrt::PackageRoot::implementation
{
    struct SettingsExpanderItemStyleSelector : SettingsExpanderItemStyleSelectorT<SettingsExpanderItemStyleSelector>
    {

        winrt::WinUINamespace::UI::Xaml::Style DefaultStyle();
        void DefaultStyle(winrt::WinUINamespace::UI::Xaml::Style const& value);

        winrt::WinUINamespace::UI::Xaml::Style ClickableStyle();
        void ClickableStyle(winrt::WinUINamespace::UI::Xaml::Style const& value);

        winrt::WinUINamespace::UI::Xaml::Style SelectStyleCore(
            winrt::Windows::Foundation::IInspectable const& item,
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& container);

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
