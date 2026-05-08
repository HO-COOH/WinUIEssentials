#pragma once

#include "TableColumn.g.h"
#include "include/EnsureDependencyProperty.hpp"

namespace winrt::PackageRoot::implementation
{
    struct TableColumn : TableColumnT<TableColumn>, EnsureDependencyProperty<TableColumn>
    {
        TableColumn() = default;
        static void EnsureDependencyProperties();

        winrt::hstring StringContent();
        void StringContent(winrt::hstring const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty StringContentProperty();

    private:
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_stringContentProperty{ nullptr };
        static void onStringContentChanged(
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
