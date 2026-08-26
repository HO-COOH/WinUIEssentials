#pragma once
#include <cstdint>
#include <winrt/Windows.Foundation.Collections.h>

class XamlOptionalSettingsStore
{
protected:

    winrt::Windows::Foundation::Collections::IPropertySet m_settings{ nullptr };
    uint32_t m_flags{};

    enum class Flag
    {
        None,
        DefaultStyleOptimizations,
        DeferContextFlyoutInit,
        IconNoGridOptimization,
        OptimizeApplyStyles,
    };

    constexpr bool hasFlag(Flag value) const
    {
        return m_flags & (1 << static_cast<uint32_t>(value));
    }

    constexpr void setFlag(Flag value)
    {
        m_flags |= (1 << static_cast<uint32_t>(value));
    }

    constexpr void removeFlag(Flag value)
    {
        m_flags &= ~(1u << static_cast<uint32_t>(value));
    }

    void save();
public:
    XamlOptionalSettingsStore();
    XamlOptionalSettingsStore(winrt::Windows::Foundation::Collections::IPropertySet const& settings);

    constexpr bool DefaultStyleOptimizations() const
    {
        return hasFlag(Flag::DefaultStyleOptimizations);
    }

    constexpr bool DeferContextFlyoutInit() const
    {
        return hasFlag(Flag::DeferContextFlyoutInit);
    }

    constexpr bool IconNoGridOptimization() const
    {
        return hasFlag(Flag::IconNoGridOptimization);
    }

    constexpr bool OptimizeApplyStyles() const
    {
        return hasFlag(Flag::OptimizeApplyStyles);
    }
};