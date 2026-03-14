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
        static winrt::Microsoft::UI::Xaml::Window Window;
        static WinUI3Example::MainWindow MainWindowInstance;

        void ExitItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void WindowEx_Activated(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowActivatedEventArgs const& args);
        void FooterMenuItemsHost_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        winrt::Windows::Foundation::IAsyncAction MoreButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void PageSourceContentButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        static winrt::Windows::Foundation::Uri GetXamlUrl(winrt::hstring const& name);

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
