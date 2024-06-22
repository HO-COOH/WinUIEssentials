#pragma once

#include "GlyphsPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct GlyphsPage : GlyphsPageT<GlyphsPage>
    {
        GlyphsPage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

        }

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Glyphs();
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct GlyphsPage : GlyphsPageT<GlyphsPage, implementation::GlyphsPage>
    {
    };
}
