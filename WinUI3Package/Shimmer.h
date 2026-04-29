#pragma once

#include "Shimmer.g.h"
#include "include/EnsureDependencyProperty.hpp"
#include <optional>
#include "Shimmer.AnimationMember.h"
#include "include/TemplateControlHelper.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct Shimmer : ShimmerT<Shimmer>, TemplateControlHelper<Shimmer>, EnsureDependencyProperty<Shimmer>
    {
        static void EnsureDependencyProperties();
        Shimmer() = default;

        bool IsLoading();

        constexpr static auto ResourceUri = L"ms-appx:///WinUI3Package/Shimmer_Resource.xaml";
        void IsLoading(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty IsLoadingProperty();

        winrt::Microsoft::UI::Xaml::Media::GradientStopCollection GradientStops();
        void GradientStops(winrt::Microsoft::UI::Xaml::Media::GradientStopCollection const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty GradientStopsProperty();

        void OnApplyTemplate();
    private:
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_isLoadingProperty = nullptr;
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_gradientStopsProperty = nullptr;
        winrt::Microsoft::UI::Xaml::FrameworkElement m_animationContainer{ nullptr };
        winrt::Microsoft::UI::Xaml::FrameworkElement::SizeChanged_revoker m_animationSizeChangedRevoker;
        void startAnimation();

        void applyGradientStops();

        // IsLoading == true
        void loadShimmer();

        // IsLoading == false
        void loadContent();

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
