// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "GlyphsPage.g.h"
#include <PropertyChangeHelper.hpp>

namespace winrt::WinUI3Example::implementation
{
    struct GlyphsPage : GlyphsPageT<GlyphsPage>, MvvmHelper::PropertyChangeHelper<GlyphsPage>
    {
        GlyphsPage() = default;
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Glyphs();
        winrt::fire_and_forget Page_Loaded(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        winrt::Windows::Foundation::Uri GlyphFont();

    private:
        bool m_hasFontDownloaded{};
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct GlyphsPage : GlyphsPageT<GlyphsPage, implementation::GlyphsPage>
    {
    };
}
