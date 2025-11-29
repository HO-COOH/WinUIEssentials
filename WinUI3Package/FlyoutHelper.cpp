#include "pch.h"
#include "FlyoutHelper.h"
#if __has_include("FlyoutHelper.g.cpp")
#include "FlyoutHelper.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty FlyoutHelper::s_acrylicWorkaroundProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"AcrylicWorkaround",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr,
				&FlyoutHelper::acrylicWorkaroundChanged
			}
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty FlyoutHelper::AcrylicWorkaroundProperty()
	{
		return s_acrylicWorkaroundProperty;
	}

	bool FlyoutHelper::GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::Flyout const& flyout)
	{
		return winrt::unbox_value<bool>(flyout.GetValue(AcrylicWorkaroundProperty()));
	}

	void FlyoutHelper::SetAcrylicWorkaround(
		winrt::Microsoft::UI::Xaml::Controls::Flyout const& flyout,
		bool value
	)
	{
		flyout.SetValue(AcrylicWorkaroundProperty(), winrt::box_value(value));
	}

	void FlyoutHelper::acrylicWorkaroundChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& object,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg)
	{

		auto const acrylicWorkaround = winrt::unbox_value<bool>(arg.NewValue());

		if (!acrylicWorkaround)
			return;

		auto Flyout = object.as<winrt::Microsoft::UI::Xaml::Controls::Flyout>();


		auto defaultStyle = winrt::Microsoft::UI::Xaml::Application::Current().Resources()
			.TryLookup(winrt::box_value(L"DefaultFlyoutPresenterStyle"))
			.try_as<winrt::Microsoft::UI::Xaml::Style>();

		if (!defaultStyle) return;


		winrt::Microsoft::UI::Xaml::Style transparentStyle{
			winrt::xaml_typename<winrt::Microsoft::UI::Xaml::Controls::FlyoutPresenter>()
		};

		transparentStyle.BasedOn(defaultStyle);
		
		transparentStyle.Setters().Append(
			winrt::Microsoft::UI::Xaml::Setter(
				winrt::Microsoft::UI::Xaml::Controls::Control::BackgroundProperty(),
				winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::Colors::Transparent())
			)
		);

		Flyout.FlyoutPresenterStyle(transparentStyle);
		Flyout.ShouldConstrainToRootBounds(false);
		Flyout.SystemBackdrop(Microsoft::UI::Xaml::Media::DesktopAcrylicBackdrop());

	}
}
