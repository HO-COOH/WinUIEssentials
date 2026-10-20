#include "pch.h"
#include "TeachingTipHelper.h"
#if __has_include("TeachingTipHelper.g.cpp")
#include "TeachingTipHelper.g.cpp"
#endif
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Content.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include "TeachingTipAcrylicStyle.h"
#include "AcrylicVisualWithBoundedCornerRadius.h"
#include "BindingHelper.h"
#include "GridHelper.hpp"

namespace winrt::WinUI3Package::implementation
{
    winrt::Microsoft::UI::Xaml::DependencyProperty TeachingTipHelper::s_acrylicWorkaroundProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
            L"AcrylicWorkaround",
            winrt::xaml_typename<bool>(),
            winrt::xaml_typename<winrt::WinUI3Package::TeachingTipHelper>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                nullptr,
                &TeachingTipHelper::acrylicWorkaroundChanged
            }
        );

    bool TeachingTipHelper::GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::TeachingTip const& teachingTip)
    {
        return winrt::unbox_value<bool>(teachingTip.GetValue(s_acrylicWorkaroundProperty));
    }

    void TeachingTipHelper::SetAcrylicWorkaround(
        winrt::Microsoft::UI::Xaml::Controls::TeachingTip const& teachingTip,
        bool value
    )
    {
        teachingTip.SetValue(s_acrylicWorkaroundProperty, winrt::box_value(value));
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty TeachingTipHelper::AcrylicWorkaroundProperty()
    {
        return s_acrylicWorkaroundProperty;
    }

    void TeachingTipHelper::acrylicWorkaroundChanged(
        winrt::Microsoft::UI::Xaml::DependencyObject const& d,
        winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg
    )
    {
        auto const acrylicWorkaround = winrt::unbox_value<bool>(arg.NewValue());
        if (!acrylicWorkaround)
            return;

        auto teachingTip = d.as<winrt::Microsoft::UI::Xaml::Controls::TeachingTip>();
        auto const isLightDismissEnabled = teachingTip.IsLightDismissEnabled();

        //if shouldConstrainToRootBounds=true, it does not blur the acrylic/mica window background, disable it first
        teachingTip.ShouldConstrainToRootBounds(false);
        teachingTip.Background(nullptr);

        auto layoutUpdated_revoker = std::make_shared<winrt::Microsoft::UI::Xaml::Controls::TeachingTip::LayoutUpdated_revoker>();
        *layoutUpdated_revoker = teachingTip.LayoutUpdated(winrt::auto_revoke, [layoutUpdated_revoker, teachingTip_ref = winrt::make_weak(teachingTip), isLightDismissEnabled](auto&&...)
        {
            auto teachingTip = teachingTip_ref.get();
            //Revoke before applying, so it is not retried on every layout pass if it throws
            layoutUpdated_revoker->revoke();
            if (!teachingTip)
                return;

            auto container = winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetChild(teachingTip, 0).as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
            teachingTip.Target() ? applyForTargeted(teachingTip, container) : applyForNonTargeted(teachingTip, container);
        });

    }

    void TeachingTipHelper::applyForNonTargeted(
        winrt::Microsoft::UI::Xaml::Controls::TeachingTip const& teachingTip,
        winrt::Microsoft::UI::Xaml::FrameworkElement const& container
    )
    {
        applyBody(
            teachingTip, 
            container, 
            container.FindName(L"ContentRootGrid").as<winrt::Microsoft::UI::Xaml::Controls::Grid>()
        );
    }

    void TeachingTipHelper::applyForTargeted(
        winrt::Microsoft::UI::Xaml::Controls::TeachingTip const& teachingTip,
        winrt::Microsoft::UI::Xaml::FrameworkElement const& container
    )
    {
        auto contentRootGrid = container.FindName(L"ContentRootGrid").as<winrt::Microsoft::UI::Xaml::Controls::Grid>();

        applyBody(
            teachingTip, 
            container, 
            contentRootGrid
        );

        TargetedTeachingTipAcrylicStyle{
            teachingTip,
            container.FindName(L"TailOcclusionGrid").as<winrt::Microsoft::UI::Xaml::Controls::Grid>(),
            contentRootGrid,
            container.FindName(L"TailPolygon").as<winrt::Microsoft::UI::Xaml::Shapes::Polygon>()
        };
    }

    void TeachingTipHelper::applyBody(
        winrt::Microsoft::UI::Xaml::Controls::TeachingTip const& teachingTip,
        winrt::Microsoft::UI::Xaml::FrameworkElement const& container,
        winrt::Microsoft::UI::Xaml::Controls::Grid const& contentRootGrid
    )
    {
        //Set all controls that has a background set in the ControlTemplate
        winrt::Microsoft::UI::Xaml::Media::SolidColorBrush transparentBrush{ winrt::Windows::UI::Colors::Transparent() };
        contentRootGrid.Background(transparentBrush);
        container.FindName(L"HeroContentBorder").as<winrt::Microsoft::UI::Xaml::Controls::Border>().Background(transparentBrush);
        container.FindName(L"MainContentPresenter").as<winrt::Microsoft::UI::Xaml::Controls::ContentPresenter>().Background(transparentBrush);

        AcrylicVisualWithBoundedCornerRadius bodyAcrylic{ contentRootGrid };
        GridHelper::SpanGrid(bodyAcrylic, contentRootGrid);

        //The acrylic in the TeachingTip's popup does not follow theme changes of the TeachingTip, sync it manually
        bodyAcrylic.RequestedTheme(teachingTip.ActualTheme());
        BindingHelper::BindTheme(bodyAcrylic, teachingTip.Parent().as<winrt::Microsoft::UI::Xaml::FrameworkElement>());

        contentRootGrid.Children().InsertAt(0, bodyAcrylic);
    }
}
