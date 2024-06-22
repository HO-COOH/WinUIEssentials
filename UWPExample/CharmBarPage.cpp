#include "pch.h"
#include "CharmBarPage.h"
#if __has_include("CharmBarPage.g.cpp")
#include "CharmBarPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::UWPExample::implementation
{

    void CharmBarPage::LocalSettingsButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        LocalSettings().ShowCurrent();
    }

    void CharmBarPage::GlobalSettingsButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        UWPPackage::SettingsPaneEx::Show();
    }
}
