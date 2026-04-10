#include "pch.h"
#include "UnderlayElement.h"

winrt::Microsoft::UI::Composition::ScalarKeyFrameAnimation UnderlayElement::getShowAnimation(winrt::Microsoft::UI::Composition::Compositor const& compositor)
{
	auto opacityAnimation = compositor.CreateScalarKeyFrameAnimation();
	opacityAnimation.InsertKeyFrame(0.f, 0.f);
	opacityAnimation.InsertKeyFrame(1.f, 1.f);
	opacityAnimation.Target(L"Opacity");
	opacityAnimation.Duration(std::chrono::milliseconds(500));

	return opacityAnimation;
}

winrt::Microsoft::UI::Composition::ScalarKeyFrameAnimation UnderlayElement::getHideAnimation(winrt::Microsoft::UI::Composition::Compositor const& compositor)
{
	auto opacityAnimation = compositor.CreateScalarKeyFrameAnimation();
	opacityAnimation.InsertKeyFrame(0.f, 1.f);
	opacityAnimation.InsertKeyFrame(1.f, 0.f);
	opacityAnimation.Target(L"Opacity");
	opacityAnimation.Duration(std::chrono::milliseconds(500));
	return opacityAnimation;
}

UnderlayElement::UnderlayElement(winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot, winrt::Microsoft::UI::Xaml::FrameworkElement const& popupContent)
{
	ShouldConstrainToRootBounds(false);
	XamlRoot(xamlRoot);
	auto const size = xamlRoot.Size();
	popupContent.Width(size.Width);
	popupContent.Height(size.Height);
	auto const visual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(popupContent);
	auto const compositor = visual.Compositor();
	winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetImplicitShowAnimation(popupContent, getShowAnimation(compositor));
	winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetImplicitHideAnimation(popupContent, getHideAnimation(compositor));
	Child(popupContent);
	IsOpen(true);
}
