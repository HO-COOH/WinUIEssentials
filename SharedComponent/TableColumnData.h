#pragma once

struct TableColumnData
{
	winrt::hstring m_stringContent;
	winrt::WinUINamespace::UI::Xaml::DataTemplate m_itemTemplate{ nullptr };
	winrt::WinUINamespace::UI::Xaml::DataTemplate m_editTemplate{ nullptr };
	winrt::WinUINamespace::UI::Xaml::HorizontalAlignment m_horizontalAlignment{ winrt::WinUINamespace::UI::Xaml::HorizontalAlignment::Left };
	bool m_sortEnabled{};
	bool m_isResizable = true;
};