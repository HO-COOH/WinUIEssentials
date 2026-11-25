#pragma once

#include "TableColumnCollection.g.h"
#include "TableColumn.h"
#include "VectorBase.hpp"

namespace winrt::PackageRoot::implementation
{
    struct TableColumnCollection :
        TableColumnCollectionT<TableColumnCollection, winrt::Windows::Foundation::Collections::IVectorView<PackageRoot::TableColumn>>,
        VectorBase<PackageRoot::TableColumn, winrt::com_ptr<TableColumn>>
    {
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct TableColumnCollection : TableColumnCollectionT<TableColumnCollection, implementation::TableColumnCollection>
    {
    };
}
