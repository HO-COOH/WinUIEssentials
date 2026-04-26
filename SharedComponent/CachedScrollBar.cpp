#include "pch.h"
#include "CachedScrollBar.h"

void CachedScrollBar::Set(winrt::WinUINamespace::UI::Xaml::Controls::Primitives::ScrollBar const& scrollBar)
{
	m_scrollBar = scrollBar;
}

void CachedScrollBar::Visibility(winrt::WinUINamespace::UI::Xaml::Visibility visibility)
{
	if (m_visibility == visibility)
		return;
	m_visibility = visibility;
	m_scrollBar.Visibility(visibility);
}

void CachedScrollBar::Maximum(double maximum)
{
	if (m_maximum == maximum)
		return;
	m_maximum = maximum;
	m_scrollBar.Maximum(maximum);
}

void CachedScrollBar::ViewportSize(double viewportSize)
{
	if (m_viewportSize == viewportSize)
		return;
	m_viewportSize = viewportSize;
	m_scrollBar.ViewportSize(viewportSize);
}

void CachedScrollBar::LargeChange(double largeChange)
{
	if (m_largeChange == largeChange)
		return;
	m_largeChange = largeChange;
	m_scrollBar.LargeChange(largeChange);
}

void CachedScrollBar::SmallChange(double smallChange)
{
	if (m_smallChange == smallChange)
		return;
	m_smallChange = smallChange;
	m_scrollBar.SmallChange(smallChange);
}

bool CachedScrollBar::Value(double value)
{
	if (m_value == value)
		return false;
	m_value = value;
	m_scrollBar.Value(value);
	return true;
}

