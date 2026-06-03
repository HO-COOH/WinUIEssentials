#pragma once

#include "ColorCodeEditor.g.h"
#include <EnsureDependencyProperty.hpp>

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

        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_commentColorProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_stringColorProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_keywordColorProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_typeColorProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_preprocessorColorProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_operatorColorProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_identifierColorProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_plainTextColorProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_functionColorProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_namespaceColorProperty = nullptr;

        static inline std::array<winrt::WinUINamespace::UI::Xaml::Media::SolidColorBrush, 10> s_brushes
        {
            nullptr, nullptr, nullptr, nullptr, nullptr,
            nullptr, nullptr, nullptr, nullptr, nullptr
        };

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
