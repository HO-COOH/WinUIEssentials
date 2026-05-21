#include "pch.h"
#include "TableOverlayManager.h"
#include "Table.h"

TableOverlayManager::TableOverlayManager(winrt::PackageRoot::implementation::Table& table) :
	m_table{ table }
{
}

void TableOverlayManager::OnInitializedComponent()
{
	m_canvasChildren = m_table.ControlsOverlay().Children();
}

void TableOverlayManager::SetCellContent(int row, int column, winrt::Windows::Foundation::IInspectable const& cellObject)
{
	auto const& column_obj = m_table.m_columns->m_data[column];
	if (!column_obj || !column_obj->m_data.m_itemTemplate)
		return;

	auto& widthManager = m_table.m_d2dContent.m_columnWidthManager;
	if (column >= static_cast<int>(widthManager.NumColumns()))
		return;

	auto cellContent = column_obj->m_data.m_itemTemplate
		.LoadContent()
		.as<winrt::WinUINamespace::UI::Xaml::FrameworkElement>();
	cellContent.DataContext(cellObject);
	m_canvasChildren.Append(cellContent);

	//we use composition to translate the control
}
