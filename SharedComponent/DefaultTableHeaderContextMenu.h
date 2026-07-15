#pragma once

#include "DefaultTableHeaderContextMenu.g.h"

namespace winrt::PackageRoot::implementation
{
    struct Table;

    struct DefaultTableHeaderContextMenu : DefaultTableHeaderContextMenuT<DefaultTableHeaderContextMenu>
    {
        DefaultTableHeaderContextMenu() = default;
        DefaultTableHeaderContextMenu(Table* table);

        void InitializeComponent();

        bool IsSortAscendingEnabled();
        bool IsSortDescendingEnabled();

        void SortAscend_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const& e);
        void SortDescend_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const& e);
    private:
        Table* m_table{ nullptr };
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct DefaultTableHeaderContextMenu : DefaultTableHeaderContextMenuT<DefaultTableHeaderContextMenu, implementation::DefaultTableHeaderContextMenu>
    {
    };
}
