#include "pch.h"
#include "TableColumnIterator.h"
#include <algorithm>

TableColumnIterator::TableColumnIterator(winrt::com_ptr<winrt::PackageRoot::implementation::TableColumnCollection> owner) : 
    m_owner{ std::move(owner) }
{
}

winrt::PackageRoot::TableColumn TableColumnIterator::Current()
{
    auto const& columns = m_owner->m_data;
    if (m_index >= columns.size())
        throw winrt::hresult_out_of_bounds();
    return columns[m_index].as<winrt::PackageRoot::TableColumn>();
}

bool TableColumnIterator::HasCurrent() const noexcept
{
    return m_index < m_owner->m_data.size();
}

bool TableColumnIterator::MoveNext() noexcept
{
    auto const& columns = m_owner->m_data;
    if (m_index < columns.size())
        ++m_index;
    return m_index < columns.size();
}

uint32_t TableColumnIterator::GetMany(winrt::array_view<winrt::PackageRoot::TableColumn> items)
{
    auto const& columns = m_owner->m_data;
    uint32_t const size = static_cast<uint32_t>(columns.size());
    if (m_index >= size)
        return 0;
    uint32_t const count = (std::min)(size - m_index, static_cast<uint32_t>(items.size()));
    for (uint32_t i = 0; i < count; ++i)
        items[i] = columns[m_index + i].as<winrt::PackageRoot::TableColumn>();
    m_index += count;
    return count;
}
