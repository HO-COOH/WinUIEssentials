#include "pch.h"
#include "ProgressBarEx.h"
#if __has_include("ProgressBarEx.g.cpp")
#include "ProgressBarEx.g.cpp"
#endif
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
namespace winrt::WinUI3Package::implementation
{
    winrt::Microsoft::UI::Xaml::DependencyProperty ProgressBarEx::s_highColorProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
        L"HighColor",
        winrt::xaml_typename<winrt::Windows::UI::Color>(),
        winrt::xaml_typename<class_type>(),
        winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(DefaultHighColor),
            [](winrt::Microsoft::UI::Xaml::DependencyObject const& d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
            {
                auto self = winrt::get_self<ProgressBarEx>(d.as<class_type>());
                if (!self->m_compositor)
                    return;

                auto highColor = winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue());
                self->m_gradients[1].Color(highColor);
                self->m_gradients[2].Color(highColor);
            }
        }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty ProgressBarEx::s_baseColorProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
        L"BaseColor",
        winrt::xaml_typename<winrt::Windows::UI::Color>(),
        winrt::xaml_typename<class_type>(),
        winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(DefaultBaseColor),
            [](winrt::Microsoft::UI::Xaml::DependencyObject const& d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
            {
                auto self = winrt::get_self<ProgressBarEx>(d.as<class_type>());
                if (!self->m_compositor)
                    return;

                auto baseColor = winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue());
                self->m_gradients[0].Color(baseColor);
                self->m_gradients[3].Color(baseColor);
            }
        }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty ProgressBarEx::s_percentProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
        L"Percent",
        winrt::xaml_typename<double>(),
        winrt::xaml_typename<class_type>(),
        winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(0.0), &ProgressBarEx::onPercentPropertyChanged }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty ProgressBarEx::s_valueProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
        L"Value",
        winrt::xaml_typename<double>(),
        winrt::xaml_typename<class_type>(),
        nullptr
    );

    void ProgressBarEx::OnApplyTemplate()
    {
        auto border = GetTemplateChild(L"RootBorder").as<winrt::Microsoft::UI::Xaml::Controls::Border>();
        m_compositor = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(border).Compositor();


        auto gradientBrush = m_compositor.CreateLinearGradientBrush();
        auto brushColorStop = gradientBrush.ColorStops();

        auto const highColor = HighColor();
        auto const baseColor = BaseColor();

        for (int i = 0; i < std::size(gradientStop); ++i)
        {
            m_gradients[i] = m_compositor.CreateColorGradientStop(gradientStop[i], i == 0 || i == std::size(gradientStop) - 1 ? baseColor : highColor);
            brushColorStop.Append(m_gradients[i]);
        }

        m_spriteVisual = m_compositor.CreateSpriteVisual();
        setSpriteSize();
        m_spriteVisual.Brush(gradientBrush);

        auto const offset = -7.f;
        auto startPointAnimation = m_compositor.CreateVector2KeyFrameAnimation();
        startPointAnimation.Duration(std::chrono::milliseconds{ 1600 });
        startPointAnimation.IterationBehavior(winrt::Microsoft::UI::Composition::AnimationIterationBehavior::Forever);
        startPointAnimation.InsertKeyFrame(0.0f, { offset, 0.0f });
        startPointAnimation.InsertKeyFrame(1.0f, {});

        auto endPointAnimation = m_compositor.CreateVector2KeyFrameAnimation();
        endPointAnimation.Duration(startPointAnimation.Duration());
        endPointAnimation.IterationBehavior(startPointAnimation.IterationBehavior());
        endPointAnimation.InsertKeyFrame(0.0f, { 1.0f, 0.0f });
        endPointAnimation.InsertKeyFrame(1.0f, { -offset, 0.0f });

        gradientBrush.StartAnimation(L"StartPoint", startPointAnimation);
        gradientBrush.StartAnimation(L"EndPoint", endPointAnimation);
        winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(border, m_spriteVisual);
        SizeChanged([this](auto...) { setSpriteSize(); });
    }

    winrt::Windows::UI::Color ProgressBarEx::HighColor()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(s_highColorProperty));
    }
    void ProgressBarEx::HighColor(winrt::Windows::UI::Color value)
    {
        SetValue(s_highColorProperty, winrt::box_value(value));
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty ProgressBarEx::HighColorProperty()
    {
        return s_highColorProperty;
    }
    winrt::Windows::UI::Color ProgressBarEx::BaseColor()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(s_baseColorProperty));
    }
    void ProgressBarEx::BaseColor(winrt::Windows::UI::Color value)
    {
        SetValue(s_baseColorProperty, winrt::box_value(value));
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty ProgressBarEx::BaseColorProperty()
    {
        return s_baseColorProperty;
    }

    double ProgressBarEx::Percent()
    {
        return winrt::unbox_value<double>(GetValue(s_percentProperty));
    }
    void ProgressBarEx::Percent(double value)
    {
        SetValue(s_percentProperty, winrt::box_value(std::clamp(value, 0.0, 100.0)));
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty ProgressBarEx::PercentProperty()
    {
        return s_percentProperty;
    }

    double ProgressBarEx::Value()
    {
        return Percent() / 100.0;
    }

    void ProgressBarEx::Value(double value)
    {
        Percent(value * 100.0);
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty ProgressBarEx::ValueProperty()
    {
        return s_valueProperty;
    }

    void ProgressBarEx::onPercentPropertyChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        winrt::get_self<ProgressBarEx>(d.as<class_type>())->setSpriteSize();
    }

    void ProgressBarEx::setSpriteSize()
    {
        if (m_compositor && m_spriteVisual)
        {
            auto animation = m_compositor.CreateVector2KeyFrameAnimation();
            auto easing = winrt::Microsoft::UI::Composition::CompositionEasingFunction::CreateCircleEasingFunction(m_compositor, winrt::Microsoft::UI::Composition::CompositionEasingFunctionMode::InOut);
            animation.InsertKeyFrame(1.0, { static_cast<float>(ActualWidth() * Value()), static_cast<float>(ActualHeight()) }, easing);
            //the default duration already looks good
            //animation.Duration(std::chrono::seconds{ 1 });
            m_spriteVisual.StartAnimation(L"Size", animation);
        }
    }
}
