#pragma once

#include "ContextMenuRequestedEventArgs.g.h"

namespace winrt::PackageRoot::implementation
{
    struct ContextMenuRequestedEventArgs : ContextMenuRequestedEventArgsT<ContextMenuRequestedEventArgs>
    {
        ContextMenuRequestedEventArgs() = default;
        ContextMenuRequestedEventArgs(
            int rowIndex,
            int columnIndex,
            winrt::Windows::Foundation::IInspectable const& dataContext = nullptr
        );

        constexpr int RowIndex() { return m_rowIndex; }
        constexpr int ColumnIndex() { return m_columnIndex; }
        winrt::Windows::Foundation::IInspectable DataContext();

        winrt::WinUINamespace::UI::Xaml::Controls::MenuFlyout ContextMenu();
        void ContextMenu(winrt::WinUINamespace::UI::Xaml::Controls::MenuFlyout const& value);

        constexpr bool Handled() { return m_handled; }
        constexpr void Handled(bool value) { m_handled = value; }

        winrt::Windows::Foundation::IInspectable m_dataContext{ nullptr };
    private:
        int m_rowIndex{ -1 };
        int m_columnIndex{ -1 };
        winrt::WinUINamespace::UI::Xaml::Controls::MenuFlyout m_contextMenu{ nullptr };
        bool m_handled{ false };
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct ContextMenuRequestedEventArgs : ContextMenuRequestedEventArgsT<ContextMenuRequestedEventArgs, implementation::ContextMenuRequestedEventArgs>
    {
    };
}
