#pragma once

#include "TableAlternateRowColorCollection.g.h"
#include "VectorBase.hpp"
#include "TableAlternateRowColor.h"

namespace winrt::PackageRoot::implementation
{
    struct TableAlternateRowColorCollection : 
        TableAlternateRowColorCollectionT<TableAlternateRowColorCollection, winrt::Windows::Foundation::Collections::IVectorView<PackageRoot::TableAlternateRowColor>>,
		VectorBase<PackageRoot::TableAlternateRowColor, winrt::com_ptr<TableAlternateRowColor>>
    {
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct TableAlternateRowColorCollection : TableAlternateRowColorCollectionT<TableAlternateRowColorCollection, implementation::TableAlternateRowColorCollection>
    {
    };
}
