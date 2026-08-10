#pragma once

#include "CodeWindowPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct CodeWindowPage : CodeWindowPageT<CodeWindowPage>
    {
        CodeWindowPage() = default;

        CodeWindowPage(
            winrt::hstring const& title,
            winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> const& codeItems
        );

        winrt::hstring WindowTitle() const { return m_title; }

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> CodeItems() const
        {
            return m_codeItems;
        }

        void Page_Loaded(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Windows::UI::Xaml::RoutedEventArgs const& args
        );

    private:
        winrt::hstring m_title;
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> m_codeItems{ nullptr };
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct CodeWindowPage : CodeWindowPageT<CodeWindowPage, implementation::CodeWindowPage>
    {
    };
}
