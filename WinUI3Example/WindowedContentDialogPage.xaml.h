#pragma once

#include "WindowedContentDialogPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct WindowedContentDialogPage : WindowedContentDialogPageT<WindowedContentDialogPage>
    {
        WindowedContentDialogPage() = default;
        winrt::fire_and_forget Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct WindowedContentDialogPage : WindowedContentDialogPageT<WindowedContentDialogPage, implementation::WindowedContentDialogPage>
    {
    };
}
