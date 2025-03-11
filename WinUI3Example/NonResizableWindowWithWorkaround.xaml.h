#pragma once

#include "NonResizableWindowWithWorkaround.g.h"
#include <winrt/Microsoft.UI.Windowing.h>

namespace winrt::WinUI3Example::implementation
{
    struct NonResizableWindowWithWorkaround : NonResizableWindowWithWorkaroundT<NonResizableWindowWithWorkaround>
    {
        NonResizableWindowWithWorkaround()
        {
            auto appWindow = AppWindow();
            appWindow.ResizeClient({ .Width = 800, .Height = 600 });
            auto presenter = appWindow.Presenter().as<winrt::Microsoft::UI::Windowing::OverlappedPresenter>();
            presenter.IsResizable(false);
            presenter.SetBorderAndTitleBar(false, false);
        }

        void myButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
        {
            myButton().Content(winrt::box_value(L"Clicked"));
        }
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct NonResizableWindowWithWorkaround : NonResizableWindowWithWorkaroundT<NonResizableWindowWithWorkaround, implementation::NonResizableWindowWithWorkaround>
    {
    };
}
