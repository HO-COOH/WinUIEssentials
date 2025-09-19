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

        static winrt::guid IconGuid();
        static HWND Hwnd;
		static winrt::Microsoft::UI::Xaml::Window Window;
    private:
        static inline std::map<winrt::hstring, winrt::Windows::UI::Xaml::Interop::TypeName> s_page
        {
            {L"Toast", winrt::xaml_typename<WinUI3Example::ToastPage>()},
            {L"CursorController", winrt::xaml_typename<WinUI3Example::CursorControllerPage>()},
            {L"Converters", winrt::xaml_typename<WinUI3Example::ConvertersPage>()},
            {L"Badge", winrt::xaml_typename<WinUI3Example::BadgePage>()},
            {L"Taskbar", winrt::xaml_typename<WinUI3Example::TaskbarPage>()},
            {L"Triggers", winrt::xaml_typename<WinUI3Example::TriggersPage>()},
            {L"GroupBox", winrt::xaml_typename<WinUI3Example::GroupBoxPage>()},
            /*{L"CharmBarPage", winrt::xaml_typename<WinUI3Example::CharmBarPage>()},*/
            {L"SettingsCard", winrt::xaml_typename<WinUI3Example::SettingsCardPage>()},
            {L"SettingsExpander", winrt::xaml_typename<WinUI3Example::SettingsExpanderPage>()},
            {L"DependentValue", winrt::xaml_typename<WinUI3Example::DependentValuePage>()},
            {L"MarqueeText", winrt::xaml_typename<WinUI3Example::MarqueeTextPage>()},
            {L"Glphys", winrt::xaml_typename<WinUI3Example::GlyphsPage>()},
            {L"TitleBar", winrt::xaml_typename<WinUI3Example::TitleBarPage>()},
            {L"ProgressBarEx", winrt::xaml_typename<WinUI3Example::ProgressBarExPage>()},
            {L"LineGraph", winrt::xaml_typename<WinUI3Example::LineGraphPage>()},
            {L"WindowEx", winrt::xaml_typename<WinUI3Example::WindowExPage>()},
            {L"Segmented", winrt::xaml_typename<WinUI3Example::SegmentedPage>()},
            {L"IconButton", winrt::xaml_typename<WinUI3Example::IconButtonPage>()},
            {L"Uris", winrt::xaml_typename<WinUI3Example::UriPage>()},
            //{L"IncrementalLoadingPage", winrt::xaml_typename<WinUI3Example::IncrementalLoadingPage>()},
            {L"Backdrop", winrt::xaml_typename<WinUI3Example::BackdropPage>()},
            {L"Shimmer", winrt::xaml_typename<WinUI3Example::ShimmerPage>()},
            {L"SwitchPresenter", winrt::xaml_typename<WinUI3Example::SwitchPresenterPage>()},
            {L"*Experiments*", winrt::xaml_typename<WinUI3Example::ExperimentPage>()},
            {L"TaskbarIcon", winrt::xaml_typename<WinUI3Example::TaskbarIconPage>()},
            {L"ThemeListener", winrt::xaml_typename<WinUI3Example::ThemeListenerPage>()},
            {L"ScopedButtonDisabler", winrt::xaml_typename<WinUI3Example::ScopedButtonDisablerPage>()},
            {L"InitializeWithWindowHelper", winrt::xaml_typename<WinUI3Example::InitializeWithWindowHelperPage>()},
            {L"ModernStandardWindowMenu", winrt::xaml_typename<WinUI3Example::ModernStandardWindowContextMenuPage>()},
            {L"Extensions", winrt::xaml_typename<WinUI3Example::ExtensionsPage>()},
            {L"ComboBoxHelper", winrt::xaml_typename<WinUI3Example::ComboBoxHelperPage>()},
			{L"WrapPanel", winrt::xaml_typename<WinUI3Example::WrapPanelPage>()},
            {L"AutoSuggestBoxHelper", winrt::xaml_typename<WinUI3Example::AutoSuggestBoxHelperPage>()},
			{L"ModalWindow", winrt::xaml_typename<WinUI3Example::ModalWindowPage>()},
			{L"ToolTipHelper", winrt::xaml_typename<WinUI3Example::ToolTipHelperPage>()},
        };

        int m_themeIndex{};
    public:
        void ExitItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ThemeButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
