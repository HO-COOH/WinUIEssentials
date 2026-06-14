#pragma once
#include <chrono>

namespace TableConstants
{
	constexpr float SortIndicatorWidth = 16.f;
	constexpr float ColumnWidth = 200.f;
	constexpr float MinColumnWidth = 16.f;
	constexpr float CornerRadius = 4.f;
	constexpr float ResizeHotZoneDelta = 8.f;
	constexpr int ResizeColumnIndexNone = -1;
	constexpr int HoveredRowNone = -1;
	
	constexpr std::chrono::milliseconds SmoothScrollDuration{ 250 };
}