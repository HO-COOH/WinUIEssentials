#pragma once
#include <concepts>
#include <winrt/Windows.Foundation.h>

template<typename T>
struct AnimatedValue
{
	T m_from{};
	T m_to{};
	
	[[nodiscard]] constexpr T Lerp(std::floating_point auto progress) const noexcept
	{
		return static_cast<T>(m_from + (m_to - m_from) * progress);
	}
};

template<>
struct AnimatedValue<winrt::Windows::Foundation::Point>
{
	winrt::Windows::Foundation::Point m_from{};
	winrt::Windows::Foundation::Point m_to{};

	[[nodiscard]] constexpr winrt::Windows::Foundation::Point Lerp(std::floating_point auto progress) const noexcept
	{
		return 
		{
			AnimatedValue<float>{ m_from.X, m_to.X }.Lerp(progress),
			AnimatedValue<float>{ m_from.Y, m_to.Y }.Lerp(progress)
		};
	}
};