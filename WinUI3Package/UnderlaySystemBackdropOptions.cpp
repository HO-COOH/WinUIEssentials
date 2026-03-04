#include "pch.h"
#include "UnderlaySystemBackdropOptions.h"
#if __has_include("UnderlaySystemBackdropOptions.g.cpp")
#include "UnderlaySystemBackdropOptions.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	UnderlaySystemBackdropOptions::UnderlaySystemBackdropOptions() 
	{
		_OpacityTransition.Duration(std::chrono::milliseconds(150));
	}

	WinUI3Package::UnderlayCoverMode UnderlaySystemBackdropOptions::CoverMode() const
	{
		return _CoverMode;
	}

	void UnderlaySystemBackdropOptions::CoverMode(WinUI3Package::UnderlayCoverMode value)
	{
		if (_CoverMode != value)
		{
			_CoverMode = value;
		}
	}

	winrt::Microsoft::UI::Xaml::ScalarTransition UnderlaySystemBackdropOptions::OpacityTransition() const
	{
		return _OpacityTransition;
	}

	void UnderlaySystemBackdropOptions::OpacityTransition(winrt::Microsoft::UI::Xaml::ScalarTransition const& value)
	{
		if (_OpacityTransition != value)
		{
			_OpacityTransition = value;
		}
	}
}
