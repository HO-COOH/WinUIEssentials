#include "pch.h"
#include "Implicit.h"
#if __has_include("UI/Xaml/Media/Animations/Implicit.g.cpp")
#include "UI/Xaml/Media/Animations/Implicit.g.cpp"
#endif

#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>

using namespace winrt;

namespace winrt::WinUI3Package::UI::Xaml::Media::Animations::implementation
{
	static Microsoft::UI::Xaml::DependencyProperty s_showAnimationsProperty{ nullptr };
	static Microsoft::UI::Xaml::DependencyProperty s_hideAnimationsProperty{ nullptr };
	static Microsoft::UI::Xaml::DependencyProperty s_implicitAnimationsProperty{ nullptr };

	Implicit::Implicit()
	{
	}

	// ShowAnimations property implementation
	Microsoft::UI::Xaml::DependencyProperty Implicit::ShowAnimationsProperty()
	{
		if (s_showAnimationsProperty)
		{
			return s_showAnimationsProperty;
		}

		s_showAnimationsProperty = Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"ShowAnimations",
			xaml_typename<winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet>(),
			xaml_typename<Microsoft::UI::Xaml::UIElement>(),
			Microsoft::UI::Xaml::PropertyMetadata{ nullptr, Microsoft::UI::Xaml::PropertyChangedCallback{ [](Microsoft::UI::Xaml::DependencyObject const& d, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
			{
				auto uiElement = d.try_as<Microsoft::UI::Xaml::UIElement>();
				if (!uiElement)
				{
					return;
				}

				auto visual = Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(uiElement);

				auto animationSet = e.NewValue().try_as<winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet>();
				if (!animationSet)
				{
					// 清除元素上之前设置的任何隐式*显示*动画
					Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetImplicitShowAnimation(uiElement, nullptr);
					return;
				}

				// Build implicit animation collection for show animations
				auto compositor = visual.Compositor();
				auto collection = compositor.CreateImplicitAnimationCollection();

				for (auto const& child : animationSet.Children())
				{
					if (auto timeline = child.try_as<winrt::Microsoft::UI::Xaml::Media::Animation::ITimeline>())
					{
						auto d = timeline.Duration();
						if (d.Type != winrt::Microsoft::UI::Xaml::DurationType::TimeSpan)
						{
							continue;
						}

						auto duration = d.TimeSpan;

						if (auto offsetAnim = child.try_as<winrt::WinUI3Package::UI::Xaml::Media::Animations::IOffsetAnimation>())
						{
							auto animation = compositor.CreateVector3KeyFrameAnimation();
							animation.Target(L"Offset");
							animation.Duration(duration);
							animation.InsertExpressionKeyFrame(0.0f, L"this.StartingValue");
							animation.InsertExpressionKeyFrame(1.0f, L"this.FinalValue");
							collection.Insert(L"Offset", animation);
						}
						else if (auto opacityAnim = child.try_as<winrt::WinUI3Package::UI::Xaml::Media::Animations::IOpacityAnimation>())
						{
							auto animation = compositor.CreateScalarKeyFrameAnimation();
							animation.Target(L"Opacity");
							animation.Duration(duration);
							animation.InsertExpressionKeyFrame(0.0f, L"this.StartingValue");
							animation.InsertExpressionKeyFrame(1.0f, L"this.FinalValue");
							collection.Insert(L"Opacity", animation);
						}
					}
				}

				visual.ImplicitAnimations(collection);
			} } });

		return s_showAnimationsProperty;
	}

	// HideAnimations property implementation
	Microsoft::UI::Xaml::DependencyProperty Implicit::HideAnimationsProperty()
	{
		if (s_hideAnimationsProperty)
		{
			return s_hideAnimationsProperty;
		}

		s_hideAnimationsProperty = Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"HideAnimations",
			xaml_typename<winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet>(),
			xaml_typename<Microsoft::UI::Xaml::UIElement>(),
			Microsoft::UI::Xaml::PropertyMetadata{ nullptr, Microsoft::UI::Xaml::PropertyChangedCallback{ [](Microsoft::UI::Xaml::DependencyObject const& d, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
			{
				auto uiElement = d.try_as<Microsoft::UI::Xaml::UIElement>();
				if (!uiElement)
				{
					return;
				}

				auto visual = Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(uiElement);

				auto animationSet = e.NewValue().try_as<winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet>();
				if (!animationSet)
				{
					// 清除元素上之前设置的任何隐式*隐藏*动画
					Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetImplicitHideAnimation(uiElement, nullptr);					return;
					return;
				}

				// Build implicit animation collection for hide animations
				auto compositor = visual.Compositor();
				auto collection = compositor.CreateImplicitAnimationCollection();

				for (auto const& child : animationSet.Children())
				{
					if (auto timeline = child.try_as<winrt::Microsoft::UI::Xaml::Media::Animation::ITimeline>())
					{
						auto d = timeline.Duration();
						if (d.Type != winrt::Microsoft::UI::Xaml::DurationType::TimeSpan)
						{
							continue;
						}

						auto duration = d.TimeSpan;

						if (auto offsetAnim = child.try_as<winrt::WinUI3Package::UI::Xaml::Media::Animations::IOffsetAnimation>())
						{
							auto animation = compositor.CreateVector3KeyFrameAnimation();
							animation.Target(L"Offset");
							animation.Duration(duration);
							animation.InsertExpressionKeyFrame(0.0f, L"this.StartingValue");
							animation.InsertExpressionKeyFrame(1.0f, L"this.FinalValue");
							collection.Insert(L"Offset", animation);
						}
						else if (auto opacityAnim = child.try_as<winrt::WinUI3Package::UI::Xaml::Media::Animations::IOpacityAnimation>())
						{
							auto animation = compositor.CreateScalarKeyFrameAnimation();
							animation.Target(L"Opacity");
							animation.Duration(duration);
							animation.InsertExpressionKeyFrame(0.0f, L"this.StartingValue");
							animation.InsertExpressionKeyFrame(1.0f, L"this.FinalValue");
							collection.Insert(L"Opacity", animation);
						}
					}
				}

				visual.ImplicitAnimations(collection);
			} } });

		return s_hideAnimationsProperty;
	}

	// Animations property implementation (general implicit animations)
	Microsoft::UI::Xaml::DependencyProperty Implicit::AnimationsProperty()
	{
		if (s_implicitAnimationsProperty)
		{
			return s_implicitAnimationsProperty;
		}

		s_implicitAnimationsProperty = Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"Animations",
			xaml_typename<winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet>(),
			xaml_typename<Microsoft::UI::Xaml::UIElement>(),
			Microsoft::UI::Xaml::PropertyMetadata{ nullptr, Microsoft::UI::Xaml::PropertyChangedCallback{ [](Microsoft::UI::Xaml::DependencyObject const& d, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
			{
				auto uiElement = d.try_as<Microsoft::UI::Xaml::UIElement>();
				if (!uiElement)
				{
					return;
				}

				auto visual = Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(uiElement);

				auto animationSet = e.NewValue().try_as<winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet>();
				if (!animationSet)
				{
					visual.ImplicitAnimations(nullptr);
					return;
				}

				// Build implicit animation collection for general animations
				auto compositor = visual.Compositor();
				auto collection = compositor.CreateImplicitAnimationCollection();

				for (auto const& child : animationSet.Children())
				{
					if (auto timeline = child.try_as<winrt::Microsoft::UI::Xaml::Media::Animation::ITimeline>())
					{
						auto d = timeline.Duration();
						if (d.Type != winrt::Microsoft::UI::Xaml::DurationType::TimeSpan)
						{
							continue;
						}

						auto duration = d.TimeSpan;

						if (auto offsetAnim = child.try_as<winrt::WinUI3Package::UI::Xaml::Media::Animations::IOffsetAnimation>())
						{
							auto animation = compositor.CreateVector3KeyFrameAnimation();
							animation.Target(L"Offset");
							animation.Duration(duration);
							animation.InsertExpressionKeyFrame(0.0f, L"this.StartingValue");
							animation.InsertExpressionKeyFrame(1.0f, L"this.FinalValue");
							collection.Insert(L"Offset", animation);
						}
						else if (auto opacityAnim = child.try_as<winrt::WinUI3Package::UI::Xaml::Media::Animations::IOpacityAnimation>())
						{
							auto animation = compositor.CreateScalarKeyFrameAnimation();
							animation.Target(L"Opacity");
							animation.Duration(duration);
							animation.InsertExpressionKeyFrame(0.0f, L"this.StartingValue");
							animation.InsertExpressionKeyFrame(1.0f, L"this.FinalValue");
							collection.Insert(L"Opacity", animation);
						}
					}
				}

				visual.ImplicitAnimations(collection);
			} } });

		return s_implicitAnimationsProperty;
	}

	winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet Implicit::GetShowAnimations(Microsoft::UI::Xaml::UIElement const& obj)
	{
		return obj.GetValue(ShowAnimationsProperty()).try_as<winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet>();
	}

	void Implicit::SetShowAnimations(Microsoft::UI::Xaml::UIElement const& obj, winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet const& value)
	{
		obj.SetValue(ShowAnimationsProperty(), value);
	}

	winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet Implicit::GetHideAnimations(Microsoft::UI::Xaml::UIElement const& obj)
	{
		return obj.GetValue(HideAnimationsProperty()).try_as<winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet>();
	}

	void Implicit::SetHideAnimations(Microsoft::UI::Xaml::UIElement const& obj, winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet const& value)
	{
		obj.SetValue(HideAnimationsProperty(), value);
	}

	winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet Implicit::GetAnimations(Microsoft::UI::Xaml::UIElement const& obj)
	{
		return obj.GetValue(AnimationsProperty()).try_as<winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet>();
	}

	void Implicit::SetAnimations(Microsoft::UI::Xaml::UIElement const& obj, winrt::WinUI3Package::UI::Xaml::Media::Animations::ImplicitAnimationSet const& value)
	{
		obj.SetValue(AnimationsProperty(), value);
	}
}
