#include "pch.h"
#include "EditControlOverlay.h"
#include "TableD2DContent.h"

winrt::WinUINamespace::UI::Xaml::FrameworkElement EditControlOverlay::MakeControl(
	winrt::WinUINamespace::UI::Xaml::DataTemplate const& dataTemplate, 
	winrt::Windows::Foundation::IInspectable const& data,
	bool isString,
	int row,
	int column
)
{
	auto control = dataTemplate.LoadContent().as<winrt::WinUINamespace::UI::Xaml::FrameworkElement>();
	control.DataContext(data);
	m_editControl = control;
	m_editingRow = row;
	m_editingColumn = column;
	m_isString = isString;
	if (isString)
		m_previousContent = winrt::unbox_value<winrt::hstring>(data);
	return control;
}

winrt::WinUINamespace::UI::Xaml::FrameworkElement EditControlOverlay::Remove(TableD2DContent& d2dContent)
{
	auto control = m_editControl.get();
	m_editControl = nullptr;

	if (m_isString)
		d2dContent.DrawPartialCell(m_editingRow, m_editingColumn, m_previousContent);
	return control;
}

EditControlOverlay::operator bool() const
{
	return static_cast<bool>(m_editControl.get());
}
