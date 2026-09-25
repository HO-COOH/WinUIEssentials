#pragma once
#include <Windows.h>
#include <limits>
#include <type_traits>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Graphics.h>

/**
 * @brief Helpers for converting between DIPs (device independent pixels, what XAML lays out in)
 * and physical pixels (what the win32 APIs take)
 * @details These take sizes, extents and insets, which are never negative.
 * An integral result type rounds, so that a size survives a scale/unscale round trip,
 * while a floating point one converts exactly. That is why the result type defaults to the
 * type of the value instead of to `int`: it picks the arithmetic, not just the cast.
 */
namespace DpiUtils
{
	/**
	 * @brief The dpi at which one DIP is one physical pixel, that is a scale factor of 1.0
	 */
	inline constexpr UINT DefaultDpi = USER_DEFAULT_SCREEN_DPI;

	/**
	 * @brief The scale factor of a dpi value, eg. 1.5 for 144 dpi
	 */
	[[nodiscard]] constexpr double ScaleFactor(UINT dpi) noexcept
	{
		return dpi / static_cast<double>(DefaultDpi);
	}

	namespace Details
	{
		//clamped to prevent int overflowing
		template<typename Result>
		[[nodiscard]] constexpr Result roundAndClamp(double value) noexcept
		{
			constexpr auto max = static_cast<double>((std::numeric_limits<Result>::max)());
			value += 0.5;
			return value >= max ? (std::numeric_limits<Result>::max)() : static_cast<Result>(value); //because constexpr std::round is C++23
		}
	}

	/**
	 * @brief Scale a value in DIPs -> physical pixels
	 * @tparam ResultType The result type, defaults to the type of `value`
	 */
	template<typename ResultType = void, typename Value>
	[[nodiscard]] constexpr auto ScaleForDpi(Value value, UINT dpi) noexcept
	{
		using Result = std::conditional_t<std::is_void_v<ResultType>, Value, ResultType>;
		auto const scaled = value * static_cast<double>(dpi) / DefaultDpi;
		if constexpr (std::is_integral_v<Result>)
			return Details::roundAndClamp<Result>(scaled);
		else
			return static_cast<Result>(scaled);
	}

	/**
	 * @brief Scale a value in physical pixels back -> DIPs
	 * @tparam ResultType The result type, defaults to the type of `value`
	 */
	template<typename ResultType = void, typename Value>
	[[nodiscard]] constexpr auto UnscaleForDpi(Value value, UINT dpi) noexcept
	{
		using Result = std::conditional_t<std::is_void_v<ResultType>, Value, ResultType>;
		auto const unscaled = value * static_cast<double>(DefaultDpi) / dpi;
		if constexpr (std::is_integral_v<Result>)
			return Details::roundAndClamp<Result>(unscaled);
		else
			return static_cast<Result>(unscaled);
	}

	[[nodiscard]] constexpr winrt::Windows::Graphics::RectInt32 ScaleRectForDpi(
		winrt::Windows::Foundation::Rect const& bound,
		UINT dpi) noexcept
	{
		return winrt::Windows::Graphics::RectInt32{
			.X = ScaleForDpi<int>(bound.X, dpi),
			.Y = ScaleForDpi<int>(bound.Y, dpi),
			.Width = ScaleForDpi<int>(bound.Width, dpi),
			.Height = ScaleForDpi<int>(bound.Height, dpi)
		};
	}
}
