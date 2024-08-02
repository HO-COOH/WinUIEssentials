// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "MainWindow.g.h"
#include <ranges>
#include <winrt/Microsoft.UI.Xaml.Markup.h>

namespace winrt::WinUI3Example::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        void NavigationView_SelectionChanged(
            winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender,
            winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Pages()
        {
            std::vector<winrt::Windows::Foundation::IInspectable> pages;
            std::ranges::transform(
                s_page,
                std::back_inserter(pages),
                [](auto const& p) { return winrt::box_value(p.first); }
            );
            return winrt::single_threaded_vector(std::move(pages));
        }

        static HWND Hwnd;
    private:
        static inline std::unordered_map<winrt::hstring, winrt::Windows::UI::Xaml::Interop::TypeName> s_page
        {
            {L"ToastPage", winrt::xaml_typename<WinUI3Example::ToastPage>()},
            {L"CursorControllerPage", winrt::xaml_typename<WinUI3Example::CursorControllerPage>()},
            {L"ConvertersPage", winrt::xaml_typename<WinUI3Example::ConvertersPage>()},
            {L"BadgePage", winrt::xaml_typename<WinUI3Example::BadgePage>()},
            {L"TaskbarPage", winrt::xaml_typename<WinUI3Example::TaskbarPage>()},
            {L"TriggersPage", winrt::xaml_typename<WinUI3Example::TriggersPage>()},
            {L"GroupBoxPage", winrt::xaml_typename<WinUI3Example::GroupBoxPage>()},
            /*{L"CharmBarPage", winrt::xaml_typename<WinUI3Example::CharmBarPage>()},*/
            {L"SettingsCardPage", winrt::xaml_typename<WinUI3Example::SettingsCardPage>()},
            {L"SettingsExpanderPage", winrt::xaml_typename<WinUI3Example::SettingsExpanderPage>()},
            {L"DependentValuePage", winrt::xaml_typename<WinUI3Example::DependentValuePage>()},
            {L"MarqueeTextPage", winrt::xaml_typename<WinUI3Example::MarqueeTextPage>()},
            {L"GlphysPage", winrt::xaml_typename<WinUI3Example::GlyphsPage>()},
            {L"TitleBarPage", winrt::xaml_typename<WinUI3Example::TitleBarPage>()},
            {L"ProgressBarExPage", winrt::xaml_typename<WinUI3Example::ProgressBarExPage>()},
            {L"LineGraphPage", winrt::xaml_typename<WinUI3Example::LineGraphPage>()},
            {L"WindowExPage", winrt::xaml_typename<WinUI3Example::WindowExPage>()},
            {L"UIElementExtensionPage", winrt::xaml_typename<WinUI3Example::UIElementExtensionPage>()},
            {L"SegmentedPage", winrt::xaml_typename<WinUI3Example::SegmentedPage>()},
            {L"IconButtonPage", winrt::xaml_typename<WinUI3Example::IconButtonPage>()},
            {L"UriPage", winrt::xaml_typename<WinUI3Example::UriPage>()},
            //{L"IncrementalLoadingPage", winrt::xaml_typename<WinUI3Example::IncrementalLoadingPage>()},
            {L"BackdropPage", winrt::xaml_typename<WinUI3Example::BackdropPage>()},
            {L"ShimmerPage", winrt::xaml_typename<WinUI3Example::ShimmerPage>()},
            {L"TaskbarIconPage", winrt::xaml_typename<WinUI3Example::TaskbarIconPage>()},
            {L"ThemeListenerPage", winrt::xaml_typename<WinUI3Example::ThemeListenerPage>()}
        };
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
