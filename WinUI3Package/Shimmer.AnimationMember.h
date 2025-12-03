#pragma once
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Windows.UI.h>
#include <boost/container/static_vector.hpp>
#include <array>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/tuple/tuple.hpp>
#include <algorithm>
#include <iterator>

class ShimmerAnimationMember
{
    winrt::Microsoft::UI::Composition::Vector2KeyFrameAnimation m_gradientStartPointAnimation;
    winrt::Microsoft::UI::Composition::Vector2KeyFrameAnimation m_gradientStopPointAnimation;
    winrt::Microsoft::UI::Composition::CompositionRoundedRectangleGeometry m_rectangleGeometry;
    winrt::Microsoft::UI::Composition::ShapeVisual m_shapeVisual{ nullptr };
    winrt::Microsoft::UI::Composition::CompositionLinearGradientBrush m_shimmerMaskGradient;

    winrt::Microsoft::UI::Composition::Compositor m_compositor;

    //winrt::Windows::Foundation::TimeSpan m_duration;
    void appendGradientStop(winrt::Windows::UI::Color color, float offset);
    void appendGradientStop(winrt::Microsoft::UI::Composition::CompositionColorGradientStop const& gradientStop);



    constexpr static auto InitialStartPointX = -7.92f;
public:
    ShimmerAnimationMember(
        winrt::Microsoft::UI::Composition::Compositor const& compositor,
        winrt::Windows::Foundation::TimeSpan duration
    );

    void SetGradientStops(winrt::Microsoft::UI::Xaml::Media::GradientStopCollection gradientStops);

    template<std::size_t N>
    void SetGradientStops(std::array<winrt::Windows::UI::Color, N> colors, std::array<float, N> gradientStopOffsets)
    {
        boost::container::static_vector<winrt::Microsoft::UI::Composition::CompositionColorGradientStop, N> gradientStops;
        std::transform(
            boost::make_zip_iterator(boost::make_tuple(colors.begin(), gradientStopOffsets.begin())),
            boost::make_zip_iterator(boost::make_tuple(colors.end(), gradientStopOffsets.end())),
            std::back_inserter(gradientStops),
            [this](auto const& t)
            {
                return m_compositor.CreateColorGradientStop(boost::get<1>(t), boost::get<0>(t));
            }
        );
        m_shimmerMaskGradient.ColorStops().ReplaceAll({ &gradientStops.front(), &(*gradientStops.end())});
    }

    winrt::Microsoft::UI::Composition::ShapeVisual GetVisual(
        winrt::Windows::Foundation::Numerics::float2 size,
        float cornerRadius
    );

    void SetSize(winrt::Windows::Foundation::Numerics::float2 size);

    void StopAnimation();

    ~ShimmerAnimationMember();
};