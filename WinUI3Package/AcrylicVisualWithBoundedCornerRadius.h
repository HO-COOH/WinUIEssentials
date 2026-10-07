#pragma once
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>

template<typename AcrylicVisualType = winrt::WinUI3Package::AcrylicVisual>
class AcrylicVisualWithBoundedCornerRadius : public AcrylicVisualType
{
public:
	template<typename Control>
	AcrylicVisualWithBoundedCornerRadius(Control&& element)
	{
		winrt::Microsoft::UI::Xaml::Data::Binding cornerRadiusBinding;
		cornerRadiusBinding.Source(element);
		cornerRadiusBinding.Path(winrt::Microsoft::UI::Xaml::PropertyPath{ L"CornerRadius" });
		AcrylicVisualType::SetBinding(
			winrt::Microsoft::UI::Xaml::Controls::Control::CornerRadiusProperty(),
			cornerRadiusBinding
		);
	}
};
