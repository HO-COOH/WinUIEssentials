#pragma once

#include "FontInfo.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct FontInfo : FontInfoT<FontInfo>
    {
        FontInfo(
            winrt::hstring const& name,
            winrt::Microsoft::UI::Xaml::Media::FontFamily const& font
        );

        winrt::hstring Name();
        winrt::Microsoft::UI::Xaml::Media::FontFamily Font();

    private:
        winrt::hstring m_name;
        winrt::Microsoft::UI::Xaml::Media::FontFamily m_font;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct FontInfo : FontInfoT<FontInfo, implementation::FontInfo>
    {
    };
}
