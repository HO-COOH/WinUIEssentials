#include "pch.h"
#include "FontIconExtension.h"
#if __has_include("FontIconExtension.g.cpp")
#include "FontIconExtension.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
    double FontIconExtension::FontSize()
    {
        return m_fontSize;
    }
    void FontIconExtension::FontSize(double value)
    {
        m_fontSize = value;
    }
    winrt::Windows::UI::Text::FontWeight FontIconExtension::FontWeight()
    {
        return m_fontWeight;
    }
    void FontIconExtension::FontWeight(winrt::Windows::UI::Text::FontWeight value)
    {
        m_fontWeight = value;
    }
    winrt::Microsoft::UI::Xaml::Media::FontFamily FontIconExtension::FontFamily()
    {
        return m_fontFamily;
    }
    void FontIconExtension::FontFamily(winrt::Microsoft::UI::Xaml::Media::FontFamily value)
    {
        m_fontFamily = value;
    }
    winrt::Windows::UI::Text::FontStyle FontIconExtension::FontStyle()
    {
        return m_fontStyle;
    }
    void FontIconExtension::FontStyle(winrt::Windows::UI::Text::FontStyle value)
    {
        m_fontStyle = value;
    }
    winrt::Microsoft::UI::Xaml::Media::Brush FontIconExtension::Foreground()
    {
        return m_foreground;
    }
    void FontIconExtension::Foreground(winrt::Microsoft::UI::Xaml::Media::Brush value)
    {
        m_foreground = value;
    }
    winrt::hstring FontIconExtension::Glyph()
    {
        return m_glyph;
    }
    void FontIconExtension::Glyph(winrt::hstring value)
    {
        m_glyph = value;
    }
    bool FontIconExtension::IsTextScaleFactorEnabled()
    {
        return m_isTextScaleFactorEnabled;
    }
    void FontIconExtension::IsTextScaleFactorEnabled(bool value)
    {
        m_isTextScaleFactorEnabled = value;
    }
    bool FontIconExtension::MirroredWhenRightToLeft()
    {
        return m_mirroredWhenRightToLeft;
    }
    void FontIconExtension::MirroredWhenRightToLeft(bool value)
    {
        m_mirroredWhenRightToLeft = value;
    }
    winrt::Windows::Foundation::IInspectable FontIconExtension::ProvideValue()
    {
        winrt::Microsoft::UI::Xaml::Controls::FontIcon fontIcon;
        fontIcon.Glyph(Glyph());
        fontIcon.FontFamily(FontFamily() ? FontFamily() : winrt::Microsoft::UI::Xaml::Media::FontFamily{ L"Segoe Fluent Icons,Segoe MDL2 Assets" });
        fontIcon.FontWeight(FontWeight());
        fontIcon.FontStyle(FontStyle());
        fontIcon.IsTextScaleFactorEnabled(IsTextScaleFactorEnabled());
        fontIcon.MirroredWhenRightToLeft(MirroredWhenRightToLeft());
        if (FontSize() > 0)
        {
            fontIcon.FontSize(FontSize());
        }
        if (Foreground())
        {
            fontIcon.Foreground(Foreground());
        }
        return fontIcon;
    }
}
