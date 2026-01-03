#include "pch.h"
#include "UnderlaySystemBackdropOptions.h"
#if __has_include("UnderlaySystemBackdropOptions.g.cpp")
#include "UnderlaySystemBackdropOptions.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	UnderlaySystemBackdropOptions::UnderlaySystemBackdropOptions() {

		CoverMode(winrt::WinUI3Package::UnderlayCoverMode::ClientArea);

		auto Transition = Microsoft::UI::Xaml::ScalarTransition();
		Transition.Duration(std::chrono::milliseconds(150));

		OpacityTransition(Transition);
	}
}
