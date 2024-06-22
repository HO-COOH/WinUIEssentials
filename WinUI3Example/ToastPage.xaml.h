// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "ToastPage.g.h"
#include <ToastBuilder.hpp>

namespace winrt::WinUI3Example::implementation
{
    struct ToastPage : ToastPageT<ToastPage>
    {
        ToastPage();

        void BodyTextOnlyBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void SingleLineHeaderWithBodyBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void TwoLineHeaderWithBodyBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void HeaderWithTwoSingleLineBody_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ImageWithBodyOnly_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ImageWithHeaderAndBodyBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ImageWithTwoLineHeaderAndBody_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ImageWithHeaderAndTwoSingleLineBody_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ToastBuilderBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    private:
        winrt::hstring getAudioSelection();
        void showArgumentToDialog(winrt::Microsoft::Windows::AppNotifications::AppNotificationActivatedEventArgs const& args);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ToastPage : ToastPageT<ToastPage, implementation::ToastPage>
    {
    };
}
