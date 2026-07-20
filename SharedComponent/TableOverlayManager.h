#pragma once
#include <optional>
#include <vector>
#include "EditControlOverlay.h"

namespace winrt::PackageRoot::implementation
{
	struct Table;
}

class TableOverlayManager
{
	constexpr static auto TranslationExpression = L"Vector2(ColumnProperty.CellX - TableProperty.ScrollOffsetX, cellY - TableProperty.ScrollOffsetY)";
	constexpr static auto HeaderTranslationExpression = L"Vector2(ColumnProperty.CellX - TableProperty.ScrollOffsetX, 0)";

	struct CellSlot
	{
		winrt::WinUINamespace::UI::Xaml::FrameworkElement element{ nullptr };
		int row{ -1 };
	};

	struct ColumnState
	{
		winrt::WinUINamespace::UI::Composition::CompositionPropertySet ColumnProperty{ nullptr };
		std::vector<CellSlot> slots;
		std::vector<winrt::Windows::Foundation::IInspectable> rowDataCache;
		winrt::WinUINamespace::UI::Xaml::FrameworkElement headerElement{ nullptr };
	};

	winrt::WinUINamespace::UI::Xaml::Controls::UIElementCollection m_children{ nullptr };
	winrt::WinUINamespace::UI::Xaml::Controls::UIElementCollection m_headerChildren{ nullptr };
	winrt::WinUINamespace::UI::Composition::Compositor m_compositor;
	winrt::WinUINamespace::UI::Composition::CompositionPropertySet TableProperty;
	winrt::WinUINamespace::UI::Composition::CompositionEasingFunction m_scrollEasingFunction;
	winrt::WinUINamespace::UI::Composition::ScalarKeyFrameAnimation m_scrollAnimation;
	winrt::WinUINamespace::UI::Composition::ExpressionAnimation m_cellExpression;
	winrt::WinUINamespace::UI::Composition::ExpressionAnimation m_headerExpression;
	winrt::PackageRoot::implementation::Table& m_table;

	std::vector<ColumnState> m_columns;
	EditControlOverlay m_editControl;

	//Cached vertical-line + left-padding offset in DIPs. Lazily filled on
	//first use; the inputs (line color, thickness, padding) don't change
	//post-load in the current pipeline.
	mutable std::optional<float> m_cellLeadingOffset;

	ColumnState& ensureColumn(int column);
	CellSlot& createSlot(ColumnState& state, int column);
	CellSlot& getOrCreateFreeSlot(ColumnState& state, int row, int column);

	float cellLeftOffset() const; //vertical line thickness + padding.left
	float cellContentWidth(int column) const;

	void recycleControls(float targetY);
	void rebindVisibleRows(float targetY);
public:
	TableOverlayManager(winrt::PackageRoot::implementation::Table& table);

	void OnInitializedComponent();
	void OnLoaded();
	void OnColumnsInitialized();

	void SetCellContent(
		int row,
		int column,
		winrt::Windows::Foundation::IInspectable const& cellObject
	);

	void OnColumnResized(int resizedColumn);

	//mouse scroll uses the same easing function as TableD2DContent
	void OnMouseScroll(float targetY);

	//directly set scroll offset without animation, used for scrollbar dragging
	void OnScrollYChanged(float newScrollY);
	void OnScrollXChanged(float newScrollX);

	//Drop the cached IInspectable for rows in [startRow, endRow] and free any
	//slots currently bound to those rows so the next RowRequested round-trip
	//rebinds with fresh data. Called from the UpdateRowData event handler.
	void InvalidateRows(int startRow, int endRow);

	//Inline cell editor: load the column's EditTemplate, place it over the
	//target cell, bind it to the cell's data. EndEdit removes it.
	void BeginEdit(int row, int column);
	void EndEdit();
	bool IsEditing() const;
};
