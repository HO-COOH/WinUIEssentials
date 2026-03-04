#pragma once

#include "Editor.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct Editor : EditorT<Editor>
    {
        Editor() = default;

        winrt::hstring Code();
        void Code(winrt::hstring const& value);
        void WebView2_CoreWebView2Initialized(winrt::Microsoft::UI::Xaml::Controls::WebView2 const& sender, winrt::Microsoft::UI::Xaml::Controls::CoreWebView2InitializedEventArgs const& args);
        
        winrt::WinUI3Example::Language CodeLanguage();
        void CodeLanguage(winrt::WinUI3Example::Language value);
        
        winrt::WinUI3Example::Language m_language;


    private:
        static double measureHeight(winrt::hstring const& value);
        static std::wstring_view ltrim(std::wstring_view str);
        static std::wstring_view rtrim(std::wstring_view str);
        static winrt::hstring stripEmptyLine(winrt::hstring const& value);
        
        std::wstring getJavascript();
        constexpr wchar_t const* languageString() const
        {
            switch (m_language)
            {
                case winrt::WinUI3Example::Language::Xaml:
                    return L"xml";
                case winrt::WinUI3Example::Language::Cpp:
                case winrt::WinUI3Example::Language::H:
                    return L"cpp";
                case winrt::WinUI3Example::Language::Idl:
                    return L"idl";
                default:
                    return L"";
            }
        }
        
        winrt::hstring m_code;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct Editor : EditorT<Editor, implementation::Editor>
    {
    };
}
