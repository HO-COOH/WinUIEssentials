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

		winrt::WinUINamespace::UI::Xaml::DataTemplate ItemTemplate();
		void ItemTemplate(winrt::WinUINamespace::UI::Xaml::DataTemplate const& value);
		static winrt::WinUINamespace::UI::Xaml::DependencyProperty ItemTemplateProperty();

		winrt::WinUINamespace::UI::Xaml::DataTemplate EditTemplate();
		void EditTemplate(winrt::WinUINamespace::UI::Xaml::DataTemplate const& value);
		static winrt::WinUINamespace::UI::Xaml::DependencyProperty EditTemplateProperty();

        bool SortEnabled();
        void SortEnabled(bool value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty SortEnabledProperty();

        bool IsResizable();
		void IsResizable(bool value);
		static winrt::WinUINamespace::UI::Xaml::DependencyProperty IsResizableProperty();

        constexpr double MinWidth() { return m_minWidth; }
		constexpr void MinWidth(double value) { m_minWidth = static_cast<float>(value); }

		constexpr double MaxWidth() { return m_maxWidth; }
		constexpr void MaxWidth(double value) { m_maxWidth = static_cast<float>(value); }

        float m_minWidth = -1.f;
        float m_maxWidth = -1.f;

        TableColumnData m_data;
    private:

        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_stringContentProperty{ nullptr };
		static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_itemTemplateProperty{ nullptr };
		static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_editTemplateProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_sortEnabledProperty{ nullptr };
		static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_isResizableProperty{ nullptr };

        static void onStringContentChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onItemTemplateChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
		);
        static void onEditTemplateChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onSortEnabledChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onIsResizableChanged(
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
