#pragma once

#include "ExpViewModel.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ExpViewModel : ExpViewModelT<ExpViewModel>
    {
        ExpViewModel() = default;

        winrt::Windows::Foundation::IInspectable MyProperty() { return m_property; }
        void MyProperty(winrt::Windows::Foundation::IInspectable const& value) { m_property = value; }

        winrt::Windows::Foundation::IInspectable m_property{ nullptr };
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ExpViewModel : ExpViewModelT<ExpViewModel, implementation::ExpViewModel>
    {
    };
}
