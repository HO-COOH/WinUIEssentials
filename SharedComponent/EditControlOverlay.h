#pragma once
#include <variant>

class TableD2DContent;

class EditControlOverlay
{
	int m_editingRow{ -1 };
	int m_editingColumn{ -1 };
	winrt::Windows::Foundation::IInspectable m_previousContent{ nullptr };
	bool m_isString{};
	winrt::weak_ref<winrt::WinUINamespace::UI::Xaml::FrameworkElement> m_editControl;
public:
	[[nodiscard]] winrt::WinUINamespace::UI::Xaml::FrameworkElement MakeControl(
		winrt::WinUINamespace::UI::Xaml::DataTemplate const& dataTemplate,
		winrt::Windows::Foundation::IInspectable const& data,
		bool isString,
		int row,
		int column
	);

	[[nodiscard]] winrt::WinUINamespace::UI::Xaml::FrameworkElement Remove(TableD2DContent& d2dContent);
	operator bool() const;
};