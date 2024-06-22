#pragma once

#include "MainPage.g.h"
#include <unordered_map>

namespace winrt::UWPExample::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

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
    private:
        static inline std::unordered_map<winrt::hstring, winrt::Windows::UI::Xaml::Interop::TypeName> s_page
        {
            {L"ToastPage", winrt::xaml_typename<UWPExample::ToastPage>()},
            {L"CursorControllerPage", winrt::xaml_typename<UWPExample::CursorControllerPage>()},
            {L"ConvertersPage", winrt::xaml_typename<UWPExample::ConvertersPage>()},
            {L"BadgePage", winrt::xaml_typename<UWPExample::BadgePage>()},
            {L"TaskbarPage", winrt::xaml_typename<UWPExample::TaskbarPage>()},
            {L"TriggersPage", winrt::xaml_typename<UWPExample::TriggersPage>()},
            {L"GroupBoxPage", winrt::xaml_typename<UWPExample::GroupBoxPage>()},
            {L"CharmBarPage", winrt::xaml_typename<UWPExample::CharmBarPage>()},
            {L"SettingsCardPage", winrt::xaml_typename<UWPExample::SettingsCardPage>()},
            {L"SettingsExpanderPage", winrt::xaml_typename<UWPExample::SettingsExpanderPage>()},
            {L"DependentValuePage", winrt::xaml_typename<UWPExample::DependentValuePage>()},
            {L"MarqueeContainerPage", winrt::xaml_typename<UWPExample::MarqueeContainerPage>()},
            {L"GlyphsPage", winrt::xaml_typename<UWPExample::GlyphsPage>()},
            {L"TilesPage", winrt::xaml_typename<UWPExample::TilesPage>()},
            {L"IconButtonPage", winrt::xaml_typename<UWPExample::IconButtonPage>()},
            {L"ProgressBarExPage", winrt::xaml_typename<UWPExample::ProgressBarExPage>()},
            {L"UIElementExtensionPage", winrt::xaml_typename<UWPExample::UIElementExtensionsPage>()},
            {L"SegmentedPage", winrt::xaml_typename<UWPExample::SegmentedPage>()},
            {L"UriPage", winrt::xaml_typename<UWPExample::UriPage>()}
        };
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
