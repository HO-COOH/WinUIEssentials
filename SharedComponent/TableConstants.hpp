#pragma once
#include <chrono>

namespace TableConstants
{
	constexpr float HeaderFontSize = 20.f;
	constexpr float CellFontSize = 14.f;
	constexpr float SortIndicatorWidth = 16.f;
	constexpr float RowHeight = 36.f;
	constexpr float HeaderHeight = 36.f;
	constexpr float ColumnWidth = 200.f;
	constexpr float MinColumnWidth = 16.f;
	constexpr float CornerRadius = 8.f;
	constexpr float ResizeHotZoneDelta = 8.f;
	constexpr int ResizeColumnIndexNone = -1;
	constexpr int HoveredRowNone = -1;
	
	constexpr float PillPaddingY = 8.f;
	constexpr float PillWidth = 2.f;
	constexpr float PillCornerRadius = 4.f;
	
	constexpr std::chrono::milliseconds SmoothScrollDuration{ 250 };
}