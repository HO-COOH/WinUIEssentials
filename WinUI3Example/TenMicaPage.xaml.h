#pragma once

#include "TenMicaPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TenMicaPage : TenMicaPageT<TenMicaPage>
    {
        TenMicaPage() = default;
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TenMicaPage : TenMicaPageT<TenMicaPage, implementation::TenMicaPage>
    {
    };
}
