#pragma once

#include "CaseCollection.g.h"

namespace winrt::UWPPackage::implementation
{
    struct CaseCollection : CaseCollectionT<CaseCollection>
    {
        CaseCollection() = default;

		UWPPackage::Case EvaluateCases(winrt::Windows::Foundation::IInspectable const& value);
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct CaseCollection : CaseCollectionT<CaseCollection, implementation::CaseCollection>
    {
    };
}
