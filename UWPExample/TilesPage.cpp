#include "pch.h"
#include "TilesPage.h"
#if __has_include("TilesPage.g.cpp")
#include "TilesPage.g.cpp"
#endif
#include <fstream>
#include <winrt/Windows.UI.StartScreen.h>
#include <winrt/Windows.Data.Xml.Dom.h>

namespace winrt::UWPExample::implementation
{
    TilesPage::TilesPage()
    {
        m_updater.EnableNotificationQueue(true);
    }

    winrt::Windows::Foundation::IAsyncAction TilesPage::ClickHandler(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        winrt::Windows::Data::Xml::Dom::XmlDocument doc;
        doc.LoadXml(XmlText().Text());

        static int id = 1;
        //auto allTiles = co_await winrt::Windows::UI::StartScreen::SecondaryTile::FindAllAsync();
        //std::vector<winrt::hstring> ids;
        //std::transform(allTiles.begin(), allTiles.end(), std::back_inserter(ids), [](auto const& tile) {
        //    return tile.TileId();
        //});
        winrt::Windows::UI::StartScreen::SecondaryTile tile{ 
            winrt::to_hstring(id++), 
            L"displayName", 
            L"arg", 
            winrt::Windows::Foundation::Uri{L"ms-appx:///Assets/LargeTile.scale-100.png"}, 
            winrt::Windows::UI::StartScreen::TileSize::Default
        };
        auto visuals = tile.VisualElements();
        //visuals.Square71x71Logo(winrt::Windows::Foundation::Uri{ L"ms-appx:///Assets/LargeTile.scale-100.png" });
        //visuals.Square150x150Logo(winrt::Windows::Foundation::Uri{ L"ms-appx:///Assets/LargeTile.scale-100.png" });
        visuals.Wide310x150Logo(winrt::Windows::Foundation::Uri{ L"ms-appx:///Assets/LargeTile.scale-100.png" });
        visuals.Square310x310Logo(winrt::Windows::Foundation::Uri{ L"ms-appx:///Assets/LargeTile.scale-100.png" });
        auto updater = winrt::Windows::UI::Notifications::TileUpdateManager::CreateTileUpdaterForSecondaryTile(tile.TileId());

        if (co_await tile.RequestCreateAsync())
        {
            updater.Update(winrt::Windows::UI::Notifications::TileNotification{ doc });
        }
    }

    void TilesPage::SetMainTileButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        winrt::Windows::Data::Xml::Dom::XmlDocument doc;
        doc.LoadXml(XmlText().Text());

        m_updater.Clear();
        m_updater.Update(winrt::Windows::UI::Notifications::TileNotification{ doc });
    }

    winrt::hstring TilesPage::GetXml(int selection)
    {
        if (selection >= 0 && selection < 80)
            return winrt::Windows::UI::Notifications::TileUpdateManager::GetTemplateContent(static_cast<winrt::Windows::UI::Notifications::TileTemplateType>(selection)).GetXml();
        return L"";
    }
}
