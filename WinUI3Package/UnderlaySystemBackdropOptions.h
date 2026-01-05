#pragma once

#include "UnderlaySystemBackdropOptions.g.h"

namespace winrt::WinUI3Package::implementation
{
	struct UnderlaySystemBackdropOptions : UnderlaySystemBackdropOptionsT<UnderlaySystemBackdropOptions>
	{
		UnderlaySystemBackdropOptions();

		// CoverMode 属性
		WinUI3Package::UnderlayCoverMode CoverMode() const
		{
			return _CoverMode;
		}

		void CoverMode(const WinUI3Package::UnderlayCoverMode& value)
		{
			if (_CoverMode != value)
			{
				_CoverMode = value;
			}
		}

		// OpacityTransition 属性
		winrt::Microsoft::UI::Xaml::ScalarTransition OpacityTransition() const
		{
			return _OpacityTransition;
		}

		void OpacityTransition(const winrt::Microsoft::UI::Xaml::ScalarTransition& value)
		{
			if (_OpacityTransition != value)
			{
				_OpacityTransition = value;
			}
		}

	private:
		WinUI3Package::UnderlayCoverMode _CoverMode;
		winrt::Microsoft::UI::Xaml::ScalarTransition _OpacityTransition;
	};
}

namespace winrt::WinUI3Package::factory_implementation
{
	struct UnderlaySystemBackdropOptions : UnderlaySystemBackdropOptionsT<UnderlaySystemBackdropOptions, implementation::UnderlaySystemBackdropOptions>
	{
	};
}