#include "pch.h"
#include "ColumnWidthManager.h"
#include <algorithm>
#include <numeric>
#include <ranges>
#include "TableConstants.hpp"
#include "TableProperty.h"
#include "TableColumn.h"
#include "ColumnWidthInitializationContext.hpp"

static float measureNaturalRawWidth(DWRITE_TEXT_METRICS& metrics, IDWriteTextLayout* layout)
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
	if (sum <= 0.f)
		return;

	std::ranges::transform(
		result,
		result.begin(),
		[sum, rawWidth](float measuredWidth) { return rawWidth * measuredWidth / sum; }
	);
}

//available width is not enough to fit the natural width of content, we use MinWidth/MaxWidth if set and measuredWidth if not
//resulting content overflows the table space, horizontal scrollbar will appear
constexpr static void clampToColumnConstraints(
	std::vector<float>& measuredWidths,
	std::vector<winrt::com_ptr<winrt::PackageRoot::implementation::TableColumn>> const& columnDefinitions)
{
	for (size_t col = 0; col < measuredWidths.size(); ++col)
	{
		auto const minWidth = columnDefinitions[col]->m_minWidth;
		auto const maxWidth = columnDefinitions[col]->m_maxWidth;
		auto const lo = minWidth >= 0.f ? minWidth : 0.f;
		auto const hi = maxWidth >= 0.f ? maxWidth : (std::numeric_limits<float>::max)();
		measuredWidths[col] = std::clamp(measuredWidths[col], lo, hi);
	}
}

void ColumnWidthManager::InitializeColumnWidth(float width, float scale, std::vector<winrt::com_ptr<winrt::PackageRoot::implementation::TableColumn>> const& columnDefinitions)
{
	auto const& layoutCache = m_layoutCacheRef.m_perCellCache;
	auto const& headerRow = layoutCache.front();
	assert(!layoutCache.empty() && !headerRow.empty());

	auto const numColumns = headerRow.size();

	//if the vertical line color is not transparent, deduct its width from total width
	if (m_tableDataRef.m_verticalLineColor.a > 0.f)
		width -= m_tableDataRef.m_verticalLineThickness * (numColumns + 1);

	if (m_sizingMode == winrt::PackageRoot::ColumnSizingMode::Equal)
	{
		initialize(width, numColumns);
		return;
	}


	auto const& padding = m_tableDataRef.m_contentPadding;
	auto const horizontalPadding = static_cast<float>(padding.Left + padding.Right);
	std::vector<float> finalWidths(headerRow.size(), horizontalPadding);

	DWRITE_TEXT_METRICS metrics;
	switch (m_sizingMode)
	{
		case winrt::PackageRoot::ColumnSizingMode::HeaderContent:
		{
			for (size_t col = 0; col < numColumns; ++col)
				finalWidths[col] += measureNaturalRawWidth(metrics, headerRow[col].layout.get()) / scale;
			break;
		}
		case winrt::PackageRoot::ColumnSizingMode::RowContent:
		{
			for (auto const& row : layoutCache)
			{
				auto const cols = (std::min)(row.size(), finalWidths.size());
				for (size_t col = 0; col < cols; ++col)
					finalWidths[col] = (std::max)(finalWidths[col], measureNaturalRawWidth(metrics, row[col].layout.get()) / scale + horizontalPadding);
			}
			break;
		}
		default:
			throw std::runtime_error{ "Unknown ColumnSizingMode" };
	}

	if (auto const [enough, sum] = isAvailableColumnWidthEnough(finalWidths, width); enough)
		weightedSum(finalWidths, width, sum);
	else
		clampToColumnConstraints(finalWidths, columnDefinitions);
	initialize(finalWidths);
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


void ColumnWidthManager::pushColumnBoundsToCache(int column, float width, ColumnWidthInitializationContext const& ctx)
{
	if (m_layoutCacheRef.m_perCellCache.empty())
		return;

	if (static_cast<size_t>(column) >= m_layoutCacheRef.m_perColumnCache.size())
		return;

	auto const paddedMaxWidth = (std::max)(0.f, (width - ctx.horizontalPadding) * ctx.scale);

	auto& columnLayout = m_layoutCacheRef.m_perColumnCache[column];
	bool const changed =
		(std::exchange(columnLayout.maxWidth, paddedMaxWidth) != paddedMaxWidth) |
		(std::exchange(columnLayout.maxHeight, ctx.paddedMaxHeight) != ctx.paddedMaxHeight);

	if (!changed)
		return;

	++columnLayout.m_contentLayoutVersion;
	auto& headerRow = m_layoutCacheRef.m_perCellCache.front();
	auto& headerLayout = headerRow[column].layout;
	winrt::check_hresult(headerLayout->SetMaxWidth(paddedMaxWidth));
	winrt::check_hresult(headerLayout->SetMaxHeight(ctx.paddedMaxHeight));
}

void ColumnWidthManager::initialize(std::vector<float> const& result)
{
	m_columnWidths = std::vector<std::atomic<float>>(result.size());
	ColumnWidthInitializationContext ctx{ m_tableDataRef, m_layoutCacheRef };
	for (size_t i = 0; i < result.size(); ++i)
	{
		m_columnWidths[i].store(result[i], std::memory_order_relaxed);
		pushColumnBoundsToCache(static_cast<int>(i), result[i], ctx);
	}
	m_widthVersion.fetch_add(1, std::memory_order_relaxed);
}

void ColumnWidthManager::initialize(float availableWidth, size_t numColumns)
{
	m_columnWidths = std::vector<std::atomic<float>>(numColumns);
	ColumnWidthInitializationContext ctx{ m_tableDataRef, m_layoutCacheRef };
	float const columnWidth = availableWidth / numColumns;
	for (size_t i = 0; i < numColumns; ++i)
	{
		m_columnWidths[i].store(columnWidth, std::memory_order_relaxed);
		pushColumnBoundsToCache(static_cast<int>(i), columnWidth, ctx);
	}
	m_widthVersion.fetch_add(1, std::memory_order_relaxed);
}

uint32_t ColumnWidthManager::Version() const noexcept
{
	return m_widthVersion.load(std::memory_order_relaxed);
}

void ColumnWidthManager::Set(int column, float width)
{
	m_columnWidths[column].store(width, std::memory_order_relaxed);
	pushColumnBoundsToCache(column, width, ColumnWidthInitializationContext{ m_tableDataRef, m_layoutCacheRef });
	m_widthVersion.fetch_add(1, std::memory_order_relaxed);
}
