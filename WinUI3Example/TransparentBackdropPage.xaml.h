#pragma once

#include "TransparentBackdropPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TransparentBackdropPage : TransparentBackdropPageT<TransparentBackdropPage>
    {
        TransparentBackdropPage() = default;
        void CreateTransparentButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TransparentBackdropPage : TransparentBackdropPageT<TransparentBackdropPage, implementation::TransparentBackdropPage>
    {
    };
}
