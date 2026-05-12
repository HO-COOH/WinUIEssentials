#pragma once
#include "TableData.h"
#include <d2d1.h>

struct ID2D1DeviceContext;
class TextLayoutCache;

struct TableD2DResource
{
	winrt::com_ptr<ID2D1SolidColorBrush> m_textBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_backgroundBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_alternateBackgroundBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_pillBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_hoverBrush;
	TextLayoutCache& m_textLayoutCache_ref;
public:
	TableD2DResource(TextLayoutCache& textLayoutCache);
	TableData m_localTableData{};
	void Create(ID2D1DeviceContext* d2dContext, TableData&& tableData);
	void ScaleChanged();
};