#include "pch.h"
#include "OpacityAnimation.h"
#if __has_include("UI/Xaml/Media/Animations/OpacityAnimation.g.cpp")
#include "UI/Xaml/Media/Animations/OpacityAnimation.g.cpp"
#endif

using namespace winrt;

namespace winrt::WinUI3Package::UI::Xaml::Media::Animations::implementation
{
	OpacityAnimation::OpacityAnimation()
	{
	}

	Microsoft::UI::Xaml::Media::Animation::EasingMode OpacityAnimation::EasingMode() const
	{
		return m_easingMode;
	}

	void OpacityAnimation::EasingMode(Microsoft::UI::Xaml::Media::Animation::EasingMode const& value)
	{
		m_easingMode = value;
	}

	double OpacityAnimation::From() const
	{
		return m_from;
	}

	void OpacityAnimation::From(double value)
	{
		m_from = value;
	}

	double OpacityAnimation::To() const
	{
		return m_to;
	}

	void OpacityAnimation::To(double value)
	{
		m_to = value;
	}
}
