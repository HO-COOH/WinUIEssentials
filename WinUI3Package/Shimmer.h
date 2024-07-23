#pragma once

#include "Shimmer.g.h"
#include <array>
#include <optional>
#include <span>

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
        winrt::Microsoft::UI::Xaml::FrameworkElement m_container{ nullptr };
        void startAnimation();

        constexpr static auto ShimmerGradientStopsResourceName = L"ShimmerGradientStops";

        //constexpr static std::array DarkColors
        //{
        //    winrt::Windows::UI::Color{ static_cast<unsigned char>(255 * 6.05 * 1 / 100), 255, 255, 255},
        //    winrt::Windows::UI::Color{ static_cast<unsigned char>(255 * 3.26 * 1 / 100), 255, 255, 255},
        //    winrt::Windows::UI::Color{ static_cast<unsigned char>(255 * 3.26 * 1 / 100), 255, 255, 255},
        //    winrt::Windows::UI::Color{ static_cast<unsigned char>(255 * 6.05 * 1 / 100), 255, 255, 255},
        //};

        //constexpr static std::array LightColors
        //{
        //    winrt::Windows::UI::Color{ static_cast<unsigned char>(255 * 5.37 / 100), 0, 0, 0},
        //    winrt::Windows::UI::Color{ static_cast<unsigned char>(255 * 2.89 / 100), 0, 0, 0},
        //    winrt::Windows::UI::Color{ static_cast<unsigned char>(255 * 2.89 / 100), 0, 0, 0},
        //    winrt::Windows::UI::Color{ static_cast<unsigned char>(255 * 5.37 / 100), 0, 0, 0},
        //};

        //constexpr static std::array GradientStopOffset
        //{
        //    0.273f,
        //    0.436f,
        //    0.482f,
        //    0.643f
        //};

        class AnimationMember
        {
            winrt::Microsoft::UI::Composition::Vector2KeyFrameAnimation m_gradientStartPointAnimation;
            winrt::Microsoft::UI::Composition::Vector2KeyFrameAnimation m_gradientStopPointAnimation;
            winrt::Microsoft::UI::Composition::CompositionRoundedRectangleGeometry m_rectangleGeometry;
            winrt::Microsoft::UI::Composition::CompositionLinearGradientBrush m_shimmerMaskGradient;

            winrt::Microsoft::UI::Composition::Compositor m_compositor;

            //winrt::Windows::Foundation::TimeSpan m_duration;
            void appendGradientStop(winrt::Windows::UI::Color color, float offset);
            void appendGradientStop(winrt::Microsoft::UI::Composition::CompositionColorGradientStop const& gradientStop);



            constexpr static auto InitialStartPointX = -7.92f;
        public:
            AnimationMember(
                winrt::Microsoft::UI::Composition::Compositor const& compositor,
                winrt::Windows::Foundation::TimeSpan duration
            );

            void SetGradientStops(
                std::span<winrt::Windows::UI::Color const> gradientStops,
                std::span<float const> gradientOffsets
            );

            void SetGradientStops(winrt::Microsoft::UI::Xaml::Media::GradientStopCollection gradientStops);

            winrt::Microsoft::UI::Composition::ShapeVisual GetVisual(
                winrt::Windows::Foundation::Numerics::float2 size,
                float cornerRadius
            );

            void StopAnimation();

            ~AnimationMember();
        };

        std::optional<AnimationMember> m_animation;
        winrt::Microsoft::UI::Xaml::Controls::ContentPresenter m_presenter{ nullptr };
        bool m_loaded{};
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct Shimmer : ShimmerT<Shimmer, implementation::Shimmer>
    {
    };
}
