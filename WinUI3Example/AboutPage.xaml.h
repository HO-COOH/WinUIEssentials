#pragma once
#include "AboutPage.g.h"
#include "PropertyChangeHelper.hpp"

namespace winrt::WinUI3Example::implementation
{
    struct AboutPage : AboutPageT<AboutPage>, MvvmHelper::PropertyChangeHelper<AboutPage>
    {
        AboutPage();

        static winrt::hstring WASDKReleaseVersion();
        static winrt::hstring WASDKRuntimeVersion();
        static winrt::hstring FormatVersion(
            uint32_t major,
            uint32_t minor,
            uint32_t patch,
            uint32_t majorMinor,
            winrt::hstring const& channel
        );
        void SettingsCard_Click(
            winrt::Windows::Foundation::IInspectable const& sender, 
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Contributors();

    private:
        winrt::fire_and_forget loadContributors();

		winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> m_contributors{ nullptr };
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct AboutPage : AboutPageT<AboutPage, implementation::AboutPage>
    {
    };
}
