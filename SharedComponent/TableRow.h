#pragma once

#include "TableRow.g.h"
#include "VectorBase.hpp"

namespace winrt::PackageRoot::implementation
{
    struct TableRow :
        TableRowT<TableRow, winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Foundation::IInspectable>>,
        VectorBase<winrt::Windows::Foundation::IInspectable>
    {
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct TableRow : TableRowT<TableRow, implementation::TableRow>
    {
    };
}
