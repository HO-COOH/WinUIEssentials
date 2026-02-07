#pragma once
#include <d2d1.h>
#include <winrt/Windows.UI.h>
#include <chrono>

namespace TenMicaConstants
{
	namespace WinUI
	{
		constexpr static inline winrt::Windows::UI::Color LuminosityColorLight{ 255, 243, 243, 243 };
		constexpr static inline winrt::Windows::UI::Color LuminosityColorDark{ 255, 32, 32, 32 };
	}

	namespace D2D
	{
		constexpr static inline D2D1_COLOR_F LuminosityColorLight{ 0.9529f, 0.9529f, 0.9529f, 1.0f };
		constexpr static inline D2D1_COLOR_F LuminosityColorDark{ 0.125f, 0.125f, 0.125f, 1.0f };
		constexpr static float TintColorOpacityLight = 0.5f;
		constexpr static float TintColorOpacityDark = 0.8f;
		constexpr static float BlurRadius = 120.f;
	}

	constexpr static inline std::chrono::milliseconds AnimationDuration{ 200 };
}