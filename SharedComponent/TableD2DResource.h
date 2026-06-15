#pragma once
#include "TableProperty.h"
#include <d2d1.h>

struct ID2D1DeviceContext;
class TextLayoutCache;

class TableD2DResource
{
	TextLayoutCache& m_textLayoutCache_ref;
	static void setIfNotTransparent(winrt::com_ptr<ID2D1SolidColorBrush>& brush, ID2D1DeviceContext* d2dContext, D2D_COLOR_F color);
public:
	winrt::com_ptr<ID2D1SolidColorBrush> m_headerTextBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_contentTextBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_headerBackgroundBrush;
	//winrt::com_ptr<ID2D1SolidColorBrush> m_alternateBackgroundBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_pillBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_hoverBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_horizontalLineBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_verticalLineBrush;

	TableD2DResource(TextLayoutCache& textLayoutCache);
	TableProperty m_localTableData{};
	void Create(ID2D1DeviceContext* d2dContext, TableProperty&& tableData);
	void ScaleChanged();
};