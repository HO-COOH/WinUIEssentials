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
	auto& factory = TenMicaEffectFactory::GetFactory();
	m_themeCrossFadeBrush.StartAnimation(
		L"ThemeFade.CrossFade",
		isLightTheme ? factory.m_crossFadeForwardAnimation : factory.m_crossFadeBackwardAnimation
	);
	m_inactiveBrush.Color(isLightTheme ? TenMicaConstants::WinUI::LuminosityColorLight : TenMicaConstants::WinUI::LuminosityColorDark);
}

void TenMicaEffect::SetActive(bool isActive)
{
	auto& factory = TenMicaEffectFactory::GetFactory();
	m_finalCrossFadeBrush.StartAnimation(
		L"CrossFade.CrossFade",
		isActive ? factory.m_crossFadeForwardAnimation : factory.m_crossFadeBackwardAnimation
	);
}
