#include "pch.h"
#include "BindingHelper.h"
#include <winrt/Microsoft.UI.Xaml.h>

namespace BindingHelper
{
	void BindTheme(
		winrt::Microsoft::UI::Xaml::FrameworkElement const& source,
		winrt::Microsoft::UI::Xaml::FrameworkElement const& target
	)
	{
		target.ActualThemeChanged([weakSource = winrt::make_weak(source)](winrt::Microsoft::UI::Xaml::FrameworkElement const& sender, auto&&)
		{
			if (auto source = weakSource.get())
				source.RequestedTheme(sender.ActualTheme());
		});
	}
}
