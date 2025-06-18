#include "pch.h"
#include "AutoSuggestBoxHelper.h"
#if __has_include("AutoSuggestBoxHelper.g.cpp")
#include "AutoSuggestBoxHelper.g.cpp"
#endif
#include "VisualTreeHelper.hpp"
#include "AcrylicVisual.h"

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty AutoSuggestBoxHelper::s_acrylicWorkaroundProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"AcrylicWorkaround",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr,
				&AutoSuggestBoxHelper::acrylicWorkaroundChanged
			}
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty AutoSuggestBoxHelper::AcrylicWorkaroundProperty()
	{
		return s_acrylicWorkaroundProperty;
	}

	bool AutoSuggestBoxHelper::GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& autoSuggestBox)
	{
		return winrt::unbox_value<bool>(autoSuggestBox.GetValue(AcrylicWorkaroundProperty()));
	}

	void AutoSuggestBoxHelper::SetAcrylicWorkaround(
		winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& autoSuggestBox,
		bool value
	)
	{
		autoSuggestBox.SetValue(AcrylicWorkaroundProperty(), winrt::box_value(value));
	}

	static void adjustVisual(winrt::WinUI3Package::AcrylicVisual const& visual, winrt::Microsoft::UI::Xaml::CornerRadius cornerRadius)
	{
		visual.CornerRadius(cornerRadius);
		//OutputDebugString(std::format(L"CornerRadius: {}, {}, {}, {}\n", cornerRadius.TopLeft, cornerRadius.TopRight, cornerRadius.BottomRight, cornerRadius.BottomLeft).data());
	}

	void AutoSuggestBoxHelper::acrylicWorkaroundChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& object,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg)
	{
		auto const acrylicWorkaround = winrt::unbox_value<bool>(arg.NewValue());
		if (!acrylicWorkaround)
			return;

		auto autoSuggestBox = object.as<winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox>();
		autoSuggestBox.LayoutUpdated([autoSuggestBoxRef = winrt::make_weak(autoSuggestBox), called = false](auto&&...) mutable
		{
			if (called) return;

			auto popup = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Primitives::Popup>(
				autoSuggestBoxRef.get().as<winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox>(), 
				L"SuggestionsPopup"
			);
			if (!popup) return;

			called = true;
			auto border = popup.FindName(L"SuggestionsContainer").as<winrt::Microsoft::UI::Xaml::Controls::Border>();
			border.Padding({});
			border.Background(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush{ winrt::Windows::UI::Colors::Transparent() });
			border.SizeChanged([called = false, popup = winrt::make_weak(popup), visualRef = winrt::weak_ref<winrt::WinUI3Package::AcrylicVisual>{}](auto const& borderRef, winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& args) mutable
			{
				if (called)
				{
					if (auto visual = visualRef.get())
						adjustVisual(visual, borderRef.as<winrt::Microsoft::UI::Xaml::Controls::Border>().CornerRadius());
					return;
				}

				auto border = borderRef.as<winrt::Microsoft::UI::Xaml::Controls::Border>();
				if (auto const newSize = args.NewSize(); newSize.Width == 0 || newSize.Height == 0)
					return;
				called = true;

				auto originalChild = border.Child();
				winrt::Microsoft::UI::Xaml::Controls::Grid scrollGrid;
				border.Child(scrollGrid);

				winrt::WinUI3Package::AcrylicVisual visual;
				adjustVisual(visual, border.CornerRadius());
				visualRef = visual;
				scrollGrid.Children().ReplaceAll({ visual, originalChild });
			});
		});

	}
}
