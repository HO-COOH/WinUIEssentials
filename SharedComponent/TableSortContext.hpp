#pragma once
#include "TableSortDirection.h"
#include <vector>

struct TableSortParameter
{
	int sortColumn = -1;
	TableSortDirection sortDirection{};

	constexpr operator bool() const
	{
		return sortColumn >= 0;
	}

	constexpr bool operator==(TableSortParameter const&) const = default;
};

struct TableSortContext
{
	TableSortParameter sortParameter;
	std::vector<size_t> sortedIndices;

	explicit operator bool() const
	{
		return static_cast<bool>(sortParameter);
	}

	//Map a display row to its underlying source row. Falls back to the
	//identity when unsorted or out of range.
	size_t Source(size_t displayRow) const
	{
		if (sortParameter && displayRow < sortedIndices.size())
			return sortedIndices[displayRow];
		return displayRow;
	}

	void Clear()
	{
		sortParameter.sortColumn = -1;
		sortParameter.sortDirection = TableSortDirection::None;
		sortedIndices.clear();
	}
};