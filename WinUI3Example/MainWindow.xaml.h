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
    struct ToastPage;
    struct CursorControllerPage;
    struct ConvertersPage;
    struct BadgePage;
    struct TaskbarPage;
    struct TriggersPage;
    struct GroupBoxPage;
    struct SettingsCardPage;
    struct SettingsExpanderPage;
    struct DependentValuePage;
    struct MarqueeTextPage;
    struct GlyphsPage;
    struct TitleBarPage;
    struct ProgressBarExPage;
    struct WindowExPage;
    struct Segmente;
    struct UriPage;
    struct BackdropPage;
    struct ShimmerPage;
    struct SwitchPresenterPage;
    struct ExperimentPage;
    struct TaskbarIconPage;
    struct ThemeListenerPage;
    struct ScopedButtonDisablerPage;
    struct InitializeWithWindowHelperPage;
    struct ModernStandardWindowContextMenuPage;
    struct ExtensionsPage;
    struct ComboBoxHelperPage;
    struct WrapPanelPage;
    struct AutoSuggestBoxHelperPage;
    struct ModalWindowPage;
    struct ToolTipHelperPage;
    struct CommandBarHelperPage;
    struct CaptionButtonThemeWorkaroundPage;
    struct NonResizableWindowWhiteBorderWorkaroundPage;
    struct NonMaximizableWindowWorkaroundPage;
    struct DatePickerHelperPage;
    struct TimePickerHelperPage;
    struct FlyoutHelperPage;
    struct CalendarDatePickerWorkaroundPage;
    struct SegmentedPage;
	struct NavigationViewHelperPage;
	struct RevealFocusPage;

    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        void NavigationView_SelectionChanged(
            winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender,
            winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Pages();


        static winrt::guid IconGuid();
        static HWND Hwnd;
		static winrt::Microsoft::UI::Xaml::Window Window;
        static WinUI3Example::MainWindow MainWindowInstance;

        void ExitItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void WindowEx_Activated(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowActivatedEventArgs const& args);
        void FooterMenuItemsHost_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        winrt::Windows::Foundation::IAsyncAction MoreButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void PageSourceContentButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        static winrt::Windows::Foundation::Uri GetXamlUrl(winrt::hstring const& name);
    private:

        //compile time sorting this blows up Visual Studio, we do it "manually"
        static constexpr auto s_page = boost::hana::make_tuple(
            boost::hana::make_pair(L"*Experiments*", boost::hana::type_c<WinUI3Example::implementation::ExperimentPage>),
            boost::hana::make_pair(L"AutoSuggestBoxHelper", boost::hana::type_c<WinUI3Example::implementation::AutoSuggestBoxHelperPage>),
            boost::hana::make_pair(L"Backdrop", boost::hana::type_c<WinUI3Example::implementation::BackdropPage>),
            boost::hana::make_pair(L"Badge", boost::hana::type_c<WinUI3Example::implementation::BadgePage>),
            boost::hana::make_pair(L"CalendarDatePickerHelper", boost::hana::type_c<WinUI3Example::implementation::CalendarDatePickerWorkaroundPage>),
            /*boost::hana::make_pair(L"CharmBarPage", boost::hana::type_c<WinUI3Example::implementation::CharmBarPage>),*/
            boost::hana::make_pair(L"ComboBoxHelper", boost::hana::type_c<WinUI3Example::implementation::ComboBoxHelperPage>),
            boost::hana::make_pair(L"CommandBarHelper", boost::hana::type_c<WinUI3Example::implementation::CommandBarHelperPage>),
            boost::hana::make_pair(L"Converters", boost::hana::type_c<WinUI3Example::implementation::ConvertersPage>),
            boost::hana::make_pair(L"CursorController", boost::hana::type_c<WinUI3Example::implementation::CursorControllerPage>),
            boost::hana::make_pair(L"DatePickerHelper", boost::hana::type_c<WinUI3Example::implementation::DatePickerHelperPage>),
            boost::hana::make_pair(L"DependentValue", boost::hana::type_c<WinUI3Example::implementation::DependentValuePage>),
            boost::hana::make_pair(L"Extensions", boost::hana::type_c<WinUI3Example::implementation::ExtensionsPage>),
            boost::hana::make_pair(L"FlyoutHelper", boost::hana::type_c<WinUI3Example::implementation::FlyoutHelperPage>),
            boost::hana::make_pair(L"Glphys", boost::hana::type_c<WinUI3Example::implementation::GlyphsPage>),
            boost::hana::make_pair(L"GroupBox", boost::hana::type_c<WinUI3Example::implementation::GroupBoxPage>),
            //boost::hana::make_pair(L"IncrementalLoadingPage", boost::hana::type_c<WinUI3Example::implementation::IncrementalLoadingPage>),
            boost::hana::make_pair(L"InitializeWithWindowHelper", boost::hana::type_c<WinUI3Example::implementation::InitializeWithWindowHelperPage>),
            boost::hana::make_pair(L"MarqueeText", boost::hana::type_c<WinUI3Example::implementation::MarqueeTextPage>),
            boost::hana::make_pair(L"ModalWindow", boost::hana::type_c<WinUI3Example::implementation::ModalWindowPage>),
            boost::hana::make_pair(L"ModernStandardWindowMenu", boost::hana::type_c<WinUI3Example::implementation::ModernStandardWindowContextMenuPage>),
            boost::hana::make_pair(L"NonMaximizableWindowWorkaround", boost::hana::type_c<WinUI3Example::implementation::NonMaximizableWindowWorkaroundPage>),
            boost::hana::make_pair(L"NonResizableWindowWhiteBorderWorkaround", boost::hana::type_c<WinUI3Example::implementation::NonResizableWindowWhiteBorderWorkaroundPage>),
            boost::hana::make_pair(L"ProgressBarEx", boost::hana::type_c<WinUI3Example::implementation::ProgressBarExPage>),
            boost::hana::make_pair(L"ScopedButtonDisabler", boost::hana::type_c<WinUI3Example::implementation::ScopedButtonDisablerPage>),
            boost::hana::make_pair(L"Segmented", boost::hana::type_c<WinUI3Example::implementation::SegmentedPage>),
            boost::hana::make_pair(L"SettingsCard", boost::hana::type_c<WinUI3Example::implementation::SettingsCardPage>),
            boost::hana::make_pair(L"SettingsExpander", boost::hana::type_c<WinUI3Example::implementation::SettingsExpanderPage>),
            boost::hana::make_pair(L"Shimmer", boost::hana::type_c<WinUI3Example::implementation::ShimmerPage>),
            boost::hana::make_pair(L"SwitchPresenter", boost::hana::type_c<WinUI3Example::implementation::SwitchPresenterPage>),
            boost::hana::make_pair(L"Taskbar", boost::hana::type_c<WinUI3Example::implementation::TaskbarPage>),
            boost::hana::make_pair(L"TaskbarIcon", boost::hana::type_c<WinUI3Example::implementation::TaskbarIconPage>),
            boost::hana::make_pair(L"ThemeListener", boost::hana::type_c<WinUI3Example::implementation::ThemeListenerPage>),
            boost::hana::make_pair(L"TimePickerHelper", boost::hana::type_c<WinUI3Example::implementation::TimePickerHelperPage>),
            boost::hana::make_pair(L"TitleBar", boost::hana::type_c<WinUI3Example::implementation::TitleBarPage>),
            boost::hana::make_pair(L"Toast", boost::hana::type_c<WinUI3Example::implementation::ToastPage>),
            boost::hana::make_pair(L"ToolTipHelper", boost::hana::type_c<WinUI3Example::implementation::ToolTipHelperPage>),
            boost::hana::make_pair(L"Triggers", boost::hana::type_c<WinUI3Example::implementation::TriggersPage>),
            boost::hana::make_pair(L"Uris", boost::hana::type_c<WinUI3Example::implementation::UriPage>),
            boost::hana::make_pair(L"WindowCaptionButtonThemeWorkaround", boost::hana::type_c<WinUI3Example::implementation::CaptionButtonThemeWorkaroundPage>),
            boost::hana::make_pair(L"WindowEx", boost::hana::type_c<WinUI3Example::implementation::WindowExPage>),
            boost::hana::make_pair(L"WrapPanel", boost::hana::type_c<WinUI3Example::implementation::WrapPanelPage>),
			boost::hana::make_pair(L"NavigationViewHelper", boost::hana::type_c<WinUI3Example::implementation::NavigationViewHelperPage>),
            boost::hana::make_pair(L"RevealFocus", boost::hana::type_c<WinUI3Example::implementation::RevealFocusPage>)
        );

        static constexpr void iteratePageType(std::wstring_view key, auto&& onFound)
        {
            boost::hana::fold_left(s_page, false, [key, &onFound](bool found, auto const& p)
            {
                if (!found && key == boost::hana::first(p))
                {
                    onFound(boost::hana::second(p));
                    return true;
                }
                return found;
            });
        }
        static winrt::Windows::UI::Xaml::Interop::TypeName getPageType(winrt::hstring const& key);
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
