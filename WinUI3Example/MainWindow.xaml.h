// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "MainWindow.g.h"
#include <ranges>
#include <string_view>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
#include "ButtonAnimations.h"
#include <boost/hana.hpp>


namespace winrt::WinUI3Example::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        void NavigationView_SelectionChanged(
            winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender,
            winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);

        static HWND Hwnd;

        void ExitItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void WindowEx_Activated(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowActivatedEventArgs const& args);
        void WindowEx_Closed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowEventArgs const& args);
        void FooterMenuItemsHost_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        winrt::Windows::Foundation::IAsyncAction MoreButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void PageSourceContentButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        static winrt::Windows::Foundation::Uri GetXamlUrl(winrt::hstring const& name);
        constexpr static winrt::guid IconGuid()
        {
#if (defined DEBUG) || (defined _DEBUG)
            return { 0xe2063928, 0xbee9, 0x4635, { 0xb2, 0xbf, 0x61, 0x12, 0x4d, 0xef, 0x18, 0xa2 } };
#else
            return { 0x50fb17d, 0xd467, 0x49ce, { 0xa0, 0xb7, 0x81, 0x87, 0x52, 0x7a, 0x9c, 0x81 } };
#endif
        }
        static winrt::hstring WindowTitle();
        // Stored animations for reversible playback
        ButtonAnimations m_sourceButtonAnimations;
        bool m_isExpanded = false;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
