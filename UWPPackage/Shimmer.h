#pragma once

#include "Shimmer.g.h"
#include <winrt/Windows.UI.Composition.h>
#include <optional>

namespace winrt::UWPPackage::implementation
{
    struct Shimmer : ShimmerT<Shimmer>
    {
        Shimmer() = default;

        bool IsLoading();
        void IsLoading(bool value);
        static winrt::Windows::UI::Xaml::DependencyProperty IsLoadingProperty();

        winrt::Windows::UI::Xaml::Media::GradientStopCollection GradientStops();
        void GradientStops(winrt::Windows::UI::Xaml::Media::GradientStopCollection const& value);
        static winrt::Windows::UI::Xaml::DependencyProperty GradientStopsProperty();

        void OnApplyTemplate();
    private:
        static winrt::Windows::UI::Xaml::DependencyProperty s_isLoadingProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty s_gradientStopsProperty;

        winrt::Windows::UI::Xaml::FrameworkElement m_animationContainer{ nullptr };
        winrt::Windows::UI::Xaml::FrameworkElement::SizeChanged_revoker m_animationSizeChangedRevoker;
        winrt::Windows::UI::Xaml::Controls::ContentPresenter m_presenter{ nullptr };
        bool m_loaded{};

        void startAnimation();
        void applyGradientStops();
        void loadShimmer();
        void loadContent();

        class AnimationMember
        {
            winrt::Windows::UI::Composition::Vector2KeyFrameAnimation m_gradientStartPointAnimation;
            winrt::Windows::UI::Composition::Vector2KeyFrameAnimation m_gradientStopPointAnimation;
            winrt::Windows::UI::Composition::CompositionRoundedRectangleGeometry m_rectangleGeometry;
            winrt::Windows::UI::Composition::ShapeVisual m_shapeVisual{ nullptr };
            winrt::Windows::UI::Composition::CompositionLinearGradientBrush m_shimmerMaskGradient;

            winrt::Windows::UI::Composition::Compositor m_compositor;

            constexpr static auto InitialStartPointX = -7.92f;
        public:
            AnimationMember(
                winrt::Windows::UI::Composition::Compositor const& compositor,
                winrt::Windows::Foundation::TimeSpan duration
            );

            void SetGradientStops(winrt::Windows::UI::Xaml::Media::GradientStopCollection gradientStops);

            winrt::Windows::UI::Composition::ShapeVisual GetVisual(
                winrt::Windows::Foundation::Numerics::float2 size,
                float cornerRadius
            );

            void SetSize(winrt::Windows::Foundation::Numerics::float2 size);

            void StopAnimation();

            ~AnimationMember();
        };

        std::optional<AnimationMember> m_animation;
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct Shimmer : ShimmerT<Shimmer, implementation::Shimmer>
    {
    };
}
