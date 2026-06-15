#pragma once

struct TableProperty;
class TextLayoutCache;
class TableHeightManager;

struct ColumnWidthInitializationContext
{
	float scale;
	float horizontalPadding;
	float paddedMaxHeight;

	ColumnWidthInitializationContext(
		TableProperty const& tableProperty,
		TextLayoutCache const& textLayout,
		TableHeightManager const& tableHeight
	);
};