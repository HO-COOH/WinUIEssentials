#pragma once

#include "ThemeListenerPage.g.h"
#include <ThemeListener.h>

namespace winrt::WinUI3Example::implementation
{
    struct ThemeListenerPage : ThemeListenerPageT<ThemeListenerPage>
    {
        ThemeListenerPage() = default;
        void TextBlock_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    private:
        void updateThemeState(winrt::Microsoft::UI::Xaml::ApplicationTheme theme);
        void updateThemeState(winrt::Microsoft::UI::Xaml::ElementTheme theme);
        ThemeListener::Token m_themeChangedHandlerToken;
    public:
        void Page_ActualThemeChanged(winrt::Microsoft::UI::Xaml::FrameworkElement const& sender, winrt::Windows::Foundation::IInspectable const& args);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ThemeListenerPage : ThemeListenerPageT<ThemeListenerPage, implementation::ThemeListenerPage>
    {
    };
}
