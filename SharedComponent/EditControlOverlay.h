#pragma once
#include <variant>

class TableD2DContent;

class EditControlOverlay
{
	int m_editingRow{ -1 };
	int m_editingColumn{ -1 };
	winrt::hstring m_previousContent;
	winrt::weak_ref<winrt::WinUINamespace::UI::Xaml::FrameworkElement> m_editControl;
	bool m_isString{};
public:
	[[nodiscard]] winrt::WinUINamespace::UI::Xaml::FrameworkElement MakeControl(
		winrt::WinUINamespace::UI::Xaml::DataTemplate const& dataTemplate,
		winrt::Windows::Foundation::IInspectable const& data,
		bool isString,
		int row,
		int column
	);

	//return previous constructed control for removing from Canvas
	[[nodiscard]] winrt::WinUINamespace::UI::Xaml::FrameworkElement Remove(TableD2DContent& d2dContent);
	operator bool() const;
};