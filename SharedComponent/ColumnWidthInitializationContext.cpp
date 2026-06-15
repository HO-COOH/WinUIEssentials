#include "pch.h"
#include "ColumnWidthInitializationContext.h"
#include "TableProperty.h"
#include "TextLayoutCache.h"
#include "TableHeightManager.h"

ColumnWidthInitializationContext::ColumnWidthInitializationContext(TableProperty const& tableProperty, TextLayoutCache const& textLayout, TableHeightManager const& tableHeight) : 
	scale{ textLayout.Scale },
	horizontalPadding{ static_cast<float>(tableProperty.m_contentPadding.Left + tableProperty.m_contentPadding.Right) },
	paddedMaxHeight{ tableHeight.ContentFontHeight() * scale }
{
}
