#include "pch.h"
#include "ColorCodeEditor.h"
#if __has_include("ColorCodeEditor.g.cpp")
#include "ColorCodeEditor.g.cpp"
#endif
#include <ranges>
#include "Language.h"
#if defined Build_WinUI3Example
#include <winrt/Microsoft.UI.Xaml.Documents.h>
#else
#include <winrt/Windows.UI.Xaml.Documents.h>
#endif


template<>
struct std::formatter<ColorCode::Scope, wchar_t> : std::formatter<std::wstring_view, wchar_t>
{
    auto format(ColorCode::Scope scope, std::wformat_context& ctx) const
    {
        std::wstring_view name;
        switch (scope)
        {
            case ColorCode::Scope::Comment:     name = L"Comment"; break;
            case ColorCode::Scope::String:      name = L"String"; break;
            case ColorCode::Scope::Keyword:     name = L"Keyword"; break;
            case ColorCode::Scope::Type:        name = L"Type"; break;
            case ColorCode::Scope::Preprocessor:name = L"Preprocessor"; break;
            case ColorCode::Scope::Operator:    name = L"Operator"; break;
            case ColorCode::Scope::Identifier:  name = L"Identifier"; break;
            case ColorCode::Scope::PlainText:   name = L"PlainText"; break;
            case ColorCode::Scope::Function:    name = L"Function"; break;
            default: break;
        }
        return std::formatter<std::wstring_view, wchar_t>::format(name, ctx);
    }
};

namespace winrt::PackageRoot::implementation
{
    ColorCodeEditor::ColorCodeEditor()
    {
        InitializeComponent();
        m_highlighted = HighlightedParagraph().Inlines();
	}

    winrt::hstring ColorCodeEditor::Code()
    {
        return m_code;
    }

    void ColorCodeEditor::Code(winrt::hstring const& value)
    {
        m_code = value;
        renderToRichTextBlock();
    }

    winrt::PackageRoot::Language ColorCodeEditor::CodeLanguage()
    {
        return m_language;
    }

    void ColorCodeEditor::CodeLanguage(winrt::PackageRoot::Language value)
    {
        m_language = value;
        renderToRichTextBlock();
    }

    winrt::WinUINamespace::UI::Xaml::Documents::InlineCollection ColorCodeEditor::Highlighted()
    {
        renderToRichTextBlock();
        return m_highlighted;
    }

    winrt::hstring ColorCodeEditor::GetLineGutterFromCode(winrt::hstring const& code)
    {
		auto const lineCount = std::count(code.begin(), code.end(), L'\n') + 1;
		std::wstring gutter;
        for (auto line : std::views::iota(1, lineCount + 1))
        {
            gutter += (line == lineCount) ?
                std::format(L"{}", line) :
                std::format(L"{}\n", line);
        }
        return winrt::hstring{ std::move(gutter) };
    }


    static void DebugToken(ColorCode::Token token, winrt::hstring const& code)
    {
        OutputDebugString(std::format(L"{}: {}\n", std::wstring_view{ &code[token.start], token.length }, token.scope).data());
    }

    void ColorCodeEditor::renderToRichTextBlock()
    {
        if (m_language == winrt::PackageRoot::Language::Undefined || m_code.empty() || m_highlighted.Size() != 0)
            return;

		//winrt::WinUINamespace::UI::Xaml::Documents::Paragraph highlighted;
		//Highlighted().Blocks().Append(highlighted);

        ColorCode::Language::Tokenize(
            m_code,
            m_language == winrt::PackageRoot::Language::Xaml? ColorCode::Language::Xaml() : ColorCode::Language::Cpp(),
            [/*highlighted,*/ code = std::wstring_view{ m_code }, this](ColorCode::Token token)
            {
                DebugToken(token, m_code);

                winrt::WinUINamespace::UI::Xaml::Documents::Run run;
                run.Text(winrt::hstring{ code.data() + token.start, static_cast<winrt::hstring::size_type>(token.length) });

                winrt::Windows::UI::Color color{ 0xff, 0xff, 0xff, 0xff };
                switch (token.scope)
                {
                    case ColorCode::Scope::Comment: color = winrt::Windows::UI::Color{ 0xff, 0x7f, 0x84, 0x8e };  break;
                    case ColorCode::Scope::String: color = winrt::Windows::UI::Color{ 0xff, 0x98, 0xc3, 0x79 }; break;
                    case ColorCode::Scope::Keyword: color = winrt::Windows::UI::Color{ 0xff, 0xc6, 0x78, 0xdd }; break;
                    case ColorCode::Scope::Type: color = winrt::Windows::UI::Color{ 0xff, 0xe5, 0xc0, 0x7b }; break;
                    case ColorCode::Scope::Preprocessor: color = winrt::Windows::UI::Color{ 0xff, 0x7e, 0x84, 0x8e };  break;
                    case ColorCode::Scope::Operator: color = winrt::Windows::UI::Color{ 0xff, 0xc6, 0x78, 0xdd }; break;
                    case ColorCode::Scope::Identifier: color = winrt::Windows::UI::Color{ 0xff, 0xe0, 0x6c, 0x75 }; break;
                    case ColorCode::Scope::PlainText:color = winrt::Windows::UI::Color{ 0xff, 0x7e, 0x84, 0x8e }; break;
                    case ColorCode::Scope::Function: color = winrt::Windows::UI::Color{ 0xff, 0x61, 0xaf, 0xef }; break;
                    case ColorCode::Scope::Namespace: color = winrt::Windows::UI::Color{ 0xff, 0xc8, 0xc8, 0xbe }; break;
                    default:
                        break;
                }
                run.Foreground(winrt::WinUINamespace::UI::Xaml::Media::SolidColorBrush{ color });
                m_highlighted.Append(run);
            }
        );
    }
}

