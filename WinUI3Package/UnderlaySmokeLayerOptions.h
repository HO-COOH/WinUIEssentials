#pragma once

#include "UnderlaySmokeLayerOptions.g.h"

namespace winrt::WinUI3Package::implementation
{
	struct UnderlaySmokeLayerOptions : UnderlaySmokeLayerOptionsT<UnderlaySmokeLayerOptions>
	{
		UnderlaySmokeLayerOptions();

		// SmokeLayerKind 属性
		WinUI3Package::WindowedContentDialogSmokeLayerKind SmokeLayerKind() const
		{
			return _SmokeLayerKind;
		}

		void SmokeLayerKind(const WinUI3Package::WindowedContentDialogSmokeLayerKind& value)
		{
			if (_SmokeLayerKind != value)
			{
				_SmokeLayerKind = value;
			}
		}

		// CustomSmokeLayer 属性
		Microsoft::UI::Xaml::UIElement CustomSmokeLayer() const
		{
			return _CustomSmokeLayer;
		}

		void CustomSmokeLayer(const Microsoft::UI::Xaml::UIElement& value)
		{
			if (_CustomSmokeLayer != value)
			{
				_CustomSmokeLayer = value;
			}
		}

		// OpacityTransition 属性
		Microsoft::UI::Xaml::ScalarTransition OpacityTransition() const
		{
			return _OpacityTransition;
		}

		void OpacityTransition(const Microsoft::UI::Xaml::ScalarTransition& value)
		{
			if (_OpacityTransition != value)
			{
				_OpacityTransition = value;
			}
		}

	private:
		WinUI3Package::WindowedContentDialogSmokeLayerKind _SmokeLayerKind;
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