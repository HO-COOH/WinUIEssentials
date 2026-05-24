#pragma once
#include <vector>

namespace winrt::PackageRoot::implementation
{
	struct Table;
}

class TableOverlayManager
{
	constexpr static auto TranslationExpression = L"Vector2(ColumnProperty.CellX - TableProperty.ScrollOffsetX, cellY - TableProperty.ScrollOffsetY)";

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
	};

	winrt::WinUINamespace::UI::Xaml::Controls::UIElementCollection m_children{ nullptr };
	winrt::WinUINamespace::UI::Composition::Compositor m_compositor;
	winrt::WinUINamespace::UI::Composition::CompositionPropertySet TableProperty;
	winrt::WinUINamespace::UI::Composition::PowerEasingFunction m_scrollEasingFunction;
	winrt::WinUINamespace::UI::Composition::ScalarKeyFrameAnimation m_scrollAnimation;
	winrt::WinUINamespace::UI::Composition::ExpressionAnimation m_cellExpression;
	winrt::PackageRoot::implementation::Table& m_table;

	std::vector<ColumnState> m_columns;

	ColumnState& ensureColumn(int column);
	CellSlot& createSlot(ColumnState& state, int column);
	CellSlot& getOrCreateFreeSlot(ColumnState& state, int row, int column);

	void recycleControls(float targetY);
	void rebindVisibleRows(float targetY);
public:
	TableOverlayManager(winrt::PackageRoot::implementation::Table& table);

	void OnInitializedComponent();

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
};
