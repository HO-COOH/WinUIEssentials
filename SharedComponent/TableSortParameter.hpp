#pragma once
#include "TableSortDirection.h"

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