#include "pch.h"
#include "ColumnWidthManager.h"
#include <algorithm>
#include <numeric>
#include <ranges>
#include "TableConstants.hpp"
#include "TableProperty.h"
#include "TableColumn.h"

static float measureNaturalWidth(DWRITE_TEXT_METRICS& metrics, IDWriteTextLayout* layout)
{
	if (!layout)
		return 0.f;

	auto const saved = layout->GetMaxWidth();
	winrt::check_hresult(layout->SetMaxWidth(FLT_MAX));
	winrt::check_hresult(layout->GetMetrics(&metrics));
	winrt::check_hresult(layout->SetMaxWidth(saved));
	return (std::max)(metrics.width, metrics.widthIncludingTrailingWhitespace);
}

constexpr static std::pair<bool, float> isAvailableColumnWidthEnough(std::vector<float> const& measuredWidth, float availableWidth)
{
	auto const sum = std::accumulate(measuredWidth.begin(), measuredWidth.end(), 0.f);
	return { sum <= availableWidth, sum };
}

constexpr static void weightedSum(std::vector<float>& result, float rawWidth, float sum)
{
	if (sum > 0.f)
	{
		std::ranges::transform(
			result,
			result.begin(),
			[sum, rawWidth](float measuredWidth) { return rawWidth * measuredWidth / sum; }
		);
	}
}

//available width is not enough to fit the natural width of content, we use MinWidth/MaxWidth if set and measuredWidth if not
//resulting content overflows the table space, horizontal scrollbar will appear
constexpr static void clampToColumnConstraints(
	std::vector<float>& measuredWidths,
	std::vector<winrt::com_ptr<winrt::PackageRoot::implementation::TableColumn>> const& columnDefinitions,
	float scale)
{
	for (size_t col = 0; col < measuredWidths.size(); ++col)
	{
		auto const minWidth = columnDefinitions[col]->m_minWidth;
		auto const maxWidth = columnDefinitions[col]->m_maxWidth;
		auto const lo = minWidth >= 0.f ? minWidth * scale : 0.f;
		auto const hi = maxWidth >= 0.f ? maxWidth * scale : (std::numeric_limits<float>::max)();
		measuredWidths[col] = std::clamp(measuredWidths[col], lo, hi);
	}
}

void ColumnWidthManager::InitializeColumnWidth(float width, float scale, std::vector<winrt::com_ptr<winrt::PackageRoot::implementation::TableColumn>> const& columnDefinitions)
{
	auto const& layoutCache = m_layoutCacheRef.m_perCellCache;
	assert(!layoutCache.empty() && !layoutCache.front().empty());

	auto const& headerRow = layoutCache.front();
	auto const numColumns = headerRow.size();

	if (m_sizingMode == winrt::PackageRoot::ColumnSizingMode::Equal)
	{
		m_columnWidths = std::vector<std::atomic<float>>(headerRow.size());
		auto const equalWidth = width / numColumns;
		for (size_t i = 0; i < numColumns; ++i)
			Set(i, equalWidth);
	}
	else
	{
		width *= scale;
		if (m_tableDataRef.m_verticalLineColor.a > 0.f)
			width -= m_tableDataRef.m_verticalLineThickness * scale * (numColumns + 1);
		std::vector<float> measuredWidths(headerRow.size(), 0.f);

		DWRITE_TEXT_METRICS metrics;
		switch (m_sizingMode)
		{
			case winrt::PackageRoot::ColumnSizingMode::HeaderContent:
			{
				for (size_t col = 0; col < numColumns; ++col)
					measuredWidths[col] = measureNaturalWidth(metrics, headerRow[col].layout.get());
				break;
			}
			case winrt::PackageRoot::ColumnSizingMode::RowContent:
			{
				for (auto const& row : layoutCache)
				{
					auto const cols = (std::min)(row.size(), measuredWidths.size());
					for (size_t col = 0; col < cols; ++col)
						measuredWidths[col] = (std::max)(measuredWidths[col], measureNaturalWidth(metrics, row[col].layout.get()));
				}
				break;
			}
			default:
				throw std::runtime_error{ "Unknown ColumnSizingMode" };
		}

		auto const& padding = m_tableDataRef.m_contentPadding;
		auto const horizontalPaddingPx = static_cast<float>(padding.Left + padding.Right) * scale;
		std::ranges::transform(
			measuredWidths,
			measuredWidths.begin(),
			[horizontalPaddingPx](float measuredWidth) { return measuredWidth + horizontalPaddingPx; }
		);

		if (auto const [enough, sum] = isAvailableColumnWidthEnough(measuredWidths, width); enough)
			weightedSum(measuredWidths, width, sum);
		else
			clampToColumnConstraints(measuredWidths, columnDefinitions, scale);
		initialize(measuredWidths, scale);
	}
}

float ColumnWidthManager::Get(int column) const
{
	return m_columnWidths.empty()? (std::numeric_limits<float>::max)() : m_columnWidths[column].load(std::memory_order_relaxed);
}

float ColumnWidthManager::SumColumnWidth(int column, float scrollOffsetX) const
{
	return std::accumulate(
		m_columnWidths.begin(),
		m_columnWidths.begin() + column,
		scrollOffsetX,
		[](float sum, std::atomic<float> const& element) { return sum + element.load(std::memory_order_relaxed); }
	);
}

float ColumnWidthManager::SumColumnWidth() const
{
	return std::accumulate(
		m_columnWidths.begin(),
		m_columnWidths.end(),
		0.f,
		[](float sum, std::atomic<float> const& element) { return sum + element.load(std::memory_order_relaxed); }
	);
}

int ColumnWidthManager::GetColumnIndexFromX(float x, float scrollOffsetX) const
{
	//The last column do not need to have a resize handle
	auto const resizable = m_columnWidths.empty() ? 0 : m_columnWidths.size() - 1;
	for (size_t i = 0; i < resizable; ++i)
	{
		scrollOffsetX += m_columnWidths[i].load(std::memory_order_relaxed);
		if (std::abs(x - scrollOffsetX) <= TableConstants::ResizeHotZoneDelta)
			return static_cast<int>(i);
	}
	return TableConstants::ResizeColumnIndexNone;
}

void ColumnWidthManager::pushColumnBoundsToCache(int column, float width)
{
	if (m_layoutCacheRef.m_perCellCache.empty())
		return;

	auto const scale = m_layoutCacheRef.Scale;
	auto const& padding = m_tableDataRef.m_contentPadding;
	auto const paddedMaxWidth = (std::max)(0.f,
		(width - static_cast<float>(padding.Left + padding.Right)) * scale);
	auto const paddedMaxHeight = (std::max)(0.f,
		(TableConstants::RowHeight - static_cast<float>(padding.Top + padding.Bottom)) * scale);

	if (static_cast<size_t>(column) >= m_layoutCacheRef.m_perColumnCache.size())
		return;

	auto& columnLayout = m_layoutCacheRef.m_perColumnCache[column];
	bool const changed =
		(std::exchange(columnLayout.maxWidth, paddedMaxWidth) != paddedMaxWidth) |
		(std::exchange(columnLayout.maxHeight, paddedMaxHeight) != paddedMaxHeight);

	if (!changed)
		return;

	++columnLayout.m_contentLayoutVersion;
	auto& headerRow = m_layoutCacheRef.m_perCellCache.front();
	auto& headerLayout = headerRow[column].layout;
	winrt::check_hresult(headerLayout->SetMaxWidth(paddedMaxWidth));
	winrt::check_hresult(headerLayout->SetMaxHeight(paddedMaxHeight));
}

void ColumnWidthManager::initialize(std::vector<float> const& result, float scale)
{
	m_columnWidths = std::vector<std::atomic<float>>(result.size());
	for (size_t i = 0; i < result.size(); ++i)
	{
		auto const columnWidth = result[i] / scale;
		Set(i, columnWidth);
	}
}

void ColumnWidthManager::Set(int column, float width)
{
	m_columnWidths[column].store(width, std::memory_order_relaxed);
	pushColumnBoundsToCache(column, width);
	m_widthVersion.fetch_add(1, std::memory_order_relaxed);
}
