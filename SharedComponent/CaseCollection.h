#pragma once

#include "CaseCollection.g.h"

namespace winrt::PackageRoot::implementation
{
    struct CaseCollection : CaseCollectionT<CaseCollection>
    {
        CaseCollection() = default;

        PackageRoot::Case EvaluateCases(winrt::Windows::Foundation::IInspectable const& value);
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct CaseCollection : CaseCollectionT<CaseCollection, implementation::CaseCollection>
    {
    };
}
