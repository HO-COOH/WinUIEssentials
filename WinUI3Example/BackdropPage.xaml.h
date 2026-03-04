#pragma once

#include "BackdropPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct BackdropPage : BackdropPageT<BackdropPage>
    {
        BackdropPage() = default;

        void CreateAcrylicButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateMicaButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateDefaultAcrylicButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateStandardAcrylicButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateDefaultMicaButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateStandardMicaButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateTransparentButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateMicaWithFallbackButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        //void SwitchBackdropButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        static std::vector<winrt::Windows::Foundation::IInspectable> Components();
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct BackdropPage : BackdropPageT<BackdropPage, implementation::BackdropPage>
    {
    };
}
