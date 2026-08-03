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

	constexpr size_t Source(size_t displayRow) const
	{
		return m_sortParameter ? m_sortedIndices[displayRow] : displayRow;
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