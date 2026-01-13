#include "pch.h"
#include "NavigationViewHelper.h"
#if __has_include("NavigationViewHelper.g.cpp")
#include "NavigationViewHelper.g.cpp"
#endif
#include "include/VisualTreeHelper.hpp"

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty NavigationViewHelper::s_acrylicWorkaroundProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"AcrylicWorkaround",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<winrt::Microsoft::UI::Xaml::Controls::NavigationView>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata(
				winrt::box_value(false),
				winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&NavigationViewHelper::acrylicWorkaroundChanged)
			)
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty NavigationViewHelper::AcrylicWorkaroundProperty()
	{
		return s_acrylicWorkaroundProperty;
	}

	bool NavigationViewHelper::GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& navigationView)
	{
		return winrt::unbox_value<bool>(navigationView.GetValue(AcrylicWorkaroundProperty()));
	}

	void NavigationViewHelper::SetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& navigationView, bool value)
	{
		navigationView.SetValue(AcrylicWorkaroundProperty(), winrt::box_value(value));
	}

	void NavigationViewHelper::acrylicWorkaroundChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& object, 
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg)
	{
		auto const value = winrt::unbox_value<bool>(arg.NewValue());
		if (!value)
			return;

		auto loadedRevoker = std::make_shared<winrt::Microsoft::UI::Xaml::FrameworkElement::Loaded_revoker>();
		*loadedRevoker = object.as<winrt::Microsoft::UI::Xaml::Controls::NavigationView>().Loaded(winrt::auto_revoke, [loadedRevoker](auto const& sender, auto const&)
		{
			auto navigationView = sender.as<winrt::Microsoft::UI::Xaml::Controls::NavigationView>();
			auto button = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Button>(navigationView, L"TopNavOverflowButton");
			auto flyout = button.Flyout().as<winrt::Microsoft::UI::Xaml::Controls::Flyout>();

			auto newStyle = getStyle(flyout.FlyoutPresenterStyle());

			flyout.FlyoutPresenterStyle(newStyle);
			flyout.Opening(&onFlyoutOpened);
			modifyNavigationViewItems(navigationView, newStyle);
			loadedRevoker->revoke();
		});
	}

	void NavigationViewHelper::modifyNavigationViewItems(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& navigationView, winrt::Microsoft::UI::Xaml::Style const& newStyle)
	{
		for (auto item : navigationView.MenuItems())
		{
			auto navigationViewItem = item.as<winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem>();
			auto rootGrid = winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetChild(navigationViewItem, 0);
			if (!rootGrid)
				continue;

			auto attachedFlyout = winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase::GetAttachedFlyout(rootGrid.as<winrt::Microsoft::UI::Xaml::FrameworkElement>());
			if (!attachedFlyout)
				continue;

			auto flyout = attachedFlyout.try_as<winrt::Microsoft::UI::Xaml::Controls::Flyout>();
			if (!flyout)
				continue;

			flyout.FlyoutPresenterStyle(newStyle);
			flyout.Opening(&onFlyoutOpened);
		}
	}

	void NavigationViewHelper::onFlyoutOpened(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const&)
	{
		auto flyout = sender.as<winrt::Microsoft::UI::Xaml::Controls::Flyout>();
		auto content = flyout.Content();
		if (!content)
			return;

		auto itemsRepeaterScrollHost = content.try_as<winrt::Microsoft::UI::Xaml::Controls::ItemsRepeaterScrollHost>();
		if (!itemsRepeaterScrollHost)
			return;

		itemsRepeaterScrollHost.ScrollViewer().Background(nullptr);
	}

	winrt::Microsoft::UI::Xaml::Style NavigationViewHelper::getStyle(winrt::Microsoft::UI::Xaml::Style const& defaultNavigationViewFlyoutStyle)
	{
		//The original FlyoutPresenter style cannot be used directly, or it will not have acrylic, I tried.
		//It must be based from the DefaultFlyoutPresenterStyle

		winrt::Microsoft::UI::Xaml::Style newStyle
		{
			winrt::xaml_typename<winrt::Microsoft::UI::Xaml::Controls::FlyoutPresenter>()
		};

		if (auto defaultFlyoutStyle = winrt::Microsoft::UI::Xaml::Application::Current().Resources().TryLookup(winrt::box_value(L"DefaultFlyoutPresenterStyle")))
			newStyle.BasedOn(defaultFlyoutStyle.try_as<winrt::Microsoft::UI::Xaml::Style>());

		auto setters = newStyle.Setters();

		//Add back some original styles for consistency
		for (auto setter : defaultNavigationViewFlyoutStyle.Setters())
		{
			if (auto targetProperty = setter.as<winrt::Microsoft::UI::Xaml::Setter>().Property();
				targetProperty == winrt::Microsoft::UI::Xaml::Controls::Control::CornerRadiusProperty() ||
				targetProperty == winrt::Microsoft::UI::Xaml::Controls::Control::PaddingProperty())
			{
				setters.Append(setter);
			}
		}

		setters.Append(winrt::Microsoft::UI::Xaml::Setter
		{
			winrt::Microsoft::UI::Xaml::Controls::Control::BackgroundProperty(),
			winrt::Microsoft::UI::Xaml::Media::SolidColorBrush{ winrt::Windows::UI::Colors::Transparent() }
		});

		return newStyle;
	}
}
