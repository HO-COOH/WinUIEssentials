#pragma once

#include "GeneratedIconSource.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct GeneratedIconSource : GeneratedIconSourceT<GeneratedIconSource>
    {
        GeneratedIconSource() = default;
        
        winrt::hstring Text();
        void Text(winrt::hstring value);

        winrt::Windows::UI::Color Foreground() { return {}; }
        void Foreground(winrt::Windows::UI::Color) {}
        
        winrt::Windows::UI::Text::FontWeight FontWeight() { return {}; }
        void FontWeight(winrt::Windows::UI::Text::FontWeight) {}

        winrt::Microsoft::UI::Xaml::Media::FontFamily FontFamily() { return nullptr; }
        void FontFamily(winrt::Microsoft::UI::Xaml::Media::FontFamily) {}
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
