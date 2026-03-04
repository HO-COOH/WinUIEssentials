#pragma once

#include "UnderlaySystemBackdropOptions.g.h"

namespace winrt::WinUI3Package::implementation
{
	struct UnderlaySystemBackdropOptions : UnderlaySystemBackdropOptionsT<UnderlaySystemBackdropOptions>
	{
		UnderlaySystemBackdropOptions();

		WinUI3Package::UnderlayCoverMode CoverMode() const;
		void CoverMode(WinUI3Package::UnderlayCoverMode value);

		winrt::Microsoft::UI::Xaml::ScalarTransition OpacityTransition() const;
		void OpacityTransition(winrt::Microsoft::UI::Xaml::ScalarTransition const& value);

	private:
		WinUI3Package::UnderlayCoverMode _CoverMode{ winrt::WinUI3Package::UnderlayCoverMode::ClientArea };
		winrt::Microsoft::UI::Xaml::ScalarTransition _OpacityTransition;
	};
}

namespace winrt::WinUI3Package::factory_implementation
{
	struct UnderlaySystemBackdropOptions : UnderlaySystemBackdropOptionsT<UnderlaySystemBackdropOptions, implementation::UnderlaySystemBackdropOptions>
	{
	};
}