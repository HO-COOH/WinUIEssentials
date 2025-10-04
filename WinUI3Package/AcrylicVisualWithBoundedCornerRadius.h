#pragma once

class AcrylicVisualWithBoundedCornerRadius : public winrt::WinUI3Package::AcrylicVisual
{
public:
	template<typename Control>
	AcrylicVisualWithBoundedCornerRadius(Control&& element)
	{
		winrt::Microsoft::UI::Xaml::Data::Binding cornerRadiusBinding;
		cornerRadiusBinding.Source(element);
		cornerRadiusBinding.Path(winrt::Microsoft::UI::Xaml::PropertyPath{ L"CornerRadius" });
		SetBinding(
			winrt::Microsoft::UI::Xaml::Controls::Control::CornerRadiusProperty(),
			cornerRadiusBinding
		);
	}
};
