#include "pch.h"
#include "EditControlOverlay.h"
#include "TableD2DContent.h"

//A TextBox by default has UpdateSourceTrigger=LostFocus, and when we remove it, it doesn't lose focus yet
static void flushTextBoxBindings(winrt::WinUINamespace::UI::Xaml::DependencyObject const& element)
{
	if (auto textBox = element.try_as<winrt::WinUINamespace::UI::Xaml::Controls::TextBox>())
	{
		if (auto binding = textBox.GetBindingExpression(winrt::WinUINamespace::UI::Xaml::Controls::TextBox::TextProperty());
			binding && binding.ParentBinding().Mode() == winrt::WinUINamespace::UI::Xaml::Data::BindingMode::TwoWay)
			binding.UpdateSource();
		return;
	}

	//in case there is a TextBox inside a DataTemplate somewhere, find it recursively
	auto const count = winrt::WinUINamespace::UI::Xaml::Media::VisualTreeHelper::GetChildrenCount(element);
	for (int32_t i = 0; i < count; ++i)
		flushTextBoxBindings(winrt::WinUINamespace::UI::Xaml::Media::VisualTreeHelper::GetChild(element, i));
}

winrt::WinUINamespace::UI::Xaml::FrameworkElement EditControlOverlay::MakeControl(
	winrt::WinUINamespace::UI::Xaml::DataTemplate const& dataTemplate,
	winrt::PackageRoot::TableCellDataWrapper const& dataContext,
	bool isString,
	int row,
	int sourceRow,
	int column
)
{
	auto control = dataTemplate.LoadContent().as<winrt::WinUINamespace::UI::Xaml::FrameworkElement>();
	control.DataContext(dataContext);
	m_editControl = control;
	m_dataContext = dataContext;
	m_previousValue = dataContext.Value();
	m_editingRow = row;
	m_editingSourceRow = sourceRow;
	m_editingColumn = column;
	m_isString = isString;
	if (isString)
		m_previousContent = winrt::unbox_value<winrt::hstring>(m_previousValue);
	return control;
}

EndEditResult EditControlOverlay::Remove(TableD2DContent& d2dContent)
{
	EndEditResult result
	{
		.displayRow = m_editingRow,
		.sourceRow = m_editingSourceRow,
		.column = m_editingColumn,
		.isString = m_isString
	};

	auto const control = m_editControl.get();
	m_editControl = nullptr;
	if (control)
		flushTextBoxBindings(control);

	//Value's setter has already forwarded any edit to ITableData::SetData
	result.value = std::exchange(m_dataContext, nullptr).Value();
	if (m_isString)
	{
		auto const content = result.value.try_as<winrt::hstring>();
		result.changed = content ? *content != m_previousContent : result.value != m_previousValue;
		d2dContent.DrawPartialCell(m_editingRow, m_editingColumn, content ? *content : m_previousContent);
	}
	else
		result.changed = result.value != m_previousValue;

	m_previousValue = nullptr;
	return result;
}

EditControlOverlay::operator bool() const
{
	return static_cast<bool>(m_editControl.get());
}
