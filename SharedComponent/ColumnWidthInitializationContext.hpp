#pragma once
#include "TableProperty.h"
#include "TextLayoutCache.h"
#include "TableConstants.hpp"

struct ColumnWidthInitializationContext
{
	float scale;
	float horizontalPadding;
	float paddedMaxHeight;

	constexpr ColumnWidthInitializationContext(
		TableProperty const& tableProperty,
		TextLayoutCache const& textLayout
	) : scale{textLayout.Scale},
		horizontalPadding{static_cast<float>(tableProperty.m_contentPadding.Left + tableProperty.m_contentPadding.Right)},
		paddedMaxHeight{(std::max)(0.f, TableConstants::RowHeight - static_cast<float>(tableProperty.m_contentPadding.Top + tableProperty.m_contentPadding.Bottom)) * scale}
	{
	}
};