#pragma once

#include <climits>

#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max
#include <tiny/optional.h>
#pragma pop_macro("max")
#pragma pop_macro("min")

/*Nothing here can be constexpr: tiny::optional reads its "is empty" flag out of
  punned bits, so has_value()/value_or() are deliberately non-constexpr (and the
  const accessors go through const_cast). Marking these constexpr trips C3615.*/
struct MinMaxSize
{
    tiny::optional<int, -1> m_minWidth;
    tiny::optional<int, -1> m_minHeight;
    tiny::optional<int, -1> m_maxWidth;
    tiny::optional<int, -1> m_maxHeight;

    constexpr void MinWidth(auto value) noexcept
    {
        m_minWidth = value;
    }

    int MinWidth() const noexcept
    {
        return m_minWidth.value_or(0);
    }

    constexpr void MinHeight(auto value) noexcept
    {
        m_minHeight = value;
    }

    int MinHeight() const noexcept
    {
        return m_minHeight.value_or(0);
    }

    constexpr void MaxWidth(auto value) noexcept
    {
        m_maxWidth = value;
    }

    int MaxWidth() const noexcept
    {
        return m_maxWidth.value_or(INT_MAX);
    }

    constexpr void MaxHeight(auto value) noexcept
    {
        m_maxHeight = value;
    }

    int MaxHeight() const noexcept
    {
        return m_maxHeight.value_or(INT_MAX);
    }

    operator bool() const noexcept
    {
        return m_minWidth || m_minHeight || m_maxWidth || m_maxHeight;
    }
};
