#include "pch.h"
#include "OffsetAnimation.h"
#if __has_include("UI/Xaml/Media/Animations/OffsetAnimation.g.cpp")
#include "UI/Xaml/Media/Animations/OffsetAnimation.g.cpp"
#endif

using namespace winrt;

namespace winrt::WinUI3Package::UI::Xaml::Media::Animations::implementation
{
	OffsetAnimation::OffsetAnimation()
	{
	}

	Microsoft::UI::Xaml::Media::Animation::EasingMode OffsetAnimation::EasingMode() const
	{
		return m_easingMode;
	}

	void OffsetAnimation::EasingMode(Microsoft::UI::Xaml::Media::Animation::EasingMode const& value)
	{
		m_easingMode = value;
	}

	Windows::Foundation::Numerics::float3 OffsetAnimation::From() const
	{
		return m_from;
	}

	void OffsetAnimation::From(Windows::Foundation::Numerics::float3 const& value)
	{
		m_from = value;
	}

	Windows::Foundation::Numerics::float3 OffsetAnimation::To() const
	{
		return m_to;
	}

	void OffsetAnimation::To(Windows::Foundation::Numerics::float3 const& value)
	{
		m_to = value;
	}
}
