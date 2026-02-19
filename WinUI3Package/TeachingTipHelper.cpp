#include "pch.h"
#include "TeachingTipHelper.h"
#if __has_include("TeachingTipHelper.g.cpp")
#include "TeachingTipHelper.g.cpp"
#endif

#include "VisualTreeHelper.hpp"
#include "AcrylicVisual.h"
#include "AcrylicVisualWithBoundedCornerRadius.h"

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty TeachingTipHelper::s_acrylicWorkaroundProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"AcrylicWorkaround",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr,
				&TeachingTipHelper::acrylicWorkaroundChanged
			}
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty TeachingTipHelper::AcrylicWorkaroundProperty()
	{
		return s_acrylicWorkaroundProperty;
	}

	bool TeachingTipHelper::GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::TeachingTip const& teachingTip)
	{
		return winrt::unbox_value<bool>(teachingTip.GetValue(AcrylicWorkaroundProperty()));
	}

	void TeachingTipHelper::SetAcrylicWorkaround(
		winrt::Microsoft::UI::Xaml::Controls::TeachingTip const& teachingTip,
		bool value
	)
	{
		teachingTip.SetValue(AcrylicWorkaroundProperty(), winrt::box_value(value));
	}


	void ApplyAcrylicToGrid(winrt::Microsoft::UI::Xaml::Controls::Grid const& grid)
	{
		grid.Background(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(
			winrt::Windows::UI::Colors::Transparent()));

		AcrylicVisualWithBoundedCornerRadius acrylicLayer{ grid };
		winrt::get_self<winrt::WinUI3Package::implementation::AcrylicVisual>(
			static_cast<winrt::WinUI3Package::AcrylicVisual const&>(acrylicLayer)
		)->ClipOffset = { 0, 0, 0, 1 };
		winrt::Microsoft::UI::Xaml::Controls::Grid::SetRow(acrylicLayer, 0);
		winrt::Microsoft::UI::Xaml::Controls::Grid::SetRowSpan(acrylicLayer, 3);

		grid.Children().InsertAt(0, acrylicLayer);
	}

	void PatchTailBorder(
		winrt::Microsoft::UI::Xaml::Controls::Grid const& contentRootGrid,
		winrt::Microsoft::UI::Xaml::Shapes::Polygon const& tailPolygon)
	{
		auto borderBrush = contentRootGrid.BorderBrush();

		auto bottomBorder = winrt::Microsoft::UI::Xaml::Controls::Grid();

		winrt::Microsoft::UI::Xaml::Controls::ColumnDefinition col0;
		col0.Width({ 1, winrt::Microsoft::UI::Xaml::GridUnitType::Star });
		winrt::Microsoft::UI::Xaml::Controls::ColumnDefinition col1;
		col1.Width({ 20, winrt::Microsoft::UI::Xaml::GridUnitType::Pixel });
		winrt::Microsoft::UI::Xaml::Controls::ColumnDefinition col2;
		col2.Width({ 1, winrt::Microsoft::UI::Xaml::GridUnitType::Star });

		bottomBorder.ColumnDefinitions().Append(col0);
		bottomBorder.ColumnDefinitions().Append(col1);
		bottomBorder.ColumnDefinitions().Append(col2);

		auto leftSeg = winrt::Microsoft::UI::Xaml::Controls::Grid();
		leftSeg.Background(borderBrush);
		winrt::Microsoft::UI::Xaml::Controls::Grid::SetColumn(leftSeg, 0);
		bottomBorder.Children().Append(leftSeg);

		auto rightSeg = winrt::Microsoft::UI::Xaml::Controls::Grid();
		rightSeg.Background(borderBrush);
		winrt::Microsoft::UI::Xaml::Controls::Grid::SetColumn(rightSeg, 2);
		bottomBorder.Children().Append(rightSeg);

		double borderHeight = 1;
		bottomBorder.Height(borderHeight);
		bottomBorder.VerticalAlignment(winrt::Microsoft::UI::Xaml::VerticalAlignment::Bottom);
		winrt::Microsoft::UI::Xaml::Controls::Grid::SetRowSpan(bottomBorder, 3);
		contentRootGrid.Children().Append(bottomBorder);

		winrt::Microsoft::UI::Xaml::Media::TranslateTransform transform;
		transform.Y(1);
		tailPolygon.RenderTransform(transform);
	}

	void PatchLightDismissSetters(winrt::Microsoft::UI::Xaml::Controls::Border const& contentRootGrid)
	{
		auto transparentBrush = winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(
			winrt::Windows::UI::Colors::Transparent());

		auto groups = winrt::Microsoft::UI::Xaml::VisualStateManager::GetVisualStateGroups(contentRootGrid);
		if (!groups) return;

		for (auto const& group : groups)
		{
			if (group.Name() != L"LightDismissStates") continue;

			for (auto const& state : group.States())
			{
				if (state.Name() != L"LightDismiss") continue;

				for (auto const& setterBase : state.Setters())
				{
					auto setter = setterBase.try_as<winrt::Microsoft::UI::Xaml::Setter>();
					if (!setter) continue;

					auto target = setter.Target();
					if (!target) continue;

					auto PathName = target.Path().Path();

					if (PathName == L"Background" || PathName == L"Fill")
					{
						setter.Value(transparentBrush);
					}
				}
			}
		}
	}


	void TeachingTipHelper::acrylicWorkaroundChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& object,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg)
	{
		auto const acrylicWorkaround = winrt::unbox_value<bool>(arg.NewValue());

		if (!acrylicWorkaround) return;

		auto teachingTip = object.as<winrt::Microsoft::UI::Xaml::Controls::TeachingTip>();

		teachingTip.Background(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush{
		   winrt::Windows::UI::Colors::Transparent()
			});


		auto teachingTipLoadedRevoker = std::make_shared<winrt::Microsoft::UI::Xaml::Controls::TeachingTip::Loaded_revoker>();
		*teachingTipLoadedRevoker = teachingTip.Loaded(winrt::auto_revoke, [teachingTipLoadedRevoker](winrt::Windows::Foundation::IInspectable const& teachingTipRef, auto&&)
		{
			teachingTipLoadedRevoker->revoke();

			auto teachingTip = teachingTipRef.as<winrt::Microsoft::UI::Xaml::Controls::TeachingTip>();
			teachingTip.ShouldConstrainToRootBounds(false);

			auto border = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Border>(
				teachingTip,
				L"Container"
			);

			if (!border) return;

			PatchLightDismissSetters(border);

			auto borderLoadedRevoker = std::make_shared<winrt::Microsoft::UI::Xaml::Controls::Border::Loaded_revoker>();
			*borderLoadedRevoker = border.Loaded(winrt::auto_revoke, [borderLoadedRevoker](winrt::Windows::Foundation::IInspectable const& borderRef, auto&&)
			{
				borderLoadedRevoker->revoke();

				auto border = borderRef.as<winrt::Microsoft::UI::Xaml::Controls::Border>();

				auto contentRootGrid = border.FindName(L"ContentRootGrid").try_as<winrt::Microsoft::UI::Xaml::Controls::Grid>();
				auto tailPolygon = border.FindName(L"TailPolygon").try_as<winrt::Microsoft::UI::Xaml::Shapes::Polygon>();

				if (contentRootGrid)
					ApplyAcrylicToGrid(contentRootGrid);

				if (contentRootGrid && tailPolygon)
					PatchTailBorder(contentRootGrid, tailPolygon);

			});


		});

	}
}
