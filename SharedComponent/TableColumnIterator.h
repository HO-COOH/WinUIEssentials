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
    //None of these function can be constexpr :<
    TableColumnIterator(winrt::com_ptr<winrt::PackageRoot::implementation::TableColumnCollection> owner);
    winrt::PackageRoot::TableColumn Current();
    bool HasCurrent() const noexcept;
    bool MoveNext() noexcept;
    uint32_t GetMany(winrt::array_view<winrt::PackageRoot::TableColumn> items);
private:
    winrt::com_ptr<winrt::PackageRoot::implementation::TableColumnCollection> m_owner;
    uint32_t m_index{};
};
