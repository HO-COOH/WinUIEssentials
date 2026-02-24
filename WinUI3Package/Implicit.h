#pragma once

#include "UI/Xaml/Media/Animations/Implicit.g.h"

namespace winrt::WinUI3Package::UI::Xaml::Media::Animations::implementation
{
	struct Implicit : ImplicitT<Implicit>
	{
		Implicit();

		static winrt::Microsoft::UI::Xaml::DependencyProperty ShowAnimationsProperty();
		static winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet GetShowAnimations(winrt::Microsoft::UI::Xaml::UIElement const& obj);
		static void SetShowAnimations(winrt::Microsoft::UI::Xaml::UIElement const& obj, winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet const& value);

		static winrt::Microsoft::UI::Xaml::DependencyProperty HideAnimationsProperty();
		static winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet GetHideAnimations(winrt::Microsoft::UI::Xaml::UIElement const& obj);
		static void SetHideAnimations(winrt::Microsoft::UI::Xaml::UIElement const& obj, winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet const& value);

		static winrt::Microsoft::UI::Xaml::DependencyProperty AnimationsProperty();
		static winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet GetAnimations(winrt::Microsoft::UI::Xaml::UIElement const& obj);
		static void SetAnimations(winrt::Microsoft::UI::Xaml::UIElement const& obj, winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet const& value);
	};
}

namespace winrt::WinUI3Package::UI::Xaml::Media::Animations::factory_implementation
{
	struct Implicit : winrt::WinUI3Package::UI::Xaml::Media::Animations::factory_implementation::ImplicitT<Implicit, implementation::Implicit>
	{
	};
}
