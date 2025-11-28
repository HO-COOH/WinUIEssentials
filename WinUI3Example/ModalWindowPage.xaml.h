#pragma once

#include "ModalWindowPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ModalWindowPage : ModalWindowPageT<ModalWindowPage>
    {
		ModalWindowPage() = default;

        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ModalWindowPage : ModalWindowPageT<ModalWindowPage, implementation::ModalWindowPage>
    {
    };
}
