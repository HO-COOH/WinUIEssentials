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
    void ColorCodeEditor::EnsureDependencyProperties()
    {
        if (m_commentColorProperty)
            return;

        std::ranges::generate(s_brushes, [] { return winrt::WinUINamespace::UI::Xaml::Media::SolidColorBrush{}; });

        m_commentColorProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"CommentColor",
            winrt::xaml_typename<winrt::Windows::UI::Color>(),
            winrt::xaml_typename<PackageRoot::ColorCodeEditor>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &ColorCodeEditor::commentColorChanged }
        );
        m_stringColorProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"StringColor",
            winrt::xaml_typename<winrt::Windows::UI::Color>(),
            winrt::xaml_typename<PackageRoot::ColorCodeEditor>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &ColorCodeEditor::stringColorChanged }
        );
        m_keywordColorProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"KeywordColor",
            winrt::xaml_typename<winrt::Windows::UI::Color>(),
            winrt::xaml_typename<PackageRoot::ColorCodeEditor>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &ColorCodeEditor::keywordColorChanged }
        );
        m_typeColorProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"TypeColor",
            winrt::xaml_typename<winrt::Windows::UI::Color>(),
            winrt::xaml_typename<PackageRoot::ColorCodeEditor>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &ColorCodeEditor::typeColorChanged }
        );
        m_preprocessorColorProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"PreprocessorColor",
            winrt::xaml_typename<winrt::Windows::UI::Color>(),
            winrt::xaml_typename<PackageRoot::ColorCodeEditor>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &ColorCodeEditor::preprocessorColorChanged }
        );
        m_operatorColorProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"OperatorColor",
            winrt::xaml_typename<winrt::Windows::UI::Color>(),
            winrt::xaml_typename<PackageRoot::ColorCodeEditor>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &ColorCodeEditor::operatorColorChanged }
        );
        m_identifierColorProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"IdentifierColor",
            winrt::xaml_typename<winrt::Windows::UI::Color>(),
            winrt::xaml_typename<PackageRoot::ColorCodeEditor>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &ColorCodeEditor::identifierColorChanged }
        );
        m_plainTextColorProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"PlainTextColor",
            winrt::xaml_typename<winrt::Windows::UI::Color>(),
            winrt::xaml_typename<PackageRoot::ColorCodeEditor>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &ColorCodeEditor::plainTextColorChanged }
        );
        m_functionColorProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"FunctionColor",
            winrt::xaml_typename<winrt::Windows::UI::Color>(),
            winrt::xaml_typename<PackageRoot::ColorCodeEditor>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &ColorCodeEditor::functionColorChanged }
        );
        m_namespaceColorProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"NamespaceColor",
            winrt::xaml_typename<winrt::Windows::UI::Color>(),
            winrt::xaml_typename<PackageRoot::ColorCodeEditor>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &ColorCodeEditor::namespaceColorChanged }
        );
    }

    ColorCodeEditor::ColorCodeEditor()
    {
        InitializeComponent();
        m_highlighted = HighlightedParagraph().Inlines();
	}

    winrt::Windows::UI::Color ColorCodeEditor::CommentColor()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(m_commentColorProperty));
    }

    void ColorCodeEditor::CommentColor(winrt::Windows::UI::Color value)
    {
        SetValue(m_commentColorProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty ColorCodeEditor::CommentColorProperty()
    {
        return m_commentColorProperty;
    }

    winrt::Windows::UI::Color ColorCodeEditor::StringColor()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(m_stringColorProperty));
    }

    void ColorCodeEditor::StringColor(winrt::Windows::UI::Color value)
    {
        SetValue(m_stringColorProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty ColorCodeEditor::StringColorProperty()
    {
        return m_stringColorProperty;
    }

    winrt::Windows::UI::Color ColorCodeEditor::KeywordColor()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(m_keywordColorProperty));
    }

    void ColorCodeEditor::KeywordColor(winrt::Windows::UI::Color value)
    {
        SetValue(m_keywordColorProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty ColorCodeEditor::KeywordColorProperty()
    {
        return m_keywordColorProperty;
    }

    winrt::Windows::UI::Color ColorCodeEditor::TypeColor()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(m_typeColorProperty));
    }

    void ColorCodeEditor::TypeColor(winrt::Windows::UI::Color value)
    {
        SetValue(m_typeColorProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty ColorCodeEditor::TypeColorProperty()
    {
        return m_typeColorProperty;
    }

    winrt::Windows::UI::Color ColorCodeEditor::PreprocessorColor()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(m_preprocessorColorProperty));
    }

    void ColorCodeEditor::PreprocessorColor(winrt::Windows::UI::Color value)
    {
        SetValue(m_preprocessorColorProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty ColorCodeEditor::PreprocessorColorProperty()
    {
        return m_preprocessorColorProperty;
    }

    winrt::Windows::UI::Color ColorCodeEditor::OperatorColor()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(m_operatorColorProperty));
    }

    void ColorCodeEditor::OperatorColor(winrt::Windows::UI::Color value)
    {
        SetValue(m_operatorColorProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty ColorCodeEditor::OperatorColorProperty()
    {
        return m_operatorColorProperty;
    }

    winrt::Windows::UI::Color ColorCodeEditor::IdentifierColor()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(m_identifierColorProperty));
    }

    void ColorCodeEditor::IdentifierColor(winrt::Windows::UI::Color value)
    {
        SetValue(m_identifierColorProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty ColorCodeEditor::IdentifierColorProperty()
    {
        return m_identifierColorProperty;
    }

    winrt::Windows::UI::Color ColorCodeEditor::PlainTextColor()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(m_plainTextColorProperty));
    }

    void ColorCodeEditor::PlainTextColor(winrt::Windows::UI::Color value)
    {
        SetValue(m_plainTextColorProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty ColorCodeEditor::PlainTextColorProperty()
    {
        return m_plainTextColorProperty;
    }

    winrt::Windows::UI::Color ColorCodeEditor::FunctionColor()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(m_functionColorProperty));
    }

    void ColorCodeEditor::FunctionColor(winrt::Windows::UI::Color value)
    {
        SetValue(m_functionColorProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty ColorCodeEditor::FunctionColorProperty()
    {
        return m_functionColorProperty;
    }

    winrt::Windows::UI::Color ColorCodeEditor::NamespaceColor()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(m_namespaceColorProperty));
    }

    void ColorCodeEditor::NamespaceColor(winrt::Windows::UI::Color value)
    {
        SetValue(m_namespaceColorProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty ColorCodeEditor::NamespaceColorProperty()
    {
        return m_namespaceColorProperty;
    }

    void ColorCodeEditor::commentColorChanged(
        winrt::WinUINamespace::UI::Xaml::DependencyObject const&,
        winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        s_brushes[static_cast<size_t>(ColorCode::Scope::Comment)].Color(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
    }

    void ColorCodeEditor::stringColorChanged(
        winrt::WinUINamespace::UI::Xaml::DependencyObject const&,
        winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        s_brushes[static_cast<size_t>(ColorCode::Scope::String)].Color(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
    }

    void ColorCodeEditor::keywordColorChanged(
        winrt::WinUINamespace::UI::Xaml::DependencyObject const&,
        winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        s_brushes[static_cast<size_t>(ColorCode::Scope::Keyword)].Color(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
    }

    void ColorCodeEditor::typeColorChanged(
        winrt::WinUINamespace::UI::Xaml::DependencyObject const&,
        winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        s_brushes[static_cast<size_t>(ColorCode::Scope::Type)].Color(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
    }

    void ColorCodeEditor::preprocessorColorChanged(
        winrt::WinUINamespace::UI::Xaml::DependencyObject const&,
        winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        s_brushes[static_cast<size_t>(ColorCode::Scope::Preprocessor)].Color(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
    }

    void ColorCodeEditor::operatorColorChanged(
        winrt::WinUINamespace::UI::Xaml::DependencyObject const&,
        winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        s_brushes[static_cast<size_t>(ColorCode::Scope::Operator)].Color(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
    }

    void ColorCodeEditor::identifierColorChanged(
        winrt::WinUINamespace::UI::Xaml::DependencyObject const&,
        winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        s_brushes[static_cast<size_t>(ColorCode::Scope::Identifier)].Color(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
    }

    void ColorCodeEditor::plainTextColorChanged(
        winrt::WinUINamespace::UI::Xaml::DependencyObject const&,
        winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        s_brushes[static_cast<size_t>(ColorCode::Scope::PlainText)].Color(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
    }

    void ColorCodeEditor::functionColorChanged(
        winrt::WinUINamespace::UI::Xaml::DependencyObject const&,
        winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        s_brushes[static_cast<size_t>(ColorCode::Scope::Function)].Color(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
    }

    void ColorCodeEditor::namespaceColorChanged(
        winrt::WinUINamespace::UI::Xaml::DependencyObject const&,
        winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        s_brushes[static_cast<size_t>(ColorCode::Scope::Namespace)].Color(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
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
            [this](ColorCode::Token token)
            {
                DebugToken(token, m_code);

                winrt::WinUINamespace::UI::Xaml::Documents::Run run;
                run.Text(winrt::hstring{ m_code.data() + token.start, static_cast<winrt::hstring::size_type>(token.length) });
                run.Foreground(s_brushes[static_cast<size_t>(token.scope)]);
                m_highlighted.Append(run);
            }
        );
    }
}

