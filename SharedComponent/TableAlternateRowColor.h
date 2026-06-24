#pragma once

#include "TableAlternateRowColor.g.h"

namespace winrt::PackageRoot::implementation
{
    struct TableAlternateRowColor : TableAlternateRowColorT<TableAlternateRowColor>
    {
        TableAlternateRowColor() = default;
        
		constexpr winrt::Windows::UI::Color ForegroundColor() const noexcept { return m_foregroundColor; }
		constexpr void ForegroundColor(winrt::Windows::UI::Color const& value) noexcept { m_foregroundColor = value; }
		constexpr winrt::Windows::UI::Color BackgroundColor() const noexcept { return m_backgroundColor; }
		constexpr void BackgroundColor(winrt::Windows::UI::Color const& value) noexcept { m_backgroundColor = value; }

		winrt::Windows::UI::Color m_foregroundColor{};
		winrt::Windows::UI::Color m_backgroundColor{};
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct TableAlternateRowColor : TableAlternateRowColorT<TableAlternateRowColor, implementation::TableAlternateRowColor>
    {
    };
}
