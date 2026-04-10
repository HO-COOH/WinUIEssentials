#pragma once
#include <chrono>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Composition.h>

//Popup is a sealed class so it cannot be derived. So we inherit for convenience. Use with caution as it breaks ref counting in specific scenario
class UnderlayElement : public winrt::Microsoft::UI::Xaml::Controls::Primitives::Popup
{
	winrt::Microsoft::UI::Composition::ScalarKeyFrameAnimation getShowAnimation(winrt::Microsoft::UI::Composition::Compositor const& compositor);
	winrt::Microsoft::UI::Composition::ScalarKeyFrameAnimation getHideAnimation(winrt::Microsoft::UI::Composition::Compositor const& compositor);
public:
	UnderlayElement(std::nullptr_t) : Popup{ nullptr } {}
	UnderlayElement(winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot, winrt::Microsoft::UI::Xaml::FrameworkElement const& popupContent);
};