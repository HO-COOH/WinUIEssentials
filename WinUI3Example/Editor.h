#pragma once

#include "Editor.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct Editor : EditorT<Editor>
    {
        Editor();
		Editor(winrt::hstring const& code, winrt::WinUI3Example::Language language);

        winrt::hstring Code();
        void Code(winrt::hstring const& value);

        winrt::fire_and_forget loadHtml();

        winrt::hstring m_code;
        winrt::WinUI3Example::Language m_language;
        winrt::Microsoft::Web::WebView2::Core::CoreWebView2 m_coreWebView{ nullptr };

    private:
        void createEditor();
        static double measureHeight(winrt::hstring const& value);
        static std::wstring_view ltrim(std::wstring_view str);
        static std::wstring_view rtrim(std::wstring_view str);
        static winrt::hstring stripEmptyLine(winrt::hstring const& value);
        wchar_t const* languageString() const;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct Editor : EditorT<Editor, implementation::Editor>
    {
    };
}
