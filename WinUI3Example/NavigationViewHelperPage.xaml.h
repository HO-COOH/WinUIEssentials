#pragma once

#include "NavigationViewHelperPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct NavigationViewHelperPage : NavigationViewHelperPageT<NavigationViewHelperPage>
    {
        NavigationViewHelperPage() = default;

        void pane8PositionLeft_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void pane8PositionTop_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void pane8PositionLeftCompact_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

		void pane9PositionLeft_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
		void pane9PositionTop_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
		void pane9PositionLeftCompact_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct NavigationViewHelperPage : NavigationViewHelperPageT<NavigationViewHelperPage, implementation::NavigationViewHelperPage>
    {
    };
}
