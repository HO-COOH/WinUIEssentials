#include "pch.h"
#include "TenMicaEffect.h"
#include "TenMicaConstants.h"
#include "TenMicaEffectFactory.h"

void TenMicaEffect::SetBrushOffset(float offsetX, float offsetY)
{
	m_lightBrush.Offset({ offsetX, offsetY });
	m_darkBrush.Offset({ offsetX, offsetY });
}

void TenMicaEffect::SetTheme(bool isLightTheme)
{
	m_themeCrossFadeBrush.StartAnimation(
		L"ThemeFade.CrossFade",
		isLightTheme ? m_factory->m_crossFadeForwardAnimation : m_factory->m_crossFadeBackwardAnimation
	);
	m_inactiveBrush.Color(isLightTheme ? TenMicaConstants::WinUI::LuminosityColorLight : TenMicaConstants::WinUI::LuminosityColorDark);
}

void TenMicaEffect::SetActive(bool isActive)
{
	m_finalCrossFadeBrush.StartAnimation(
		L"CrossFade.CrossFade",
		isActive ? m_factory->m_crossFadeForwardAnimation : m_factory->m_crossFadeBackwardAnimation
	);
}
