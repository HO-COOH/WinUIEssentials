#pragma once

#include "ModernWindowCaptionButtonToolTipPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ModernWindowCaptionButtonToolTipPage : ModernWindowCaptionButtonToolTipPageT<ModernWindowCaptionButtonToolTipPage>
    {
        void OriginalWinUI3WindowButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void OriginalWinUI3WindowExtendedButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void OriginalWinUI3WindowWithModernToolTipButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void OriginalWinUI3WindowExtendedWithModernToolTipButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ModernWindowCaptionButtonToolTipPage : ModernWindowCaptionButtonToolTipPageT<ModernWindowCaptionButtonToolTipPage, implementation::ModernWindowCaptionButtonToolTipPage>
    {
    };
}
