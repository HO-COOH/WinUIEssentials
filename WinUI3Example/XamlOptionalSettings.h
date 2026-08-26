#pragma once

#include "XamlOptionalSettings.g.h"
#include "XamlOptionalSettingsStore.h"
#include <PropertyChangeHelper.hpp>
#include <bit>

namespace winrt::WinUI3Example::implementation
{
    struct XamlOptionalSettings : 
        XamlOptionalSettingsT<XamlOptionalSettings>, 
        XamlOptionalSettingsStore, 
        MvvmHelper::PropertyChangeHelper<XamlOptionalSettings>
    {
        using XamlOptionalSettingsStore::DefaultStyleOptimizations;
        void DefaultStyleOptimizations(bool value);

        using XamlOptionalSettingsStore::DeferContextFlyoutInit;
        void DeferContextFlyoutInit(bool value);

        using XamlOptionalSettingsStore::IconNoGridOptimization;
        void IconNoGridOptimization(bool value);

        using XamlOptionalSettingsStore::OptimizeApplyStyles;
        void OptimizeApplyStyles(bool value);

        constexpr bool RequiresRestart() const noexcept
        {
            return m_requiresRestart;
        }

        constexpr int EnabledCount() const noexcept
        {
            constexpr auto AllFlags = 
                (1u << static_cast<uint32_t>(Flag::DefaultStyleOptimizations)) |
                (1u << static_cast<uint32_t>(Flag::DeferContextFlyoutInit)) |
                (1u << static_cast<uint32_t>(Flag::IconNoGridOptimization)) |
                (1u << static_cast<uint32_t>(Flag::OptimizeApplyStyles));
            return std::popcount(m_flags & AllFlags);
        }
    private:
        void requiresRestart();
        void setAndSave(Flag value, bool set);
        bool m_requiresRestart{};
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct XamlOptionalSettings : XamlOptionalSettingsT<XamlOptionalSettings, implementation::XamlOptionalSettings>
    {
    };
}
