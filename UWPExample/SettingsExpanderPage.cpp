#include "pch.h"
#include "SettingsExpanderPage.h"
#if __has_include("SettingsExpanderPage.g.cpp")
#include "SettingsExpanderPage.g.cpp"
#endif
#include <winrt/Windows.System.h>
#include "PageTagRegister.h"

namespace winrt::UWPExample::implementation
{
    static PageTagRegister<SettingsExpanderPage> s_tags{ L"settingsexpander", L"setting", L"expander", L"control"};

    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> SettingsExpanderPage::MyDataSet()
    {
        auto copy = m_myDataSet;
        return winrt::single_threaded_vector(std::move(copy));
    }

    void SettingsExpanderPage::Button_Click(
        winrt::Windows::Foundation::IInspectable const& sender, 
        winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        winrt::Windows::System::Launcher::LaunchUriAsync(winrt::Windows::Foundation::Uri{ L"https://microsoft.com/" });
    }

}
