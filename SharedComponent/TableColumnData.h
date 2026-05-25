#pragma once

struct TableColumnData
{
	winrt::hstring m_stringContent;
	winrt::WinUINamespace::UI::Xaml::DataTemplate m_itemTemplate{ nullptr };
	winrt::WinUINamespace::UI::Xaml::DataTemplate m_editTemplate{ nullptr };
	bool m_sortEnabled;
};