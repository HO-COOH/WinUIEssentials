#pragma once

#include "UI/Xaml/Media/Animations/OffsetAnimation.g.h"

namespace winrt::WinUI3Package::UI::Xaml::Media::Animations::implementation
{
	struct OffsetAnimation : OffsetAnimationT<OffsetAnimation>
	{
		OffsetAnimation();

		Microsoft::UI::Xaml::Media::Animation::EasingMode EasingMode() const;
		void EasingMode(Microsoft::UI::Xaml::Media::Animation::EasingMode const& value);

		Windows::Foundation::Numerics::float3 From() const;
		void From(Windows::Foundation::Numerics::float3 const& value);

		Windows::Foundation::Numerics::float3 To() const;
		void To(Windows::Foundation::Numerics::float3 const& value);

    private:
		Microsoft::UI::Xaml::Media::Animation::EasingMode m_easingMode{};
		Windows::Foundation::Numerics::float3 m_from{};
		Windows::Foundation::Numerics::float3 m_to{};
	};
}

namespace winrt::WinUI3Package::UI::Xaml::Media::Animations::factory_implementation
{
	struct OffsetAnimation : winrt::WinUI3Package::UI::Xaml::Media::Animations::factory_implementation::OffsetAnimationT<OffsetAnimation, implementation::OffsetAnimation>
	{
	};
}
