#pragma once

#include "AnimatedDigit.g.h"
#include <PropertyChangeHelper.hpp>
#include <TemplateControlHelper.hpp>

namespace winrt::WinUI3Example::implementation
{
    struct AnimatedDigit : AnimatedDigitT<AnimatedDigit>, TemplateControlHelper<AnimatedDigit, false>, MvvmHelper::PropertyChangeHelper<AnimatedDigit>
    {
        friend class TemplateControlHelper<AnimatedDigit, false>;

        AnimatedDigit() = default;

        void OnApplyTemplate();

        void Value(int value);
        int Value();

        winrt::hstring CurrentValue();
        winrt::hstring NextValue();

        static winrt::Windows::Foundation::IReference<double> Negative(double value)
        {
            return -value - 10;
        }
    private:
        bool m_isFirst = true;
        int m_value = -1;
        int m_currentValue = -1;
        int m_nextValue = -1;

        void currentValue(int value);
        void nextValue(int value);

        winrt::Microsoft::UI::Xaml::FrameworkElement m_currentDigit{ nullptr };
        winrt::Microsoft::UI::Xaml::FrameworkElement m_nextDigit{ nullptr };

        winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation m_increaseCurrentAnim{ nullptr };
        winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation m_increaseNextAnim{ nullptr };
        winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation m_decreaseCurrentAnim{ nullptr };
        winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation m_decreaseNextAnim{ nullptr };
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct AnimatedDigit : AnimatedDigitT<AnimatedDigit, implementation::AnimatedDigit>
    {
    };
}
