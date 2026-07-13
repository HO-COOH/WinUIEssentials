#pragma once

#include "TableAlternateRowColorCollection.g.h"
#include "VectorBase.hpp"
#include "TableAlternateRowColor.h"

namespace winrt::PackageRoot::implementation
{
    struct TableAlternateRowColorCollection : 
        TableAlternateRowColorCollectionT<TableAlternateRowColorCollection>,
		VectorBase<TableAlternateRowColorCollection, PackageRoot::TableAlternateRowColor, winrt::com_ptr<TableAlternateRowColor>>
    {

		static PackageRoot::TableAlternateRowColor to_projected(winrt::com_ptr<TableAlternateRowColor> const& stored)
		{
			return *stored;
		}

        static winrt::com_ptr<TableAlternateRowColor> to_stored(PackageRoot::TableAlternateRowColor const& value)
        {
            return winrt::get_self<TableAlternateRowColor>(value)->get_strong();
        }

		static bool is_same(winrt::com_ptr<TableAlternateRowColor> const& stored, PackageRoot::TableAlternateRowColor const& value)
		{
			return stored.get() == winrt::get_self<TableAlternateRowColor>(value);
		}
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct TableAlternateRowColorCollection : TableAlternateRowColorCollectionT<TableAlternateRowColorCollection, implementation::TableAlternateRowColorCollection>
    {
    };
}
