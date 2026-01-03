#include "pch.h"
#include "UnderlaySmokeLayerOptions.h"
#if __has_include("UnderlaySmokeLayerOptions.g.cpp")
#include "UnderlaySmokeLayerOptions.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	UnderlaySmokeLayerOptions::UnderlaySmokeLayerOptions() {

		SmokeLayerKind(WinUI3Package::WindowedContentDialogSmokeLayerKind::Darken);


		auto Transition = Microsoft::UI::Xaml::ScalarTransition();
		Transition.Duration(std::chrono::milliseconds(250));

		OpacityTransition(Transition);
	}
}
