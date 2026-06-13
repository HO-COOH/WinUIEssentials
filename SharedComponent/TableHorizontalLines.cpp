#include "pch.h"
#include "TableHorizontalLines.h"
#include <d2d1_1.h>
#include <cmath>
#include "TableD2DResource.h"
#include "D2DPrimitiveHelper.h"

TableHorizontalLines::TableHorizontalLines(ID2D1Factory* factory, TableD2DResource& resource) :
	m_d2dFactory{ factory },
	m_resource_ref{ resource }
{
}

void TableHorizontalLines::Rebuild(float viewportWidth, float viewportHeight, float rowHeight, float headerHeight)
{
	if (m_geometry
		&& m_viewportWidth == viewportWidth
		&& m_viewportHeight == viewportHeight
		&& m_rowHeight == rowHeight
		&& m_headerHeight == headerHeight)
		return;

	m_viewportWidth = viewportWidth;
	m_viewportHeight = viewportHeight;
	m_rowHeight = rowHeight;
	m_headerHeight = headerHeight;
	m_geometry = nullptr;

	if (rowHeight <= 0.f || viewportWidth <= 0.f || viewportHeight <= 0.f)
		return;

	winrt::check_hresult(m_d2dFactory->CreatePathGeometry(m_geometry.put()));

	winrt::com_ptr<ID2D1GeometrySink> sink;
	winrt::check_hresult(m_geometry->Open(sink.put()));
	sink->SetFillMode(D2D1_FILL_MODE_WINDING);

	// One extra line so the partially-scrolled edge at the top is covered after
	// translation by up to (rowHeight - epsilon).
	int const lineCount = static_cast<int>(std::ceil(viewportHeight / rowHeight)) + 1;
	for (int i = 0; i < lineCount; ++i)
		D2DPrimitiveHelper::DrawHorizontalGeometry(sink.get(), 0.f, viewportWidth, i * rowHeight);
	winrt::check_hresult(sink->Close());
}

void TableHorizontalLines::Draw(ID2D1DeviceContext* d2dContext, float scrollOffsetY, float dataBottomY, float strokeWidth)
{
	if (!m_geometry || !m_resource_ref.m_horizontalLineBrush)
		return;

	float frac = std::fmod(scrollOffsetY, m_rowHeight);
	if (frac < 0.f)
		frac += m_rowHeight;

	float const yOffset = m_headerHeight + m_rowHeight - frac;

	D2D1_MATRIX_3X2_F saved;
	d2dContext->GetTransform(&saved);
	d2dContext->PushAxisAlignedClip(
		D2D1::RectF(0.f, m_headerHeight, m_viewportWidth, dataBottomY),
		D2D1_ANTIALIAS_MODE_ALIASED
	);
	d2dContext->SetTransform(D2D1::Matrix3x2F::Translation(0.f, yOffset) * saved);
	d2dContext->DrawGeometry(m_geometry.get(), m_resource_ref.m_horizontalLineBrush.get(), strokeWidth);
	d2dContext->SetTransform(saved);
	d2dContext->PopAxisAlignedClip();
}
