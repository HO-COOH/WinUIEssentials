#pragma once

#include "ColorCodeEditor.g.h"
#include <EnsureDependencyProperty.hpp>
#include "Scope.h"

namespace winrt::PackageRoot::implementation
{
    struct ColorCodeEditor : ColorCodeEditorT<ColorCodeEditor>, EnsureDependencyProperty<ColorCodeEditor>
    {
        static void EnsureDependencyProperties();
        ColorCodeEditor();

        winrt::hstring Code();
        void Code(winrt::hstring const& value);

        winrt::PackageRoot::Language CodeLanguage();
        void CodeLanguage(winrt::PackageRoot::Language value);

        winrt::WinUINamespace::UI::Xaml::Documents::InlineCollection Highlighted();

        winrt::Windows::UI::Color CommentColor();
        void CommentColor(winrt::Windows::UI::Color value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty CommentColorProperty();

        winrt::Windows::UI::Color StringColor();
        void StringColor(winrt::Windows::UI::Color value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty StringColorProperty();

        winrt::Windows::UI::Color KeywordColor();
        void KeywordColor(winrt::Windows::UI::Color value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty KeywordColorProperty();

        winrt::Windows::UI::Color TypeColor();
        void TypeColor(winrt::Windows::UI::Color value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty TypeColorProperty();

        winrt::Windows::UI::Color PreprocessorColor();
        void PreprocessorColor(winrt::Windows::UI::Color value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty PreprocessorColorProperty();

        winrt::Windows::UI::Color OperatorColor();
        void OperatorColor(winrt::Windows::UI::Color value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty OperatorColorProperty();

        winrt::Windows::UI::Color IdentifierColor();
        void IdentifierColor(winrt::Windows::UI::Color value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty IdentifierColorProperty();

        winrt::Windows::UI::Color PlainTextColor();
        void PlainTextColor(winrt::Windows::UI::Color value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty PlainTextColorProperty();

        winrt::Windows::UI::Color FunctionColor();
        void FunctionColor(winrt::Windows::UI::Color value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty FunctionColorProperty();

        winrt::Windows::UI::Color NamespaceColor();
        void NamespaceColor(winrt::Windows::UI::Color value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty NamespaceColorProperty();

        static winrt::hstring GetLineGutterFromCode(winrt::hstring const& code);
    private:
		winrt::hstring m_code;
        winrt::PackageRoot::Language m_language{ winrt::PackageRoot::Language::Undefined };
        winrt::WinUINamespace::UI::Xaml::Documents::InlineCollection m_highlighted{ nullptr };

        static winrt::WinUINamespace::UI::Xaml::DependencyProperty m_commentColorProperty;
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty m_stringColorProperty;
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty m_keywordColorProperty;
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty m_typeColorProperty;
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty m_preprocessorColorProperty;
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty m_operatorColorProperty;
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty m_identifierColorProperty;
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty m_plainTextColorProperty;
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty m_functionColorProperty;
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty m_namespaceColorProperty;

#if defined Build_WinUIExample
        static inline std::array<winrt::WinUINamespace::UI::Xaml::Media::SolidColorBrush, static_cast<size_t>(ColorCode::Scope::MaxValue_)> s_brushes
        {
            nullptr, nullptr, nullptr, nullptr, nullptr,
            nullptr, nullptr, nullptr, nullptr, nullptr
        };
#endif
        static std::array<winrt::WinUINamespace::UI::Xaml::Media::SolidColorBrush, static_cast<size_t>(ColorCode::Scope::MaxValue_)>& brushes();


        static void commentColorChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void stringColorChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void keywordColorChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void typeColorChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void preprocessorColorChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void operatorColorChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void identifierColorChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void plainTextColorChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void functionColorChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void namespaceColorChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        void renderToRichTextBlock();
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct ColorCodeEditor : ColorCodeEditorT<ColorCodeEditor, implementation::ColorCodeEditor>
    {
    };
}
