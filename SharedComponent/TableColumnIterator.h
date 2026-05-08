#pragma once
#include <winrt/base.h>
#include <vector>
#include "TableColumnCollection.h"
#include <winrt/Windows.Foundation.Collections.h>

struct TableColumnIterator : winrt::implements<
    TableColumnIterator,
    winrt::Windows::Foundation::Collections::IIterator<winrt::PackageRoot::TableColumn>
>
{
    TableColumnIterator(winrt::com_ptr<winrt::PackageRoot::implementation::TableColumnCollection> owner);

    winrt::PackageRoot::TableColumn Current();

    constexpr bool HasCurrent() const noexcept
    {
        return m_index < m_ownerRaw->m_columns.size();
    }

    constexpr bool MoveNext() noexcept
    {
        auto const& columns = m_ownerRaw->m_columns;
        if (m_index < columns.size())
            ++m_index;
        return m_index < columns.size();
    }

    uint32_t GetMany(winrt::array_view<winrt::PackageRoot::TableColumn> items);
private:
    winrt::com_ptr<winrt::PackageRoot::implementation::TableColumnCollection> m_owner;
    winrt::PackageRoot::implementation::TableColumnCollection* m_ownerRaw;
    uint32_t m_index{};
};
