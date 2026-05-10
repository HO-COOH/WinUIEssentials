#pragma once

#include "TableColumnCollection.g.h"
#include "TableColumn.h"
#include <vector>

struct TableColumnIterator;

namespace winrt::PackageRoot::implementation
{
    struct TableColumnCollection : TableColumnCollectionT<TableColumnCollection>
    {
        friend struct ::TableColumnIterator;

        TableColumnCollection() = default;

        // IIterable<TableColumn>
        winrt::Windows::Foundation::Collections::IIterator<PackageRoot::TableColumn> First();

        // IVector<TableColumn>
        PackageRoot::TableColumn GetAt(uint32_t index);
        uint32_t Size();
        winrt::Windows::Foundation::Collections::IVectorView<PackageRoot::TableColumn> GetView();
        bool IndexOf(PackageRoot::TableColumn const& value, uint32_t& index);
        void SetAt(uint32_t index, PackageRoot::TableColumn const& value);
        void InsertAt(uint32_t index, PackageRoot::TableColumn const& value);
        void RemoveAt(uint32_t index);
        void Append(PackageRoot::TableColumn const& value);
        void RemoveAtEnd();
        void Clear();
        uint32_t GetMany(uint32_t startIndex, winrt::array_view<PackageRoot::TableColumn> items);
        void ReplaceAll(winrt::array_view<PackageRoot::TableColumn const> items);

        std::vector<winrt::com_ptr<TableColumn>> m_data;
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct TableColumnCollection : TableColumnCollectionT<TableColumnCollection, implementation::TableColumnCollection>
    {
    };
}
