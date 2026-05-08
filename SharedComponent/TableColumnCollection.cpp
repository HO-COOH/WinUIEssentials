#include "pch.h"
#include "TableColumnCollection.h"
#if __has_include("TableColumnCollection.g.cpp")
#include "TableColumnCollection.g.cpp"
#endif
#include "TableColumnIterator.h"
#include "TableColumnVectorView.h"

namespace winrt::PackageRoot::implementation
{
    winrt::Windows::Foundation::Collections::IIterator<PackageRoot::TableColumn> TableColumnCollection::First()
    {
        return winrt::make<TableColumnIterator>(get_strong());
    }

    PackageRoot::TableColumn TableColumnCollection::GetAt(uint32_t index)
    {
        if (index >= m_columns.size())
            throw winrt::hresult_out_of_bounds();
        return m_columns[index];
    }

    uint32_t TableColumnCollection::Size()
    {
        return static_cast<uint32_t>(m_columns.size());
    }

    winrt::Windows::Foundation::Collections::IVectorView<PackageRoot::TableColumn> TableColumnCollection::GetView()
    {
        return winrt::make<TableColumnVectorView>(get_strong());
    }

    bool TableColumnCollection::IndexOf(PackageRoot::TableColumn const& value, uint32_t& index)
    {
        auto const it = std::find(m_columns.begin(), m_columns.end(), value);
        if (it == m_columns.end())
        {
            index = 0;
            return false;
        }
        index = static_cast<uint32_t>(std::distance(m_columns.begin(), it));
        return true;
    }

    void TableColumnCollection::SetAt(uint32_t index, PackageRoot::TableColumn const& value)
    {
        if (index >= m_columns.size())
            throw winrt::hresult_out_of_bounds();
        m_columns[index] = value;
    }

    void TableColumnCollection::InsertAt(uint32_t index, PackageRoot::TableColumn const& value)
    {
        if (index > m_columns.size())
            throw winrt::hresult_out_of_bounds();
        m_columns.insert(m_columns.begin() + index, value);
    }

    void TableColumnCollection::RemoveAt(uint32_t index)
    {
        if (index >= m_columns.size())
            throw winrt::hresult_out_of_bounds();
        m_columns.erase(m_columns.begin() + index);
    }

    void TableColumnCollection::Append(PackageRoot::TableColumn const& value)
    {
        m_columns.push_back(value);
    }

    void TableColumnCollection::RemoveAtEnd()
    {
        if (m_columns.empty())
            throw winrt::hresult_out_of_bounds();
        m_columns.pop_back();
    }

    void TableColumnCollection::Clear()
    {
        m_columns.clear();
    }

    uint32_t TableColumnCollection::GetMany(uint32_t startIndex, winrt::array_view<PackageRoot::TableColumn> items)
    {
        if (startIndex >= m_columns.size())
            return 0;
        uint32_t const available = static_cast<uint32_t>(m_columns.size()) - startIndex;
        uint32_t const count = (std::min)(available, static_cast<uint32_t>(items.size()));
        for (uint32_t i = 0; i < count; ++i)
            items[i] = m_columns[startIndex + i];
        return count;
    }

    void TableColumnCollection::ReplaceAll(winrt::array_view<PackageRoot::TableColumn const> items)
    {
        m_columns.assign(items.begin(), items.end());
    }
}
