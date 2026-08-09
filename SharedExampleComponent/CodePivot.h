#pragma once

#include "CodePivot.g.h"

namespace winrt::PackageRoot::implementation
{
    struct CodePivot : CodePivotT<CodePivot>
    {
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct CodePivot : CodePivotT<CodePivot, implementation::CodePivot>
    {
    };
}
