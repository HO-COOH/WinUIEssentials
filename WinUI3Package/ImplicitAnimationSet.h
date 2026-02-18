#pragma once

#include "UI/Xaml/Media/Animations/ImplicitAnimationSet.g.h"

namespace winrt::WinUI3Package::UI::Xaml::Media::Animations::implementation
{
	struct ImplicitAnimationSet : ImplicitAnimationSetT<ImplicitAnimationSet>
	{
		ImplicitAnimationSet();

		Microsoft::UI::Xaml::Media::Animation::TimelineCollection Children();

	private:
		Microsoft::UI::Xaml::Media::Animation::TimelineCollection m_children{ nullptr };
	};
}

namespace winrt::WinUI3Package::UI::Xaml::Media::Animations::factory_implementation
{
	struct ImplicitAnimationSet : winrt::WinUI3Package::UI::Xaml::Media::Animations::factory_implementation::ImplicitAnimationSetT<ImplicitAnimationSet, implementation::ImplicitAnimationSet>
	{
	};
}
