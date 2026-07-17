#pragma once

#include "DefaultTableHeaderContextMenu.g.h"

namespace winrt::PackageRoot::implementation
{
    struct Table;

    struct DefaultTableHeaderContextMenu : DefaultTableHeaderContextMenuT<DefaultTableHeaderContextMenu>
    {
        DefaultTableHeaderContextMenu() = default;
        DefaultTableHeaderContextMenu(Table* table, int columnIndex);

        void InitializeComponent();

        bool IsSortAscendingEnabled();
        bool IsSortDescendingEnabled();
		bool IsClearSortEnabled();

        void SortAscend_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const& e);
        void SortDescend_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const& e);
		void ClearSorting_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const& e);
    private:
        //only sort string, numbers etc. If the column is IInspectable, try unbox it to IPropertyValue
        bool isSortable() const;
		int m_columnIndex{ -1 };
        Table* m_table{ nullptr };
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct DefaultTableHeaderContextMenu : DefaultTableHeaderContextMenuT<DefaultTableHeaderContextMenu, implementation::DefaultTableHeaderContextMenu>
    {
    };
}
