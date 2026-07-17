#pragma once

#include "DefaultTableContextMenu.g.h"

namespace winrt::PackageRoot::implementation
{
    struct Table;

    struct DefaultTableContextMenu : DefaultTableContextMenuT<DefaultTableContextMenu>
    {
        DefaultTableContextMenu() = default;
        DefaultTableContextMenu(Table* table, int row, int column);

        void CopyCell_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const& e);
        void CopyRow_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const& e);

    private:
        Table* m_table{ nullptr };
        int m_row{ -1 };
        int m_column{ -1 };
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct DefaultTableContextMenu : DefaultTableContextMenuT<DefaultTableContextMenu, implementation::DefaultTableContextMenu>
    {
    };
}
