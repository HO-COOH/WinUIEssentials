#pragma once

#include "FontIconExtension.g.h"
#if defined Build_WinUIPackage
#include <winrt/Microsoft.UI.Text.h>
#else
#include <winrt/Windows.UI.Text.h>
#endif

namespace winrt::PackageRoot::implementation
{
    struct FontIconExtension : FontIconExtensionT<FontIconExtension>
    {
        FontIconExtension() = default;

        double FontSize();
        void FontSize(double value);

        winrt::Windows::UI::Text::FontWeight FontWeight();
        void FontWeight(winrt::Windows::UI::Text::FontWeight value);

        winrt::WinUINamespace::UI::Xaml::Media::FontFamily FontFamily();
        void FontFamily(winrt::WinUINamespace::UI::Xaml::Media::FontFamily value);

        winrt::Windows::UI::Text::FontStyle FontStyle();
        void FontStyle(winrt::Windows::UI::Text::FontStyle value);

        winrt::WinUINamespace::UI::Xaml::Media::Brush Foreground();
        void Foreground(winrt::WinUINamespace::UI::Xaml::Media::Brush value);

        winrt::hstring Glyph();
        void Glyph(winrt::hstring value);

        bool IsTextScaleFactorEnabled();
        void IsTextScaleFactorEnabled(bool value);

        bool MirroredWhenRightToLeft();
        void MirroredWhenRightToLeft(bool value);

        winrt::Windows::Foundation::IInspectable ProvideValue();

#if defined Build_WinUIPackage
        winrt::Windows::Foundation::IInspectable ProvideValue(
            winrt::Microsoft::UI::Xaml::IXamlServiceProvider provider
        )
        {
            return ProvideValue();
        }
#endif
    private:
        double m_fontSize{};
        winrt::Windows::UI::Text::FontWeight m_fontWeight{ winrt::WinUINamespace::UI::Text::FontWeights::Normal() };
        winrt::WinUINamespace::UI::Xaml::Media::FontFamily m_fontFamily{ nullptr };
        winrt::Windows::UI::Text::FontStyle m_fontStyle{ winrt::Windows::UI::Text::FontStyle::Normal };
        winrt::WinUINamespace::UI::Xaml::Media::Brush m_foreground{ nullptr };
        winrt::hstring m_glyph;
        bool m_isTextScaleFactorEnabled{};
        bool m_mirroredWhenRightToLeft{};
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct FontIconExtension : FontIconExtensionT<FontIconExtension, implementation::FontIconExtension>
    {
    };
}
