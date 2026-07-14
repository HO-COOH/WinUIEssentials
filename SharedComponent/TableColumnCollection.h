#pragma once

#include "TableColumnCollection.g.h"
#include "TableColumn.h"
#include "VectorBase.hpp"

namespace winrt::PackageRoot::implementation
{
    struct TableColumnCollection :
        TableColumnCollectionT<TableColumnCollection>,
        VectorBase<TableColumnCollection, PackageRoot::TableColumn, winrt::com_ptr<TableColumn>>
    {

        static PackageRoot::TableColumn to_projected(winrt::com_ptr<TableColumn> const& stored)
        {
            return *stored;
        }

        static winrt::com_ptr<TableColumn> to_stored(PackageRoot::TableColumn const& value)
        {
            return winrt::get_self<TableColumn>(value)->get_strong();
        }

        static bool is_same(winrt::com_ptr<TableColumn> const& stored, PackageRoot::TableColumn const& value)
        {
            return stored.get() == winrt::get_self<TableColumn>(value);
        }
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct TableColumnCollection : TableColumnCollectionT<TableColumnCollection, implementation::TableColumnCollection>
    {
    };
}
