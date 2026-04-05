#pragma once

#include "AnimatedNumber.g.h"
#include <TemplateControlHelper.hpp>
#include <boost/container/small_vector.hpp>

namespace winrt::WinUI3Example::implementation
{
    struct AnimatedNumber : AnimatedNumberT<AnimatedNumber>, TemplateControlHelper<AnimatedNumber, false>
    {
        friend struct TemplateControlHelper<AnimatedNumber, false>;
        
        AnimatedNumber() = default;

        constexpr int32_t Value()
        {
            return *m_value;
        }

        void Value(int32_t value);

        void OnApplyTemplate();
    private:
        winrt::Microsoft::UI::Xaml::Controls::Panel m_rootPanel{ nullptr };
        std::optional<int> m_value;
        static void getDigit(int value, auto& container)
        {
            if (value > 0)
            {
                getDigit(value / 10, container);
                container.push_back(value % 10);
            }
        }
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct AnimatedNumber : AnimatedNumberT<AnimatedNumber, implementation::AnimatedNumber>
    {
    };
}
