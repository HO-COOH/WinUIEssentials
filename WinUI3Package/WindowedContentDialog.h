#pragma once

#include "WindowedContentDialog.g.h"
namespace winrt::WinUI3Package::implementation
{
    struct WindowedContentDialog : WindowedContentDialogT<WindowedContentDialog>
    {
        WindowedContentDialog();
		WindowedContentDialog(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& m_dialog);

        winrt::Microsoft::UI::Xaml::Controls::ContentDialog Content();

        winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult> ShowAsync();
        winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult> ShowAsync(winrt::Microsoft::UI::Xaml::Window parentWindow);

    private:
        winrt::Microsoft::UI::Xaml::Window m_window;
        winrt::Microsoft::UI::Xaml::Controls::Grid m_placeholder;
        winrt::Microsoft::UI::Xaml::Controls::ContentDialog m_dialog;
        winrt::Windows::Graphics::SizeInt32 getDesiredWindowSize();
        void setContent();
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct WindowedContentDialog : WindowedContentDialogT<WindowedContentDialog, implementation::WindowedContentDialog>
    {
    };
}
