#pragma once

#include "TilesPage.g.h"
#include <winrt/Windows.UI.Notifications.h>

namespace winrt::UWPExample::implementation
{
    struct TilesPage : TilesPageT<TilesPage>
    {
        TilesPage();

        winrt::Windows::Foundation::IAsyncAction ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    private:
        winrt::Windows::UI::Notifications::TileUpdater m_updater = winrt::Windows::UI::Notifications::TileUpdateManager::CreateTileUpdaterForApplication();
    public:


        static winrt::hstring GetXml(int selection);

        void SetMainTileButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct TilesPage : TilesPageT<TilesPage, implementation::TilesPage>
    {
    };
}
