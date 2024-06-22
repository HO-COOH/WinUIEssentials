#pragma once

#include "FontIconExtension.g.h"
#include <winrt/Microsoft.UI.Text.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>

namespace winrt::WinUI3Package::implementation
{
    struct FontIconExtension : FontIconExtensionT<FontIconExtension>
    {
        FontIconExtension() = default;

        double FontSize();
        void FontSize(double value);

        winrt::Windows::UI::Text::FontWeight FontWeight();
        void FontWeight(winrt::Windows::UI::Text::FontWeight value);

        winrt::Microsoft::UI::Xaml::Media::FontFamily FontFamily();
        void FontFamily(winrt::Microsoft::UI::Xaml::Media::FontFamily value);

        winrt::Windows::UI::Text::FontStyle FontStyle();
        void FontStyle(winrt::Windows::UI::Text::FontStyle value);

        winrt::Microsoft::UI::Xaml::Media::Brush Foreground();
        void Foreground(winrt::Microsoft::UI::Xaml::Media::Brush value);

        winrt::hstring Glyph();
        void Glyph(winrt::hstring value);

        bool IsTextScaleFactorEnabled();
        void IsTextScaleFactorEnabled(bool value);

        bool MirroredWhenRightToLeft();
        void MirroredWhenRightToLeft(bool value);

        winrt::Windows::Foundation::IInspectable ProvideValue();
        winrt::Windows::Foundation::IInspectable ProvideValue(
            winrt::Microsoft::UI::Xaml::IXamlServiceProvider provider
        )
        {
            return ProvideValue();
        }
    private:
        double m_fontSize{};
        winrt::Windows::UI::Text::FontWeight m_fontWeight{ winrt::Microsoft::UI::Text::FontWeights::Normal() };
        winrt::Microsoft::UI::Xaml::Media::FontFamily m_fontFamily{ nullptr };
        winrt::Windows::UI::Text::FontStyle m_fontStyle{ winrt::Windows::UI::Text::FontStyle::Normal };
        winrt::Microsoft::UI::Xaml::Media::Brush m_foreground{ nullptr };
        winrt::hstring m_glyph;
        bool m_isTextScaleFactorEnabled{};
        bool m_mirroredWhenRightToLeft{};
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct FontIconExtension : FontIconExtensionT<FontIconExtension, implementation::FontIconExtension>
    {
    };
}
