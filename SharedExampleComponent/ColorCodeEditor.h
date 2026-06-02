#pragma once

#include "ColorCodeEditor.g.h"

namespace winrt::PackageRoot::implementation
{
    struct ColorCodeEditor : ColorCodeEditorT<ColorCodeEditor>
    {
        ColorCodeEditor();

        winrt::hstring Code();
        void Code(winrt::hstring const& value);

        winrt::PackageRoot::Language CodeLanguage();
        void CodeLanguage(winrt::PackageRoot::Language value);
        
        winrt::WinUINamespace::UI::Xaml::Documents::InlineCollection Highlighted();

        static winrt::hstring GetLineGutterFromCode(winrt::hstring const& code);
    private:
		winrt::hstring m_code;
        winrt::PackageRoot::Language m_language{ winrt::PackageRoot::Language::Undefined };
        winrt::WinUINamespace::UI::Xaml::Documents::InlineCollection m_highlighted{ nullptr };

        void renderToRichTextBlock();
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct ColorCodeEditor : ColorCodeEditorT<ColorCodeEditor, implementation::ColorCodeEditor>
    {
    };
}
