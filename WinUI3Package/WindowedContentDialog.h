#pragma once

#include "WindowedContentDialog.g.h"
namespace winrt::WinUI3Package::implementation
{
    struct WindowedContentDialog : WindowedContentDialogT<WindowedContentDialog>
    {
        WindowedContentDialog();
		WindowedContentDialog(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& m_dialog);

        winrt::Microsoft::UI::Xaml::Controls::ContentDialog Content();
        void Content(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& value);

        winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult> ShowAsync();
        winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult> ShowAsync(winrt::Microsoft::UI::Xaml::Window parentWindow);
    private:
        winrt::Microsoft::UI::Xaml::Window m_window;
		winrt::WinUI3Package::NonMaximizableWindowWorkaround m_nonResizableWorkaround{ m_window, false };
        winrt::Microsoft::UI::Xaml::Controls::Grid m_placeholder;
        winrt::Microsoft::UI::Xaml::Controls::ContentDialog m_dialog{ nullptr };

        bool m_isClosingByCode{ false };
        winrt::Windows::Graphics::SizeInt32 getDesiredWindowSize();
        void setContent();
        void centerWindowInParent(
            winrt::Microsoft::UI::Windowing::AppWindow const& appWindow,
            winrt::Microsoft::UI::Xaml::Window const& parentWindow
        );
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct WindowedContentDialog : WindowedContentDialogT<WindowedContentDialog, implementation::WindowedContentDialog>
    {
    };
}
