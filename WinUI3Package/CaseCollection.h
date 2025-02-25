#pragma once

#include "CaseCollection.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct CaseCollection : CaseCollectionT<CaseCollection>
    {
        CaseCollection() = default;

        WinUI3Package::Case EvaluateCases(winrt::Windows::Foundation::IInspectable const& value);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct CaseCollection : CaseCollectionT<CaseCollection, implementation::CaseCollection>
    {
    };
}
