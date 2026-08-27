#include "pch.h"
#include "WrapPanelPage.h"
#if __has_include("WrapPanelPage.g.cpp")
#include "WrapPanelPage.g.cpp"
#endif
#include "PageTagRegister.h"
#include <random>
#include "../UWPPackage/VisualTreeHelper.hpp"

namespace winrt::UWPExample::implementation
{
    static PageTagRegister<WrapPanelPage> s_tags{ L"wrappanel", L"panel", L"layout", L"control" };

    winrt::Windows::Foundation::Collections::IObservableVector<UWPExample::PhotoDataItemWithDimension> WrapPanelPage::WrapPanelCollection()
    {
        return m_wrapPanelCollection;
    }

    void WrapPanelPage::ItemControl_ItemClick(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
    {
        if (auto item = e.ClickedItem().try_as<UWPExample::PhotoDataItemWithDimension>())
        {
            uint32_t index;
            m_wrapPanelCollection.IndexOf(item, index);
            m_wrapPanelCollection.RemoveAt(index);
        }
    }

    void WrapPanelPage::AddButton_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        static std::mt19937 eng{ std::random_device{}() };

        UWPExample::PhotoDataItemWithDimension item;
        item.Category(L"Remove");
        item.Thumbnail(L"ms-appx:///Assets/BigFourSummerHeat.jpg");
        item.Width(std::uniform_real_distribution<>{ 60, 180 }(eng));
        item.Height(std::uniform_real_distribution<>{40, 140}(eng));
        m_wrapPanelCollection.Append(item);
    }

    void WrapPanelPage::AddFixedBtn_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        UWPExample::PhotoDataItemWithDimension item;
        item.Category(L"Remove");
        item.Thumbnail(L"ms-appx:///Assets/BigFourSummerHeat.jpg");
        item.Width(150);
        item.Height(100);
        m_wrapPanelCollection.Append(item);
    }

    void WrapPanelPage::SwitchBtn_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        auto wrapPanelContainer = WrapPanelContainer();
        auto sampleWrapPanel = wrapPanelContainer.ItemsPanelRoot().as<UWPPackage::WrapPanel>();
        if (sampleWrapPanel.Orientation() == winrt::Windows::UI::Xaml::Controls::Orientation::Horizontal)
        {
            sampleWrapPanel.Orientation(winrt::Windows::UI::Xaml::Controls::Orientation::Vertical);
            winrt::Windows::UI::Xaml::Controls::ScrollViewer::SetVerticalScrollMode(wrapPanelContainer, winrt::Windows::UI::Xaml::Controls::ScrollMode::Disabled);
            winrt::Windows::UI::Xaml::Controls::ScrollViewer::SetVerticalScrollBarVisibility(wrapPanelContainer, winrt::Windows::UI::Xaml::Controls::ScrollBarVisibility::Disabled);
            winrt::Windows::UI::Xaml::Controls::ScrollViewer::SetHorizontalScrollMode(wrapPanelContainer, winrt::Windows::UI::Xaml::Controls::ScrollMode::Auto);
            winrt::Windows::UI::Xaml::Controls::ScrollViewer::SetHorizontalScrollBarVisibility(wrapPanelContainer, winrt::Windows::UI::Xaml::Controls::ScrollBarVisibility::Auto);
        }
        else
        {
            sampleWrapPanel.Orientation(winrt::Windows::UI::Xaml::Controls::Orientation::Horizontal);
            winrt::Windows::UI::Xaml::Controls::ScrollViewer::SetVerticalScrollMode(wrapPanelContainer, winrt::Windows::UI::Xaml::Controls::ScrollMode::Auto);
            winrt::Windows::UI::Xaml::Controls::ScrollViewer::SetVerticalScrollBarVisibility(wrapPanelContainer, winrt::Windows::UI::Xaml::Controls::ScrollBarVisibility::Auto);
            winrt::Windows::UI::Xaml::Controls::ScrollViewer::SetHorizontalScrollMode(wrapPanelContainer, winrt::Windows::UI::Xaml::Controls::ScrollMode::Disabled);
            winrt::Windows::UI::Xaml::Controls::ScrollViewer::SetHorizontalScrollBarVisibility(wrapPanelContainer, winrt::Windows::UI::Xaml::Controls::ScrollBarVisibility::Disabled);
        }
    }
}
