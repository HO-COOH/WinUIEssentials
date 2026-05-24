#include "pch.h"
#include "TableOverlayManager.h"
#include "Table.h"
#include "TableD2DContent.h"
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
	if (iter == state.slots.end())
	{
		//find a recyclable slot
		iter = std::ranges::find_if(state.slots, [](CellSlot const& cell) {return cell.row == -1; });
		return iter != state.slots.end() ? *iter : createSlot(state, column);
	}
	return *iter;
}

void TableOverlayManager::recycleControls(float targetY)
{
	auto const [beforeScrollFirst, beforeScrollLast] = m_table.m_d2dContent.GetVisibleRowRangeInclusive(m_table.m_d2dContent.ScrollOffsetY());
	auto const [afterScrollfirst, afterScrollLast] = m_table.m_d2dContent.GetVisibleRowRangeInclusive(targetY);

	auto const first = (std::min)(beforeScrollFirst, afterScrollfirst);
	auto const last = (std::max)(beforeScrollLast, afterScrollLast);
	for (auto& column : m_columns)
	{
		for (auto& slot : column.slots)
		{
			if (slot.row >= 0 && (slot.row < first || slot.row > last))
				slot.row = -1;
		}
	}
}

void TableOverlayManager::SetCellContent(int row, int column, winrt::Windows::Foundation::IInspectable const& cellObject)
{
	auto const& itemTemplate = m_table.m_columns->m_data[column]->m_data.m_itemTemplate;
	if (!itemTemplate)
		return;

	auto& widthManager = m_table.m_d2dContent.m_columnWidthManager;
	if (column >= static_cast<int>(widthManager.NumColumns()))
		return;

	auto& columnState = ensureColumn(column);

	//cache cell data
	if (row >= static_cast<int>(columnState.rowDataCache.size()))
		columnState.rowDataCache.resize(row + 1);
	columnState.rowDataCache[row] = cellObject;

	auto& slot = getOrCreateFreeSlot(columnState, row, column);
	bool const recycled = std::exchange(slot.row, row) != row;
	if (recycled)
	{
		slot.element.DataContext(cellObject);
		m_cellExpression.SetReferenceParameter(L"ColumnProperty", columnState.ColumnProperty);
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

void TableOverlayManager::rebindVisibleRows(float targetY)
{
	auto const [first, last] = m_table.m_d2dContent.GetVisibleRowRangeInclusive(targetY);
	for (int col = 0; col < m_columns.size(); ++ col)
	{
		if (!m_columns[col].ColumnProperty)
			continue;

		int const rEnd = (std::min)(last, static_cast<int>(m_columns[col].rowDataCache.size()) - 1);
		for (int r = first; r <= rEnd; ++r)
		{
			if (auto const& cached = m_columns[col].rowDataCache[r])
				SetCellContent(r, col, cached);
		}
	}
}

void TableOverlayManager::OnMouseScroll(float targetY)
{
	recycleControls(targetY);
	rebindVisibleRows(targetY);
	m_scrollAnimation.InsertKeyFrame(1.f, targetY, m_scrollEasingFunction);
	TableProperty.StartAnimation(L"ScrollOffsetY", m_scrollAnimation);
}

void TableOverlayManager::OnScrollYChanged(float newScrollY)
{
	recycleControls(newScrollY);
	rebindVisibleRows(newScrollY);
	TableProperty.InsertScalar(L"ScrollOffsetY", newScrollY);
}

void TableOverlayManager::OnScrollXChanged(float newScrollX)
{
	TableProperty.InsertScalar(L"ScrollOffsetX", newScrollX);
}

void TableOverlayManager::InvalidateRows(int startRow, int endRow)
{
	for (auto& column : m_columns | std::views::filter([](ColumnState const& column) { return static_cast<bool>(column.ColumnProperty); }))
	{
		int const cacheEnd = (std::min)(endRow, static_cast<int>(column.rowDataCache.size()) - 1);
		if (cacheEnd >= startRow)
		{
			std::ranges::fill(
				column.rowDataCache.begin() + startRow,
				column.rowDataCache.begin() + cacheEnd + 1,
				nullptr
			);
		}

		for (auto& slot : column.slots | std::views::filter([&](CellSlot const& slot) { return slot.row >= startRow && slot.row <= endRow; }))
			slot.row = -1;
	}
}
