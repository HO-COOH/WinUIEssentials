#include "pch.h"
#include "UnderlaySmokeLayerOptions.h"
#if __has_include("UnderlaySmokeLayerOptions.g.cpp")
#include "UnderlaySmokeLayerOptions.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	UnderlaySmokeLayerOptions::UnderlaySmokeLayerOptions() 
	{
		SmokeLayerKind(WinUI3Package::WindowedContentDialogSmokeLayerKind::Darken);
		_OpacityTransition.Duration(std::chrono::milliseconds(250));
	}

	WinUI3Package::WindowedContentDialogSmokeLayerKind UnderlaySmokeLayerOptions::SmokeLayerKind() const
	{
		return _SmokeLayerKind;
	}

	void UnderlaySmokeLayerOptions::SmokeLayerKind(WinUI3Package::WindowedContentDialogSmokeLayerKind value)
	{
		if (_SmokeLayerKind != value)
		{
			_SmokeLayerKind = value;
		}
	}

	Microsoft::UI::Xaml::UIElement UnderlaySmokeLayerOptions::CustomSmokeLayer() const
	{
		return _CustomSmokeLayer;
	}

	void UnderlaySmokeLayerOptions::CustomSmokeLayer(Microsoft::UI::Xaml::UIElement const& value)
	{
		if (_CustomSmokeLayer != value)
		{
			_CustomSmokeLayer = value;
		}
	}

	Microsoft::UI::Xaml::ScalarTransition UnderlaySmokeLayerOptions::OpacityTransition() const
	{
		return _OpacityTransition;
	}

	void UnderlaySmokeLayerOptions::OpacityTransition(Microsoft::UI::Xaml::ScalarTransition const& value)
	{
		if (_OpacityTransition != value)
		{
			_OpacityTransition = value;
		}
	}
}
