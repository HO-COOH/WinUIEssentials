#pragma once

#include "AnimatedNumber.g.h"
#include <TemplateControlHelper.hpp>

namespace winrt::WinUI3Example::implementation
{
    struct AnimatedNumber : AnimatedNumberT<AnimatedNumber>, TemplateControlHelper<AnimatedNumber, false>
    {
        friend struct TemplateControlHelper<AnimatedNumber, false>;
        
        AnimatedNumber() = default;

        winrt::hstring Value();
        void Value(winrt::hstring const& value);

        void OnApplyTemplate();
    private:
        winrt::Microsoft::UI::Xaml::Controls::Panel m_rootPanel{ nullptr };
        winrt::hstring m_value;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct AnimatedNumber : AnimatedNumberT<AnimatedNumber, implementation::AnimatedNumber>
    {
    };
}
