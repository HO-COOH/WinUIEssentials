#pragma once
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Windows.UI.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>

namespace ContentDialogUtils 
{
	winrt::Microsoft::UI::Xaml::Style DefaultButtonStyle();
	winrt::Windows::UI::Color SmokeFillColor();
	winrt::Microsoft::UI::Xaml::Controls::Primitives::Popup CreatePopup(
		winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot, 
		bool isFullCover, 
		double verticalOffset
	);
};
