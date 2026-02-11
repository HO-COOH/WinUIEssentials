#pragma once
#include <d2d1.h>
#include <winrt/Windows.UI.h>
#include <chrono>

namespace TenMicaConstants
{
	constexpr static D2D1_COLOR_F WindowsColorToD2DColor(winrt::Windows::UI::Color color)
	{
		constexpr float maxValue = (std::numeric_limits<decltype(color.A)>::max)();
		return D2D1_COLOR_F
		{
			.r = color.R / maxValue,
			.g = color.G / maxValue,
			.b = color.B / maxValue,
			.a = color.A / maxValue
		};
	}

	namespace WinUI
	{
		constexpr static inline winrt::Windows::UI::Color LuminosityColorLight{ 255, 243, 243, 243 };
		constexpr static inline winrt::Windows::UI::Color LuminosityColorDark{ 255, 32, 32, 32 };
	}

	namespace D2D
	{
		constexpr static inline D2D1_COLOR_F LuminosityColorLight = WindowsColorToD2DColor(WinUI::LuminosityColorLight);
		constexpr static inline D2D1_COLOR_F LuminosityColorDark = WindowsColorToD2DColor(WinUI::LuminosityColorDark);
		constexpr static float TintColorOpacityLight = 0.5f;
		constexpr static float TintColorOpacityDark = 0.8f;
		constexpr static float BlurRadius = 120.f;
	}

	constexpr static inline std::chrono::milliseconds AnimationDuration{ 250 };
}