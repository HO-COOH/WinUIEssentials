#pragma once

#include "BackdropPage.g.h"
#include <array>
#include <boost/hana.hpp>
#include "ComponentTag.h"

namespace winrt::WinUI3Example::implementation
{
    struct BackdropPage : BackdropPageT<BackdropPage>
    {
        constexpr static auto Components = boost::hana::make_tuple(
            boost::hana::make_pair(L"CustomAcrylicBackdrop", boost::hana::make_tuple(ComponentTag::Idl{}, ComponentTag::H{}, ComponentTag::Cpp{})),
            boost::hana::make_pair(L"CustomMicaBackdrop", boost::hana::make_tuple(ComponentTag::Idl{}, ComponentTag::H{}, ComponentTag::Cpp{})),
            boost::hana::make_pair(L"MicaBackdropWithFallback", boost::hana::make_tuple(ComponentTag::Idl{}, ComponentTag::H{}, ComponentTag::Cpp{}))
        );

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
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct BackdropPage : BackdropPageT<BackdropPage, implementation::BackdropPage>
    {
    };
}
