#pragma once
#include "TableColumnCollection.h"
struct TableColumnVectorView : winrt::implements<
    TableColumnVectorView,
    winrt::Windows::Foundation::Collections::IVectorView<winrt::PackageRoot::TableColumn>,
    winrt::Windows::Foundation::Collections::IIterable<winrt::PackageRoot::TableColumn>
>
{
    TableColumnVectorView(winrt::com_ptr<winrt::PackageRoot::implementation::TableColumnCollection> owner);

    winrt::PackageRoot::TableColumn GetAt(uint32_t index);
    uint32_t Size();
    bool IndexOf(winrt::PackageRoot::TableColumn const& value, uint32_t& index);
    uint32_t GetMany(uint32_t startIndex, winrt::array_view<winrt::PackageRoot::TableColumn> items);
    winrt::Windows::Foundation::Collections::IIterator<winrt::PackageRoot::TableColumn> First();

private:
    winrt::com_ptr<winrt::PackageRoot::implementation::TableColumnCollection> m_owner;
    winrt::PackageRoot::implementation::TableColumnCollection* m_ownerRaw;
};