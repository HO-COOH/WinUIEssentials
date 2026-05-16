#pragma once
#include <vector>
#include "TextLayoutCache.h"

struct TableProperty;

class ColumnWidthManager
{
	winrt::PackageRoot::ColumnSizingMode m_sizingMode{ winrt::PackageRoot::ColumnSizingMode::RowContent };
	TextLayoutCache& m_layoutCacheRef;
	TableProperty const& m_tableDataRef;
	std::vector<std::atomic<float>> m_columnWidths;
	void pushColumnBoundsToCache(int column, float width);
public:
	constexpr ColumnWidthManager(TextLayoutCache& layoutCache, TableProperty const& tableData)
		: m_layoutCacheRef{ layoutCache }
		, m_tableDataRef{ tableData }
	{
	}

	constexpr winrt::PackageRoot::ColumnSizingMode SizingMode() const
	{
		return m_sizingMode;
	}

	void GetInitialColumnWidth(float width, float scale);

	float Get(int column) const;
	float SumColumnWidth(int column, float scrollOffsetX = 0.f) const;
	int GetColumnIndexFromX(float x, float scrollOffsetX = 0.f) const;
	void Set(int column, float width);

	constexpr size_t NumColumns() const
	{
		return m_columnWidths.size();
	}
};