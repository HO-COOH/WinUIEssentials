#pragma once

#include "UI/Xaml/Media/Animations/OpacityAnimation.g.h"

namespace winrt::WinUI3Package::UI::Xaml::Media::Animations::implementation
{
	struct OpacityAnimation : OpacityAnimationT<OpacityAnimation>
	{
		OpacityAnimation();

		Microsoft::UI::Xaml::Media::Animation::EasingMode EasingMode() const;
		void EasingMode(Microsoft::UI::Xaml::Media::Animation::EasingMode const& value);

		double From() const;
		void From(double value);

		double To() const;
		void To(double value);

	private:
		Microsoft::UI::Xaml::Media::Animation::EasingMode m_easingMode{};
		double m_from{};
		double m_to{};
	};
}

namespace winrt::WinUI3Package::UI::Xaml::Media::Animations::factory_implementation
{
	struct OpacityAnimation : winrt::WinUI3Package::UI::Xaml::Media::Animations::factory_implementation::OpacityAnimationT<OpacityAnimation, implementation::OpacityAnimation>
	{
	};
}
