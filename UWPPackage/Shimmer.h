#pragma once

#include "Shimmer.g.h"
#include <array>
#include <vector>
#include <winrt/Windows.UI.Composition.h>
#include <span>
#include <optional>

namespace winrt::UWPPackage::implementation
{
    struct Shimmer : ShimmerT<Shimmer>
    {
        Shimmer() = default;
        
        bool IsLoading();
        void IsLoading(bool value);
        static winrt::Windows::UI::Xaml::DependencyProperty IsLoadingProperty();

        void OnApplyTemplate();
    private:
        static winrt::Windows::UI::Xaml::DependencyProperty s_isLoadingProperty;
        winrt::Windows::UI::Xaml::FrameworkElement m_container{ nullptr };
        void startAnimation();

        constexpr static std::array DarkColors
        {
            winrt::Windows::UI::Color{ static_cast<unsigned char>(255 * 6.05 / 100), 255, 255, 255},
            winrt::Windows::UI::Color{ static_cast<unsigned char>(255 * 3.26 / 100), 255, 255, 255},
            winrt::Windows::UI::Color{ static_cast<unsigned char>(255 * 3.26 / 100), 255, 255, 255},
            winrt::Windows::UI::Color{ static_cast<unsigned char>(255 * 6.05 / 100), 255, 255, 255},
        };

        constexpr static std::array LightColors
        {
            winrt::Windows::UI::Color{ static_cast<unsigned char>(255 * 5.37 / 100), 0, 0, 0},
            winrt::Windows::UI::Color{ static_cast<unsigned char>(255 * 2.89 / 100), 0, 0, 0},
            winrt::Windows::UI::Color{ static_cast<unsigned char>(255 * 2.89 / 100), 0, 0, 0},
            winrt::Windows::UI::Color{ static_cast<unsigned char>(255 * 5.37 / 100), 0, 0, 0},
        };

        constexpr static std::array GradientStopOffset
        {
            0.273f,
            0.436f,
            0.482f,
            0.643f
        };

        class AnimationMember
        {
            winrt::Windows::UI::Composition::Vector2KeyFrameAnimation m_gradientStartPointAnimation;
            winrt::Windows::UI::Composition::Vector2KeyFrameAnimation m_gradientStopPointAnimation;
            winrt::Windows::UI::Composition::CompositionRoundedRectangleGeometry m_rectangleGeometry;
            winrt::Windows::UI::Composition::CompositionLinearGradientBrush m_shimmerMaskGradient;

            winrt::Windows::UI::Composition::Compositor m_compositor;

            //winrt::Windows::Foundation::TimeSpan m_duration;
            void appendGradientStop(winrt::Windows::UI::Color color, float offset);
            void appendGradientStop(winrt::Windows::UI::Composition::CompositionColorGradientStop const& gradientStop);

            constexpr static auto InitialStartPointX = -7.92f;
        public:
            AnimationMember(
                winrt::Windows::UI::Composition::Compositor const& compositor,
                winrt::Windows::Foundation::TimeSpan duration
            );

            void SetGradientStops(
                std::span<winrt::Windows::UI::Color const> gradientStops,
                std::span<float const> gradientOffsets
            );

            winrt::Windows::UI::Composition::ShapeVisual GetVisual(
                winrt::Windows::Foundation::Numerics::float2 size,
                float cornerRadius
            );
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
