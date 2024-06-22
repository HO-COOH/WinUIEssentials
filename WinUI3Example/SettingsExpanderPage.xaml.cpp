// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "SettingsExpanderPage.xaml.h"
#if __has_include("SettingsExpanderPage.g.cpp")
#include "SettingsExpanderPage.g.cpp"
#endif
#include <winrt/Windows.System.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    SettingsExpanderPage::SettingsExpanderPage()
    {
        InitializeComponent();
    }

    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> SettingsExpanderPage::MyDataSet()
    {
        auto copy = m_myDataSet;
        return winrt::single_threaded_vector(std::move(copy));
    }

    void SettingsExpanderPage::Button_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        winrt::Windows::System::Launcher::LaunchUriAsync(winrt::Windows::Foundation::Uri{ L"https://microsoft.com/" });
    }
}
