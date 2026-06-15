#pragma once
#include <vector>
#include "TextLayoutCache.h"

struct TableProperty;
struct ColumnWidthInitializationContext;
class TableHeightManager;

namespace winrt::PackageRoot::implementation
{
	struct TableColumn;
}

class ColumnWidthManager
{
	winrt::PackageRoot::ColumnSizingMode m_sizingMode{ winrt::PackageRoot::ColumnSizingMode::RowContent };
	TextLayoutCache& m_layoutCacheRef;
	TableProperty const& m_tableDataRef;
	TableHeightManager const& m_tableHeightRef;
	std::vector<std::atomic<float>> m_columnWidths;
	std::atomic<uint32_t> m_widthVersion{ 0 };
	void pushColumnBoundsToCache(int column, float width, ColumnWidthInitializationContext const& ctx);
	void initialize(std::vector<float> const& result);
	void initializeUniformWidth(float availableWidth, size_t numColumns);
public:
	constexpr ColumnWidthManager(TextLayoutCache& layoutCache, TableProperty const& tableData, TableHeightManager const& tableHeight)
		: m_layoutCacheRef{ layoutCache }
		, m_tableDataRef{ tableData }
		, m_tableHeightRef{ tableHeight }
	{
	}

	uint32_t Version() const noexcept;
	constexpr winrt::PackageRoot::ColumnSizingMode SizingMode() const
	{
		return m_sizingMode;
	}

	void InitializeColumnWidth(
		float width, 
		float scale, 
		std::vector<winrt::com_ptr<winrt::PackageRoot::implementation::TableColumn>> const& columnDefinitions
	);

	float Get(int column) const;
	float SumColumnWidth(int column, float scrollOffsetX = 0.f) const;
	float SumColumnWidth() const;
	int GetColumnIndexFromX(float x, float scrollOffsetX = 0.f) const;
	void Set(int column, float width);

	constexpr size_t NumColumns() const
	{
		return m_columnWidths.size();
	}
};