#pragma once

#include "AnimatedNumber.g.h"
#include <TemplateControlHelper.hpp>

namespace winrt::WinUI3Example::implementation
{
    struct AnimatedNumber : AnimatedNumberT<AnimatedNumber>, TemplateControlHelper<AnimatedNumber>
    {
        AnimatedNumber() = default;

        int32_t Value() { return 45; }
        void Value(int32_t value) {}

        winrt::Windows::Foundation::Collections::IObservableVector<int> Digits();

        void OnApplyTemplate();

        friend class TemplateControlHelper<AnimatedNumber>;
    private:
        winrt::Windows::Foundation::Collections::IObservableVector<int> m_digits = winrt::single_threaded_observable_vector<int>({1,2,3,4});
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct AnimatedNumber : AnimatedNumberT<AnimatedNumber, implementation::AnimatedNumber>
    {
    };
}
