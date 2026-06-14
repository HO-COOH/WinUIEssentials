#include "pch.h"
#include "TableOverlayManager.h"
#include "Table.h"
#include "TableD2DContent.h"
#include "TableConstants.hpp"
#include "TableColumnCollection.h"
#include <ranges>
#include <variant>

TableOverlayManager::TableOverlayManager(winrt::PackageRoot::implementation::Table& table) :
	m_compositor{ winrt::WinUINamespace::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(table).Compositor() },
	TableProperty{ m_compositor.CreatePropertySet() },
	m_scrollEasingFunction{ winrt::WinUINamespace::UI::Composition::CompositionEasingFunction::CreatePowerEasingFunction(m_compositor, winrt::WinUINamespace::UI::Composition::CompositionEasingFunctionMode::Out, 5.f) },
	m_scrollAnimation{ m_compositor.CreateScalarKeyFrameAnimation() },
	m_cellExpression{ m_compositor.CreateExpressionAnimation(TranslationExpression) },
	m_headerExpression{ m_compositor.CreateExpressionAnimation(HeaderTranslationExpression) },
	m_table{ table }
{
	TableProperty.InsertScalar(L"ScrollOffsetX", 0.f);
	TableProperty.InsertScalar(L"ScrollOffsetY", 0.f);
	m_scrollAnimation.Duration(TableConstants::SmoothScrollDuration);
	m_cellExpression.SetReferenceParameter(L"TableProperty", TableProperty);
	m_headerExpression.SetReferenceParameter(L"TableProperty", TableProperty);
}

void TableOverlayManager::OnInitializedComponent()
{
	m_headerChildren = m_table.HeaderControlsOverlay().Children();

	auto canvas = m_table.ControlsOverlay();
	m_children = canvas.Children();
}

float TableOverlayManager::cellLeftOffset() const
{
	if (!m_cellLeadingOffset)
	{
		auto const& tableData = m_table.m_tableProperty;
		auto const verticalLineSpace = tableData.m_verticalLineColor.a > 0.f ? tableData.m_verticalLineThickness : 0.f;
		m_cellLeadingOffset = verticalLineSpace + static_cast<float>(tableData.m_contentPadding.Left);
	}
	return *m_cellLeadingOffset;
}

float TableOverlayManager::cellContentWidth(int column) const
{
	auto const columnWidth = m_table.m_d2dContent.m_columnWidthManager.Get(column);
	auto const padRight = static_cast<float>(m_table.m_tableProperty.m_contentPadding.Right);
	return (std::max)(0.f, columnWidth - cellLeftOffset() - padRight);
}

TableOverlayManager::ColumnState& TableOverlayManager::ensureColumn(int column)
{
	if (static_cast<int>(m_columns.size()) <= column)
		m_columns.resize(column + 1);

	auto& state = m_columns[column];
	if (!state.ColumnProperty)
	{
		state.ColumnProperty = m_compositor.CreatePropertySet();
		state.ColumnProperty.InsertScalar(L"CellX", m_table.m_d2dContent.m_columnWidthManager.SumColumnWidth(column, 0) + cellLeftOffset());
	}
	return state;
}

TableOverlayManager::CellSlot& TableOverlayManager::createSlot(ColumnState& state, int column)
{
	auto& tableColumn = *m_table.m_columns->m_data[column];
	auto& columnData = tableColumn.m_data;
	auto cellContent = columnData.m_itemTemplate
		.LoadContent()
		.as<winrt::WinUINamespace::UI::Xaml::FrameworkElement>();

	winrt::WinUINamespace::UI::Xaml::Hosting::ElementCompositionPreview::SetIsTranslationEnabled(cellContent, true);

	cellContent.HorizontalAlignment(tableColumn.HorizontalAlignment());
	cellContent.Width(cellContentWidth(column));

	if (!columnData.m_editTemplate)
		cellContent.IsHitTestVisible(false); //make the control read-only

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

void TableOverlayManager::OnLoaded()
{
	auto const headerHeight = m_table.m_d2dContent.m_tableHeight.HeaderRowHeight();

	//clip canvas to prevent cell content from showing in header. Deferred to
	//Loaded so the resolved header height (font + padding) is available.
	auto canvas = m_table.ControlsOverlay();
	winrt::WinUINamespace::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(canvas)
		.Clip(m_compositor.CreateInsetClip(0.f, headerHeight, 0.f, 0.f));

	m_headerChildren.Clear();

	for (auto& state : m_columns)
		state.headerElement = nullptr;

	auto const& columns = m_table.m_columns->m_data;
	for (size_t col = 0; col < columns.size(); ++col)
	{
		auto* content = std::get_if<winrt::Windows::Foundation::IInspectable>(&columns[col]->m_data.m_content);
		if (!content || !*content)
			continue;

		auto control = content->try_as<winrt::WinUINamespace::UI::Xaml::FrameworkElement>();
		if (!control)
			continue;

		winrt::WinUINamespace::UI::Xaml::Hosting::ElementCompositionPreview::SetIsTranslationEnabled(control, true);
		control.HorizontalAlignment(columns[col]->HorizontalAlignment());
		control.Width(cellContentWidth(static_cast<int>(col)));
		control.Height(headerHeight);
		m_headerChildren.Append(control);

		auto& state = ensureColumn(static_cast<int>(col));
		state.headerElement = control;
		m_headerExpression.SetReferenceParameter(L"ColumnProperty", state.ColumnProperty);
		winrt::WinUINamespace::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(control).StartAnimation(L"Translation.XY", m_headerExpression);
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
		auto const& tableHeight = m_table.m_d2dContent.m_tableHeight;
		float const cellY = tableHeight.HeaderRowHeight() + row * tableHeight.ContentRowHeight();
		m_cellExpression.SetScalarParameter(L"cellY", cellY);
		winrt::WinUINamespace::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(slot.element).StartAnimation(L"Translation.XY", m_cellExpression);
	}
}

void TableOverlayManager::OnColumnResized(int resizedColumn)
{
	int const numColumns = static_cast<int>(m_columns.size());

	if (resizedColumn < 0 || resizedColumn >= numColumns)
		return;

	auto& widthManager = m_table.m_d2dContent.m_columnWidthManager;
	auto const leading = cellLeftOffset();

	//change xaml control width of the column
	auto const newWidth = cellContentWidth(resizedColumn);
	for (auto& slot : m_columns[resizedColumn].slots)
		slot.element.Width(newWidth);
	if (auto& header = m_columns[resizedColumn].headerElement)
		header.Width(newWidth);

	for (int c = resizedColumn + 1; c < numColumns; ++c)
	{
		if (auto& columnProperty = m_columns[c].ColumnProperty)
			columnProperty.InsertScalar(L"CellX", widthManager.SumColumnWidth(c, 0) + leading);
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

void TableOverlayManager::BeginEdit(int row, int column)
{
	auto const& columnData = m_table.m_columns->m_data[column]->m_data;
	if (!columnData.m_editTemplate)
		return;

	auto const hasItemTemplate = static_cast<bool>(columnData.m_itemTemplate);
	auto editControl = m_editControl.MakeControl(
		columnData.m_editTemplate, 
		 hasItemTemplate?  
			m_columns[column].rowDataCache[row] : 
			winrt::box_value(m_table.m_d2dContent.m_textLayoutCache.GetCellContent(row, column)),
		!hasItemTemplate,
		row, 
		column
	);

	if (!hasItemTemplate)
	{
		//clear d2dContent cell if is plain string
		m_table.m_d2dContent.DrawPartialCell(row, column, L"");
	}

	//set edit control size and position
	auto& widthManager = m_table.m_d2dContent.m_columnWidthManager;
	auto const& tableHeight = m_table.m_d2dContent.m_tableHeight;
	auto const contentRowHeight = tableHeight.ContentRowHeight();
	editControl.Width(widthManager.Get(column));
	editControl.Height(contentRowHeight);
	winrt::WinUINamespace::UI::Xaml::Controls::Canvas::SetLeft(editControl, widthManager.SumColumnWidth(column, 0) + cellLeftOffset() - m_table.m_d2dContent.ScrollOffsetX());
	winrt::WinUINamespace::UI::Xaml::Controls::Canvas::SetTop(editControl, tableHeight.HeaderRowHeight() + row * contentRowHeight - m_table.m_d2dContent.ScrollOffsetY());
	m_children.Append(editControl);

	//try set focus
	editControl.Focus(winrt::WinUINamespace::UI::Xaml::FocusState::Programmatic);
}

void TableOverlayManager::EndEdit()
{
	if (!m_editControl)
		return;

	uint32_t index = 0;
	if (m_children.IndexOf(m_editControl.Remove(m_table.m_d2dContent), index))
		m_children.RemoveAt(index);
}

bool TableOverlayManager::IsEditing() const
{
	return m_editControl;
}
