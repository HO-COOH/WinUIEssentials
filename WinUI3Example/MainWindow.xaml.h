// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "MainWindow.g.h"
#include <ranges>
#include <string_view>
#include <utility>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include "ButtonAnimations.h"
#include "NavigationHelper.h"


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
        void RootGrid_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
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
        
        constexpr static auto WindowTitle()
        {
#if (defined DEBUG) || (defined _DEBUG)
            return L"WinUIEssentials.WinUI3Example(Dev)";
#else
            return L"WinUIEssentials.WinUI3Example";
#endif
        }

        // Stored animations for reversible playback
        ButtonAnimations m_sourceButtonAnimations;
        bool m_isExpanded = false;
        void GithubFlyoutItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void StoreFlyoutItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        static inline std::chrono::steady_clock::time_point AppStartTime{ std::chrono::steady_clock::now() };
        void AutoSuggestBox_QuerySubmitted(winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs const& args);
        void AutoSuggestBox_TextChanged(winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args);
    private:
        NavigationHelper m_navigationHelper;

        /*
            The window is kept hidden from construction until XAML has drawn a few frames of it, so
            it is never seen empty and the system's open animation plays over finished content.
        */
        void onRendering();
        void onRevealTimerTick();
        void showWindow();

        /*
            Holds the window back until it has something to show, and answers the close button
            directly, because WinUI spends most of a second in its own teardown otherwise. The window
            carries a pointer to us, so the state both need can live here instead of at file scope.
        */
        static LRESULT CALLBACK subclassProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, UINT_PTR id, DWORD_PTR ref);
        void exitNow();

        /*
            Set once the window is allowed on screen. Until then the show request that Activate()
            makes is swallowed, which is what keeps the empty window from being seen.
        */
        bool m_allowShow{};

        winrt::event_token m_renderingToken{};
        winrt::Microsoft::UI::Dispatching::DispatcherQueueTimer m_revealTimer{ nullptr };
        winrt::event_token m_revealTimerToken{};
        int m_renderedFrames{};
        int m_ticks{};
        bool m_shown{};
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
