#pragma once

#include "TableColumn.g.h"
#include "include/EnsureDependencyProperty.hpp"
#include "TableColumnData.h"

namespace winrt::PackageRoot::implementation
{
    struct TableColumn : TableColumnT<TableColumn>, EnsureDependencyProperty<TableColumn>
    {
        TableColumn() = default;
        static void EnsureDependencyProperties();

        winrt::hstring StringContent();
        void StringContent(winrt::hstring const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty StringContentProperty();

        bool SortEnabled();
        void SortEnabled(bool value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty SortEnabledProperty();

        TableColumnData m_data;
    private:
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_stringContentProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_sortEnabledProperty{ nullptr };
        
        static void onStringContentChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onSortEnabledChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct TableColumn : TableColumnT<TableColumn, implementation::TableColumn>
    {
    };
}
