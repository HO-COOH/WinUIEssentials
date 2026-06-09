#pragma once
#include <variant>

struct TableColumnData
{
	std::variant<winrt::hstring, winrt::Windows::Foundation::IInspectable> m_content;
	winrt::WinUINamespace::UI::Xaml::DataTemplate m_itemTemplate{ nullptr };
	winrt::WinUINamespace::UI::Xaml::DataTemplate m_editTemplate{ nullptr };
	winrt::WinUINamespace::UI::Xaml::HorizontalAlignment m_horizontalAlignment{ winrt::WinUINamespace::UI::Xaml::HorizontalAlignment::Left };
	bool m_sortEnabled{};
	bool m_isResizable = true;
};