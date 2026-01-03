#pragma once


namespace ContentDialogUtils {


	static winrt::Microsoft::UI::Xaml::Style DefaultButtonStyle()
	{
		// 获取应用程序当前实例
		auto application = winrt::Microsoft::UI::Xaml::Application::Current();

		// 检查应用程序资源中是否有 DefaultButtonStyle
		if (application && application.Resources().HasKey(winrt::box_value(L"DefaultButtonStyle")))
		{
			return application.Resources().TryLookup(winrt::box_value(L"DefaultButtonStyle")).as<winrt::Microsoft::UI::Xaml::Style>();
		}

		// 如果没有找到，返回 null 或默认样式
		return nullptr;
	}

	static winrt::Windows::UI::Color SmokeFillColor()
	{
		if (auto current = winrt::Microsoft::UI::Xaml::Application::Current())
		{
			if (auto resources = current.Resources())
			{
				if (auto color = resources.TryLookup(winrt::box_value(L"SmokeFillColorDefault")))
				{
					return color.try_as<winrt::Windows::UI::Color>().value_or(winrt::Microsoft::UI::Colors::Black()); // Default fallback
				}
			}
		}
		return winrt::Microsoft::UI::Colors::Black(); // Default fallback color
	}

	static winrt::Microsoft::UI::Xaml::Controls::Primitives::Popup CreatePopup(winrt::Microsoft::UI::Xaml::XamlRoot xamlRoot, bool isFullCover, double verticalOffset) {

		winrt::Microsoft::UI::Xaml::Controls::Primitives::Popup popup = {};
		popup.IsLightDismissEnabled(false);
		popup.XamlRoot(xamlRoot);
		popup.ShouldConstrainToRootBounds(false);

		// Create the overlay Border
		winrt::Microsoft::UI::Xaml::Controls::Border overlay = {};
		overlay.HorizontalAlignment(winrt::Microsoft::UI::Xaml::HorizontalAlignment::Stretch);
		overlay.VerticalAlignment(winrt::Microsoft::UI::Xaml::VerticalAlignment::Stretch);
		overlay.Width(xamlRoot.Size().Width);
		overlay.Height(isFullCover ? xamlRoot.Size().Height : xamlRoot.Size().Height - verticalOffset);
		overlay.Opacity(0.0);

		if (isFullCover)
		{
			overlay.CornerRadius(winrt::Microsoft::UI::Xaml::CornerRadiusHelper::FromUniformRadius(8));
			popup.Margin(winrt::Microsoft::UI::Xaml::ThicknessHelper::FromUniformLength(0));
		}
		else
		{
			if (verticalOffset == 0)
			{
				overlay.CornerRadius(winrt::Microsoft::UI::Xaml::CornerRadiusHelper::FromUniformRadius(8));
			}
			else
			{
				overlay.CornerRadius(winrt::Microsoft::UI::Xaml::CornerRadiusHelper::FromRadii(0, 0, 8, 8));
			}
			popup.Margin(winrt::Microsoft::UI::Xaml::ThicknessHelper::FromLengths(0, verticalOffset, 0, 0));
		}


		// Set system backdrop
		//PopupBackdropManager::TrySetSystemBackdrop(popup, backdropType);

		// Set the child and return
		popup.Child(overlay);
		return popup;

	}

};
