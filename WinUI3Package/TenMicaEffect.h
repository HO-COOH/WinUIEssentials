#pragma once
#include <winrt/Windows.UI.Composition.h>
struct TenMicaEffect
{
	winrt::Windows::UI::Composition::CompositionEffectBrush m_themeCrossFadeBrush{ nullptr };
	winrt::Windows::UI::Composition::CompositionEffectBrush m_finalCrossFadeBrush{ nullptr };
	winrt::Windows::UI::Composition::CompositionColorBrush m_inactiveBrush{ nullptr };
	winrt::Windows::UI::Composition::CompositionSurfaceBrush m_lightBrush{ nullptr };
	winrt::Windows::UI::Composition::CompositionSurfaceBrush m_darkBrush{ nullptr };
	

	void SetBrushOffset(float offsetX, float offsetY);
	void SetTheme(bool isLightTheme);
	void SetActive(bool isActive);
};