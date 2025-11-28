#pragma once

#include "ModernStandardWindowContextMenuPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ModernStandardWindowContextMenuPage : ModernStandardWindowContextMenuPageT<ModernStandardWindowContextMenuPage>
    {
        ModernStandardWindowContextMenuPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        void StandardWindowButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void NonResizableWindowButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void EssentialWindowWithMenuButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CustomWindowMenuButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ModernStandardWindowContextMenuPage : ModernStandardWindowContextMenuPageT<ModernStandardWindowContextMenuPage, implementation::ModernStandardWindowContextMenuPage>
    {
    };
}
