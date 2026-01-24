#pragma once

#include "Convert.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct Convert : ConvertT<Convert>
    {
        constexpr static float DoubleToSingle(double value) noexcept
        {
            return static_cast<float>(value);
		}
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct Convert : ConvertT<Convert, implementation::Convert>
    {
    };
}
