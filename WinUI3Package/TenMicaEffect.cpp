#include "pch.h"
#include "TenMicaEffect.h"
#include "TenMicaConstants.h"
#include "TenMicaEffectFactory.h"

void TenMicaEffect::SetBrushOffset(float offsetX, float offsetY)
{
	if (IsFallback())
		return;

	m_lightBrush.Offset({ offsetX, offsetY });
	m_darkBrush.Offset({ offsetX, offsetY });
}

void TenMicaEffect::SetTheme(winrt::Microsoft::UI::Xaml::ElementTheme theme)
{
	bool const isLightTheme = theme == winrt::Microsoft::UI::Xaml::ElementTheme::Light;
	if (m_themeCrossFadeBrush)
	{
		m_themeCrossFadeBrush.StartAnimation(
			L"ThemeFade.CrossFade",
			isLightTheme ? m_factory->m_crossFadeForwardAnimation : m_factory->m_crossFadeBackwardAnimation
		);
	}
	m_inactiveBrush.Color(isLightTheme ? TenMicaConstants::WinUI::LuminosityColorLight : TenMicaConstants::WinUI::LuminosityColorDark);
}

void TenMicaEffect::SetActive(bool isActive)
{
	if (m_finalCrossFadeBrush)
	{
		m_finalCrossFadeBrush.StartAnimation(
			L"CrossFade.CrossFade",
			isActive ? m_factory->m_crossFadeForwardAnimation : m_factory->m_crossFadeBackwardAnimation
		);
	}
}

void TenMicaEffect::FallbackToInactiveBrush() noexcept
{
	m_themeCrossFadeBrush = nullptr;
	m_finalCrossFadeBrush = nullptr;
	m_lightBrush = nullptr;
	m_darkBrush = nullptr;
}

bool TenMicaEffect::IsFallback() const noexcept
{
	return !m_finalCrossFadeBrush;
}
