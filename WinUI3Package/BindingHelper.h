#pragma once

namespace winrt::Microsoft::UI::Xaml
{
	struct DependencyProperty;
	struct FrameworkElement;
	struct PropertyPath;
}

namespace BindingHelper
{
	void BindTheme(
		winrt::Microsoft::UI::Xaml::FrameworkElement const& source,
		winrt::Microsoft::UI::Xaml::FrameworkElement const& target
	);

	void Bind(
		winrt::Microsoft::UI::Xaml::FrameworkElement const& source,
		winrt::Microsoft::UI::Xaml::DependencyProperty const& sourceProperty,
		winrt::Microsoft::UI::Xaml::PropertyPath const& targetProperty,
		winrt::Microsoft::UI::Xaml::FrameworkElement const& target
	);

	void Bind(
		winrt::Microsoft::UI::Xaml::FrameworkElement const& source,
		winrt::Microsoft::UI::Xaml::DependencyProperty const& sourceProperty,
		wchar_t const* targetProperty,
		winrt::Microsoft::UI::Xaml::FrameworkElement const& target
	);
}