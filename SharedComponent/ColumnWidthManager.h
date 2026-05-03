#pragma once
#include <vector>
#include "TextLayoutCache.h"

class ColumnWidthManager
{
	winrt::PackageRoot::ColumnSizingMode m_sizingMode{ winrt::PackageRoot::ColumnSizingMode::HeaderContent };
	TextLayoutCache const& m_layoutCacheRef;
	std::vector<std::atomic<float>> m_columnWidths;
public:
	constexpr ColumnWidthManager(TextLayoutCache const& layoutCache) : m_layoutCacheRef{ layoutCache }
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
};