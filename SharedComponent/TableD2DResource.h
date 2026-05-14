#pragma once
#include "TableData.h"
#include <d2d1.h>

struct ID2D1DeviceContext;
class TextLayoutCache;

class TableD2DResource
{
	TextLayoutCache& m_textLayoutCache_ref;
public:
	winrt::com_ptr<ID2D1SolidColorBrush> m_headerTextBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_contentTextBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_backgroundBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_alternateBackgroundBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_pillBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_hoverBrush;

	TableD2DResource(TextLayoutCache& textLayoutCache);
	TableData m_localTableData{};
	void Create(ID2D1DeviceContext* d2dContext, TableData&& tableData);
	void ScaleChanged();
};