#include "pch.h"
#include "ComboBoxHelper.h"
#if __has_include("ComboBoxHelper.g.cpp")
#include "ComboBoxHelper.g.cpp"
#endif
#include "VisualTreeHelper.hpp"
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include <winrt/Microsoft.UI.Content.h>
#include <unordered_map>

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty ComboBoxHelper::s_acrylicWorkaroundProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"AcrylicWorkaround",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr, 
				&ComboBoxHelper::acrylicWorkaroundChanged
			}
		);

	winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration ComboBoxHelper::m_configuration = 
		[]() 
		{
			winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration configuration;
			configuration.IsInputActive(true);
			return configuration;
		}();

	winrt::Microsoft::UI::Xaml::DependencyProperty ComboBoxHelper::AcrylicWorkaroundProperty()
	{
		return s_acrylicWorkaroundProperty;
	}

	bool ComboBoxHelper::GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::ComboBox const& comboBox)
	{
		return winrt::unbox_value<bool>(comboBox.GetValue(AcrylicWorkaroundProperty()));
	}

	void ComboBoxHelper::SetAcrylicWorkaround(
		winrt::Microsoft::UI::Xaml::Controls::ComboBox const& comboBox,
		bool value
	)
	{
		comboBox.SetValue(AcrylicWorkaroundProperty(), winrt::box_value(value));
	}

	struct AcrylicInfo
	{
		winrt::Microsoft::UI::Content::ContentExternalBackdropLink backdropLink{ nullptr };
		winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicController controller{ nullptr };
	};

	std::unordered_map<winrt::Microsoft::UI::Xaml::Controls::ComboBox, AcrylicInfo> s_maps;

	void ComboBoxHelper::acrylicWorkaroundChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& object, 
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg)
	{
		auto const acrylicWorkaround = winrt::unbox_value<bool>(arg.NewValue());
		if (!acrylicWorkaround)
			return;

		auto comboBox = object.as<winrt::Microsoft::UI::Xaml::Controls::ComboBox>();
		comboBox.Loaded([](winrt::Windows::Foundation::IInspectable const& comboBoxRef, auto&&...) {
			auto comboBox = comboBoxRef.as<winrt::Microsoft::UI::Xaml::Controls::ComboBox>();
			auto popup = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Primitives::Popup>(comboBox, L"Popup");
			if (!popup) return;

			popup.Opened(
				[
					border = popup.FindName(L"PopupBorder").as<winrt::Microsoft::UI::Xaml::Controls::Border>(), 
					comboBoxWeak = winrt::make_weak(comboBox), 
					called = false
				](auto&...) mutable
				{
					//only set the visual once
					if (called)
						return;

					called = true;
					auto size = border.ActualSize();

					auto originalChild = border.Child();
					winrt::Microsoft::UI::Xaml::Controls::Grid scrollGrid;
					scrollGrid.Width(size.x);
					scrollGrid.Height(size.y);
					border.Child(scrollGrid);


					winrt::Microsoft::UI::Xaml::Controls::Grid visualGrid;
					scrollGrid.Children().Append(visualGrid);
					scrollGrid.Children().Append(originalChild);

					auto compositor = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(border).Compositor();

					AcrylicInfo info
					{
						.backdropLink = winrt::Microsoft::UI::Content::ContentExternalBackdropLink::Create(compositor),
						.controller = {}
					};

					info.backdropLink.ExternalBackdropBorderMode(winrt::Microsoft::UI::Composition::CompositionBorderMode::Soft);
					
					auto placementVisual = info.backdropLink.PlacementVisual();
					placementVisual.Size(size);
					placementVisual.Clip(compositor.CreateRectangleClip(
						0.f,
						0.f,
						size.x,
						size.y - 2,
						{ ComboBoxCornerRadius, ComboBoxCornerRadius },
						{ ComboBoxCornerRadius, ComboBoxCornerRadius },
						{ ComboBoxCornerRadius, ComboBoxCornerRadius },
						{ ComboBoxCornerRadius, ComboBoxCornerRadius }
					));
					placementVisual.BorderMode(winrt::Microsoft::UI::Composition::CompositionBorderMode::Soft);

					//Add this placementVisual to Grid's ContainerVisual
					winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(visualGrid)
						.as<winrt::Microsoft::UI::Composition::ContainerVisual>()
						.Children()
						.InsertAtTop(placementVisual);

					info.controller.AddSystemBackdropTarget(
						info.backdropLink.as<winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop>()
					);
					info.controller.SetSystemBackdropConfiguration(m_configuration);

					s_maps[comboBoxWeak.get()] = info;
				});

			//We need to programmatically open it once, otherwise it will close when we first set its visual, not sure why
			//IsEditable=True is an exception, it will open if we programatically open it
			if (!comboBox.IsEditable())
				comboBox.IsDropDownOpen(true);
		});

		//clean up the dictionary
		comboBox.Unloaded([](winrt::Windows::Foundation::IInspectable const& comboBoxRef, auto&&...)
		{
			s_maps.erase(comboBoxRef.as<winrt::Microsoft::UI::Xaml::Controls::ComboBox>());
		});
	}
}
