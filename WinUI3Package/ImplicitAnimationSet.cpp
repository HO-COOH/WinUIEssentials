#include "pch.h"
#include "ImplicitAnimationSet.h"
#if __has_include("UI/Xaml/Media/Animations/ImplicitAnimationSet.g.cpp")
#include "UI/Xaml/Media/Animations/ImplicitAnimationSet.g.cpp"
#endif

using namespace winrt;

namespace winrt::WinUI3Package::UI::Xaml::Media::Animations::implementation
{
	ImplicitAnimationSet::ImplicitAnimationSet()
	{
		m_children = Microsoft::UI::Xaml::Media::Animation::TimelineCollection{};
	}

	Microsoft::UI::Xaml::Media::Animation::TimelineCollection ImplicitAnimationSet::Children()
	{
		return m_children;
	}
}
