#pragma once

#include "Shimmer.g.h"
#include <optional>
#include "Shimmer.AnimationMember.h"

namespace winrt::WinUI3Package::implementation
{
    struct Shimmer : ShimmerT<Shimmer>
    {
        Shimmer() = default;

        bool IsLoading();
        void IsLoading(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty IsLoadingProperty();

        void OnApplyTemplate();
    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_isLoadingProperty;
        winrt::Microsoft::UI::Xaml::FrameworkElement m_animationContainer{ nullptr };
        winrt::Microsoft::UI::Xaml::FrameworkElement::SizeChanged_revoker m_animationSizeChangedRevoker;
        void startAnimation();

        constexpr static auto ShimmerGradientStopsResourceName = L"ShimmerGradientStops";

        void setGradientStops();
        void setDefaultGradientStops(winrt::Microsoft::UI::Xaml::ElementTheme theme);

        // IsLoading == true
        void loadShimmer();

        // IsLoading == false
        void loadContent();
        
        
        static winrt::Microsoft::UI::Xaml::ResourceDictionary tryGetThemeResourceDictionaryFromResource(
            winrt::Microsoft::UI::Xaml::ResourceDictionary const& resource,
            winrt::Microsoft::UI::Xaml::ElementTheme theme
        );
        winrt::Microsoft::UI::Xaml::ResourceDictionary tryGetThemeResourceDictionary(winrt::Microsoft::UI::Xaml::ElementTheme theme);
        winrt::Microsoft::UI::Xaml::Media::GradientStopCollection tryGetGraidentStopsFromThemeResource(winrt::Microsoft::UI::Xaml::ElementTheme theme);
        winrt::Microsoft::UI::Xaml::Media::GradientStopCollection tryGetGradientStopsFromAppResource(winrt::Microsoft::UI::Xaml::ElementTheme theme);

        
        static bool removeChildFromPanel(
            winrt::Microsoft::UI::Xaml::Controls::Panel const& panel,
            winrt::Microsoft::UI::Xaml::FrameworkElement const& child
        );

        std::optional<ShimmerAnimationMember> m_animation;
        winrt::Microsoft::UI::Xaml::Controls::ContentPresenter m_presenter{ nullptr };
        winrt::Microsoft::UI::Xaml::Controls::Panel m_rootPanel{ nullptr };
        bool m_loaded{};
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct Shimmer : ShimmerT<Shimmer, implementation::Shimmer>
    {
    };
}
