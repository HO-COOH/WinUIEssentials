#pragma once

#include "UnderlaySmokeLayerOptions.g.h"

namespace winrt::WinUI3Package::implementation
{
	struct UnderlaySmokeLayerOptions : UnderlaySmokeLayerOptionsT<UnderlaySmokeLayerOptions>
	{
		UnderlaySmokeLayerOptions();

		WinUI3Package::WindowedContentDialogSmokeLayerKind SmokeLayerKind() const;
		void SmokeLayerKind(WinUI3Package::WindowedContentDialogSmokeLayerKind value);

		Microsoft::UI::Xaml::UIElement CustomSmokeLayer() const;
		void CustomSmokeLayer(Microsoft::UI::Xaml::UIElement const& value);

		Microsoft::UI::Xaml::ScalarTransition OpacityTransition() const;
		void OpacityTransition(Microsoft::UI::Xaml::ScalarTransition const& value);

	private:
		WinUI3Package::WindowedContentDialogSmokeLayerKind _SmokeLayerKind{ WinUI3Package::WindowedContentDialogSmokeLayerKind::Darken };
		Microsoft::UI::Xaml::UIElement _CustomSmokeLayer{ nullptr };
		Microsoft::UI::Xaml::ScalarTransition _OpacityTransition;
	};
}

namespace winrt::WinUI3Package::factory_implementation
{
	struct UnderlaySmokeLayerOptions : UnderlaySmokeLayerOptionsT<UnderlaySmokeLayerOptions, implementation::UnderlaySmokeLayerOptions>
	{
	};
}