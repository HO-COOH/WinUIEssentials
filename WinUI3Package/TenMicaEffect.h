#pragma once
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <memory>

class TenMicaEffectFactory;

struct TenMicaEffect
{
	std::shared_ptr<TenMicaEffectFactory> m_factory;
	winrt::Windows::UI::Composition::CompositionEffectBrush m_themeCrossFadeBrush{ nullptr };
	winrt::Windows::UI::Composition::CompositionEffectBrush m_finalCrossFadeBrush{ nullptr };
	winrt::Windows::UI::Composition::CompositionColorBrush m_inactiveBrush{ nullptr };
	winrt::Windows::UI::Composition::CompositionSurfaceBrush m_lightBrush{ nullptr };
	winrt::Windows::UI::Composition::CompositionSurfaceBrush m_darkBrush{ nullptr };
	

	void SetBrushOffset(float offsetX, float offsetY);
	void SetTheme(winrt::Microsoft::UI::Xaml::ElementTheme theme);
	void SetActive(bool isActive);
	void FallbackToInactiveBrush() noexcept;
	[[nodiscard]] bool IsFallback() const noexcept;
};