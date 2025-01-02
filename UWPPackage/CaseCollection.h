#pragma once

#include "CaseCollection.g.h"

namespace winrt::UWPPackage::implementation
{
    struct CaseCollection : CaseCollectionT<CaseCollection>
    {
        CaseCollection() = default;
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct CaseCollection : CaseCollectionT<CaseCollection, implementation::CaseCollection>
    {
    };
}
