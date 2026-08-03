#include "pch.h"
#include "TableSortContext.hpp"
#include "TableCompare.hpp"
#include "TableRow.h"
#include "TextLayoutCache.h"
#include <algorithm>

void TableSortContext::SortObject(int rowCount, std::vector<winrt::com_ptr<winrt::PackageRoot::implementation::TableRow>> const& tableRows)
{
	std::ranges::stable_sort(m_sortedIndices, [&tableRows, this](size_t lhsIndex, size_t rhsIndex)
	{
		auto const cmp = compareObject(
			tableRows[lhsIndex]->m_data[m_sortParameter.sortColumn],
			tableRows[rhsIndex]->m_data[m_sortParameter.sortColumn]
		);
		return m_sortParameter.sortDirection == TableSortDirection::Ascending ? std::is_lt(cmp) : std::is_gt(cmp);
	});
}

void TableSortContext::SortString(int rowCount, TextLayoutCache const& textLayoutCache)
{
	std::ranges::stable_sort(m_sortedIndices, [&textLayoutCache, this](size_t lhsIndex, size_t rhsIndex)
	{
		auto const cmp =
			textLayoutCache.GetCellContent(lhsIndex, m_sortParameter.sortColumn) <=>
			textLayoutCache.GetCellContent(rhsIndex, m_sortParameter.sortColumn);
		return m_sortParameter.sortDirection == TableSortDirection::Ascending ? std::is_lt(cmp) : std::is_gt(cmp);
	});
}
