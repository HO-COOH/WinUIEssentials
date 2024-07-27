#pragma once

#include "GeneratedIconSource.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct GeneratedIconSource : GeneratedIconSourceT<GeneratedIconSource>
    {
        GeneratedIconSource() = default;
        
        winrt::hstring Text();
        void Text(winrt::hstring value);

    private:
        winrt::hstring m_text;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct GeneratedIconSource : GeneratedIconSourceT<GeneratedIconSource, implementation::GeneratedIconSource>
    {
    };
}
