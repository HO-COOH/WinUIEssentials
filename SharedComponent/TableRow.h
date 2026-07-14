#pragma once

#include "TableRow.g.h"
#include "VectorBase.hpp"

namespace winrt::PackageRoot::implementation
{
    struct TableRow :
        TableRowT<TableRow>,
        VectorBase<TableRow, winrt::Windows::Foundation::IInspectable, winrt::Windows::Foundation::IInspectable>
    {

        static winrt::Windows::Foundation::IInspectable const& to_projected(winrt::Windows::Foundation::IInspectable const& stored) noexcept
        {
            return stored;
        }
        static winrt::Windows::Foundation::IInspectable to_stored(winrt::Windows::Foundation::IInspectable const& value)
        {
            return value;
        }
        static bool is_same(winrt::Windows::Foundation::IInspectable const& stored, winrt::Windows::Foundation::IInspectable const& value) noexcept
        {
            return stored == value;
        }
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct TableRow : TableRowT<TableRow, implementation::TableRow>
    {
    };
}
