#include "pch.h"
#include "TableColumnCollection.h"
#if __has_include("TableColumnCollection.g.cpp")
#include "TableColumnCollection.g.cpp"
#endif
#include "TableColumnIterator.h"
#include "TableColumnVectorView.h"

namespace winrt::PackageRoot::implementation
{
    static winrt::com_ptr<TableColumn> toImpl(PackageRoot::TableColumn const& value)
    {
        return winrt::get_self<TableColumn>(value)->get_strong();
    }

    winrt::Windows::Foundation::Collections::IIterator<PackageRoot::TableColumn> TableColumnCollection::First()
    {
        return winrt::make<TableColumnIterator>(get_strong());
    }

    PackageRoot::TableColumn TableColumnCollection::GetAt(uint32_t index)
    {
        if (index >= m_data.size())
            throw winrt::hresult_out_of_bounds();
        return *m_data[index];
    }

    uint32_t TableColumnCollection::Size()
    {
        return static_cast<uint32_t>(m_data.size());
    }

    winrt::Windows::Foundation::Collections::IVectorView<PackageRoot::TableColumn> TableColumnCollection::GetView()
    {
        return winrt::make<TableColumnVectorView>(get_strong());
    }

    bool TableColumnCollection::IndexOf(PackageRoot::TableColumn const& value, uint32_t& index)
    {
        auto* target = winrt::get_self<TableColumn>(value);
        auto const it = std::find_if(m_data.begin(), m_data.end(),[target](auto const& entry) { return entry.get() == target; });
        if (it == m_data.end())
        {
            index = 0;
            return false;
        }
        index = static_cast<uint32_t>(std::distance(m_data.begin(), it));
        return true;
    }

    void TableColumnCollection::SetAt(uint32_t index, PackageRoot::TableColumn const& value)
    {
        if (index >= m_data.size())
            throw winrt::hresult_out_of_bounds();
        m_data[index] = toImpl(value);
    }

    void TableColumnCollection::InsertAt(uint32_t index, PackageRoot::TableColumn const& value)
    {
        if (index > m_data.size())
            throw winrt::hresult_out_of_bounds();
        m_data.insert(m_data.begin() + index, toImpl(value));
    }

    void TableColumnCollection::RemoveAt(uint32_t index)
    {
        if (index >= m_data.size())
            throw winrt::hresult_out_of_bounds();
        m_data.erase(m_data.begin() + index);
    }

    void TableColumnCollection::Append(PackageRoot::TableColumn const& value)
    {
        m_data.push_back(toImpl(value));
    }

    void TableColumnCollection::RemoveAtEnd()
    {
        if (m_data.empty())
            throw winrt::hresult_out_of_bounds();
        m_data.pop_back();
    }

    void TableColumnCollection::Clear()
    {
        m_data.clear();
    }

    uint32_t TableColumnCollection::GetMany(uint32_t startIndex, winrt::array_view<PackageRoot::TableColumn> items)
    {
        if (startIndex >= m_data.size())
            return 0;
        uint32_t const available = static_cast<uint32_t>(m_data.size()) - startIndex;
        uint32_t const count = (std::min)(available, static_cast<uint32_t>(items.size()));
        for (uint32_t i = 0; i < count; ++i)
            items[i] = *m_data[startIndex + i];
        return count;
    }

    void TableColumnCollection::ReplaceAll(winrt::array_view<PackageRoot::TableColumn const> items)
    {
        m_data.resize(items.size());
        std::ranges::transform(items, m_data.begin(), toImpl);
    }
}
