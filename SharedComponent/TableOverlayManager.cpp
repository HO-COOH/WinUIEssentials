#include "pch.h"
#include "TableOverlayManager.h"
#include "Table.h"
#include "TableConstants.hpp"
#include <ranges>

TableOverlayManager::TableOverlayManager(winrt::PackageRoot::implementation::Table& table) :
	m_compositor{ winrt::WinUINamespace::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(table).Compositor() },
	TableProperty{ m_compositor.CreatePropertySet() },
	m_scrollEasingFunction{ winrt::WinUINamespace::UI::Composition::CompositionEasingFunction::CreatePowerEasingFunction(m_compositor, winrt::WinUINamespace::UI::Composition::CompositionEasingFunctionMode::Out, 5.f) },
	m_scrollAnimation{ m_compositor.CreateScalarKeyFrameAnimation() },
	m_cellExpression{ m_compositor.CreateExpressionAnimation(TranslationExpression) },
	m_table{ table }
{
	TableProperty.InsertScalar(L"ScrollOffsetX", 0.f);
	TableProperty.InsertScalar(L"ScrollOffsetY", 0.f);
	m_scrollAnimation.Duration(TableConstants::SmoothScrollDuration);
	m_cellExpression.SetReferenceParameter(L"TableProperty", TableProperty);
}

void TableOverlayManager::OnInitializedComponent()
{
	auto const canvas = m_table.ControlsOverlay();
	m_children = canvas.Children();

	//clip canvas to prevent cell content from showing in header
	winrt::WinUINamespace::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(canvas)
		.Clip(m_compositor.CreateInsetClip(0.f, TableConstants::HeaderHeight, 0.f, 0.f));
}

TableOverlayManager::ColumnState& TableOverlayManager::ensureColumn(int column)
{
	if (static_cast<int>(m_columns.size()) <= column)
		m_columns.resize(column + 1);

	auto& state = m_columns[column];
	if (!state.ColumnProperty)
	{
		state.ColumnProperty = m_compositor.CreatePropertySet();
		state.ColumnProperty.InsertScalar(L"CellX", m_table.m_d2dContent.m_columnWidthManager.SumColumnWidth(column, 0));
	}
	return state;
}

TableOverlayManager::CellSlot& TableOverlayManager::createSlot(ColumnState& state, int column)
{
	auto cellContent = m_table.m_columns->m_data[column]->m_data.m_itemTemplate
		.LoadContent()
		.as<winrt::WinUINamespace::UI::Xaml::FrameworkElement>();

	winrt::WinUINamespace::UI::Xaml::Hosting::ElementCompositionPreview::SetIsTranslationEnabled(cellContent, true);

	m_children.Append(cellContent);
	state.slots.push_back(CellSlot{ cellContent, -1 });
	return state.slots.back();
}

TableOverlayManager::CellSlot& TableOverlayManager::getOrCreateFreeSlot(ColumnState& state, int row, int column)
{
	auto iter = std::ranges::find_if(state.slots, [row](CellSlot const& cell) {return cell.row == row; });
	return iter != state.slots.end() ? *iter : createSlot(state, column);
}

void TableOverlayManager::SetCellContent(int row, int column, winrt::Windows::Foundation::IInspectable const& cellObject)
{
	auto const& itemTemplate = m_table.m_columns->m_data[column]->m_data.m_itemTemplate;
	if (!itemTemplate)
		return;

	auto& widthManager = m_table.m_d2dContent.m_columnWidthManager;
	if (column >= static_cast<int>(widthManager.NumColumns()))
		return;

	auto& state = ensureColumn(column);
	auto& slot = getOrCreateFreeSlot(state, row, column);

	bool const recycled = std::exchange(slot.row, row) != row;
	slot.element.DataContext(cellObject);

	if (recycled)
	{
		m_cellExpression.SetReferenceParameter(L"ColumnProperty", state.ColumnProperty);
		float const cellY = TableConstants::HeaderHeight + row * TableConstants::RowHeight;
		m_cellExpression.SetScalarParameter(L"cellY", cellY);

		winrt::WinUINamespace::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(slot.element).StartAnimation(L"Translation.XY", m_cellExpression);
	}
}

void TableOverlayManager::OnColumnResized(int resizedColumn)
{
	auto& widthManager = m_table.m_d2dContent.m_columnWidthManager;
	int const numColumns = static_cast<int>(m_columns.size());
	for (int c = resizedColumn + 1; c < numColumns; ++c)
	{
		if (auto& columnProperty = m_columns[c].ColumnProperty)
			columnProperty.InsertScalar(L"CellX", widthManager.SumColumnWidth(c, 0));
	}
}

void TableOverlayManager::OnMouseScroll(float targetY)
{
	m_scrollAnimation.InsertKeyFrame(1.f, targetY, m_scrollEasingFunction);
	TableProperty.StartAnimation(L"ScrollOffsetY", m_scrollAnimation);
}

void TableOverlayManager::OnScrollYChanged(float newScrollY)
{
	TableProperty.InsertScalar(L"ScrollOffsetY", newScrollY);
}

void TableOverlayManager::OnScrollXChanged(float newScrollX)
{
	TableProperty.InsertScalar(L"ScrollOffsetX", newScrollX);
}
