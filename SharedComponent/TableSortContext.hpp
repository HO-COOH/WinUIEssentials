#pragma once
#include "TableSortParameter.hpp"
#include <vector>
#include <numeric>

namespace winrt::PackageRoot::implementation
{
	struct TableRow;
}

class TextLayoutCache;

class TableSortContext
{
	TableSortParameter m_sortParameter;
	//display row -> source row
	std::vector<size_t> m_sortedIndices;

	constexpr void makeSortIndices(int rowCount)
	{
		m_sortedIndices.resize(rowCount);
		std::iota(m_sortedIndices.begin(), m_sortedIndices.end(), size_t{ 0 });
	}
public:
	constexpr explicit operator bool() const
	{
		return static_cast<bool>(m_sortParameter);
	}

	//Maps a display row to the source row whose data it shows. Returns `displayRow`
	//unchanged when unsorted, and passes a negative through so callers that use -1
	//as "no row" keep working.
	constexpr int Source(int displayRow) const
	{
		//Only SetSort rebuilds the permutation, but rows can be added afterwards, so
		//the row count can outgrow it: display rows past the end fall through to
		//identity (the appended rows, shown unsorted at the bottom) rather than
		//reading off the end of the vector.
		return m_sortParameter && static_cast<size_t>(displayRow) < m_sortedIndices.size()
			? static_cast<int>(m_sortedIndices[displayRow])
			: displayRow;
	}

	constexpr TableSortDirection SortDirection() const
	{
		return m_sortParameter.sortDirection;
	}

	constexpr void SetSortParameter(TableSortParameter sortParameter)
	{
		if (sortParameter.sortDirection == TableSortDirection::None)
			sortParameter.sortColumn = -1;

		if (m_sortParameter == sortParameter)
			return;

		m_sortParameter = sortParameter;
		m_sortedIndices.clear();
	}

	void SortObject(int rowCount, std::vector<winrt::com_ptr<winrt::PackageRoot::implementation::TableRow>> const& tableRows);
	void SortString(int rowCount, TextLayoutCache const& textLayoutCache);
};