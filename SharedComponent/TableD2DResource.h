#pragma once
#include "TableProperty.h"
#include <d2d1.h>
#include <vector>

struct ID2D1DeviceContext;
class TextLayoutCache;

class TableD2DResource
{
	TextLayoutCache& m_textLayoutCache_ref;
	static void setIfNotTransparent(winrt::com_ptr<ID2D1SolidColorBrush>& brush, ID2D1DeviceContext* d2dContext, D2D_COLOR_F color);
public:
	struct AlternateRowBrushPair
	{
		winrt::com_ptr<ID2D1SolidColorBrush> m_background;
		winrt::com_ptr<ID2D1SolidColorBrush> m_foreground;
	};

	winrt::com_ptr<ID2D1SolidColorBrush> m_headerTextBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_contentTextBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_headerBackgroundBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_pillBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_hoverBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_horizontalLineBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_verticalLineBrush;

	std::vector<AlternateRowBrushPair> m_alternateRowBrushes;

	TableD2DResource(TextLayoutCache& textLayoutCache);
	TableProperty m_localTableData{};
	void Create(ID2D1DeviceContext* d2dContext, TableProperty&& tableData);
	void RebuildAlternateRowBrushes(ID2D1DeviceContext* d2dContext);
	void ScaleChanged();
};