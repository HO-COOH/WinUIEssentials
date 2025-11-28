#pragma once

#include "NonResizableWindowWithMenu.g.h"
#include <winrt/Microsoft.UI.Windowing.h>

namespace winrt::WinUI3Example::implementation
{
    struct NonResizableWindowWithMenu : NonResizableWindowWithMenuT<NonResizableWindowWithMenu>
    {
        NonResizableWindowWithMenu()
        {
            AppWindow()
                .Presenter()
                .as<winrt::Microsoft::UI::Windowing::OverlappedPresenter>()
                .IsResizable(false);
        }

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct NonResizableWindowWithMenu : NonResizableWindowWithMenuT<NonResizableWindowWithMenu, implementation::NonResizableWindowWithMenu>
    {
    };
}
