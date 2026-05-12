#include "pch.h"
#include "ColumnWidthManager.h"
#include <algorithm>
#include <numeric>
#include <ranges>
#include "TableConstants.hpp"

static float measureNaturalWidth(DWRITE_TEXT_METRICS& metrics, IDWriteTextLayout* layout)
{
	auto const saved = layout->GetMaxWidth();
	winrt::check_hresult(layout->SetMaxWidth(FLT_MAX));
	winrt::check_hresult(layout->GetMetrics(&metrics));
	winrt::check_hresult(layout->SetMaxWidth(saved));
	return (std::max)(metrics.width, metrics.widthIncludingTrailingWhitespace);
}

void ColumnWidthManager::GetInitialColumnWidth(float width, float scale)
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
		std::vector<float> result(headerRow.size(), 0.f);

		DWRITE_TEXT_METRICS metrics;
		switch (m_sizingMode)
		{
			case winrt::PackageRoot::ColumnSizingMode::HeaderContent:
			{
				for (size_t col = 0; col < numColumns; ++col)
					result[col] = measureNaturalWidth(metrics, headerRow[col].layout.get());
				break;
			}
			case winrt::PackageRoot::ColumnSizingMode::RowContent:
			{
				for (auto const& row : layoutCache)
				{
					auto const cols = (std::min)(row.size(), result.size());
					for (size_t col = 0; col < cols; ++col)
						result[col] = (std::max)(result[col], measureNaturalWidth(metrics, row[col].layout.get()));
				}
				break;
			}
			default:
				throw std::runtime_error{ "Unknown ColumnSizingMode" };
		}

		if (auto const sum = std::accumulate(result.begin(), result.end(), 0.f); sum > 0.f)
		{
			std::ranges::transform(
				result, 
				result.begin(),
				[sum, width](float measuredWidth) { return width * measuredWidth / sum; }
			);
		}

		m_columnWidths = std::vector<std::atomic<float>>(result.size());
		for (size_t i = 0; i < result.size(); ++i)
		{
			auto const columnWidth = result[i] / scale;
			Set(i, columnWidth);
		}
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

void ColumnWidthManager::Set(int column, float width)
{
	m_columnWidths[column].store(width, std::memory_order_relaxed);
	pushColumnBoundsToCache(column, width);
}
