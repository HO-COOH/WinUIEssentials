#pragma once

#include "CodeWindow.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct CodeWindow : CodeWindowT<CodeWindow>
    {
        CodeWindow() = default;
        CodeWindow(winrt::hstring const& title, winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> const& codeItems);

        winrt::hstring WindowTitle();
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> CodeItems();

        winrt::hstring m_title;
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> m_codeItems{ nullptr };
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct CodeWindow : CodeWindowT<CodeWindow, implementation::CodeWindow>
    {
    };
}
