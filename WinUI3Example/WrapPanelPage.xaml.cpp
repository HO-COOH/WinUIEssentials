#include "pch.h"
#include "WrapPanelPage.xaml.h"
#if __has_include("WrapPanelPage.g.cpp")
#include "WrapPanelPage.g.cpp"
#endif
#include <random>
#include <VisualTreeHelper.hpp>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    winrt::Windows::Foundation::Collections::IObservableVector<WinUI3Example::PhotoDataItemWithDimension> WrapPanelPage::WrapPanelCollection()
    {
        return m_wrapPanelCollection;
    }

    void WrapPanelPage::ItemControl_ItemClick(
        winrt::Windows::Foundation::IInspectable const& sender, 
        winrt::Microsoft::UI::Xaml::Controls::ItemClickEventArgs const& e)
    {
        if (auto item = e.ClickedItem().try_as<WinUI3Example::PhotoDataItemWithDimension>())
        {
            uint32_t index;
            m_wrapPanelCollection.IndexOf(item, index);
            m_wrapPanelCollection.RemoveAt(index);
        }
    }

    void WrapPanelPage::AddButton_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        static std::mt19937 eng{ std::random_device{}() };
        
        WinUI3Example::PhotoDataItemWithDimension item;
        item.Category(L"Remove");
        item.Thumbnail(L"ms-appx:///Assets/BigFourSummerHeat.jpg");
        item.Width(std::uniform_real_distribution<>{ 60, 180 }(eng));
        item.Height(std::uniform_real_distribution<>{40, 140}(eng));
        m_wrapPanelCollection.Append(item);
    }

    void WrapPanelPage::AddFixedBtn_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        WinUI3Example::PhotoDataItemWithDimension item;
        item.Category(L"Remove");
        item.Thumbnail(L"ms-appx:///Assets/BigFourSummerHeat.jpg");
        item.Width(150);
        item.Height(100);
        m_wrapPanelCollection.Append(item);
    }

    void WrapPanelPage::SwitchBtn_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto wrapPanelContainer = WrapPanelContainer();
        if (auto sampleWrapPanel = VisualTreeHelper::FindVisualChildByType<winrt::WinUI3Package::WrapPanel>(wrapPanelContainer))
        {
            if (sampleWrapPanel.Orientation() == winrt::Microsoft::UI::Xaml::Controls::Orientation::Horizontal)
            {
                sampleWrapPanel.Orientation(winrt::Microsoft::UI::Xaml::Controls::Orientation::Vertical);
                winrt::Microsoft::UI::Xaml::Controls::ScrollViewer::SetVerticalScrollMode(wrapPanelContainer, winrt::Microsoft::UI::Xaml::Controls::ScrollMode::Disabled);
                winrt::Microsoft::UI::Xaml::Controls::ScrollViewer::SetVerticalScrollBarVisibility(wrapPanelContainer, winrt::Microsoft::UI::Xaml::Controls::ScrollBarVisibility::Disabled);
                winrt::Microsoft::UI::Xaml::Controls::ScrollViewer::SetHorizontalScrollMode(wrapPanelContainer, winrt::Microsoft::UI::Xaml::Controls::ScrollMode::Auto);
                winrt::Microsoft::UI::Xaml::Controls::ScrollViewer::SetHorizontalScrollBarVisibility(wrapPanelContainer, winrt::Microsoft::UI::Xaml::Controls::ScrollBarVisibility::Auto);
            }
            else
            {
                sampleWrapPanel.Orientation(winrt::Microsoft::UI::Xaml::Controls::Orientation::Horizontal);
                winrt::Microsoft::UI::Xaml::Controls::ScrollViewer::SetVerticalScrollMode(wrapPanelContainer, winrt::Microsoft::UI::Xaml::Controls::ScrollMode::Auto);
                winrt::Microsoft::UI::Xaml::Controls::ScrollViewer::SetVerticalScrollBarVisibility(wrapPanelContainer, winrt::Microsoft::UI::Xaml::Controls::ScrollBarVisibility::Auto);
                winrt::Microsoft::UI::Xaml::Controls::ScrollViewer::SetHorizontalScrollMode(wrapPanelContainer, winrt::Microsoft::UI::Xaml::Controls::ScrollMode::Disabled);
                winrt::Microsoft::UI::Xaml::Controls::ScrollViewer::SetHorizontalScrollBarVisibility(wrapPanelContainer, winrt::Microsoft::UI::Xaml::Controls::ScrollBarVisibility::Disabled);
            }
        }
    }
}
