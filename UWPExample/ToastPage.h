#pragma once

#include "ToastPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct ToastPage : ToastPageT<ToastPage>
    {
        void BodyTextOnlyBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void SingleLineHeaderWithBodyBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void TwoLineHeaderWithBodyBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void HeaderWithTwoSingleLineBody_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void ImageWithBodyOnly_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void ImageWithHeaderAndBodyBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void ImageWithTwoLineHeaderAndBody_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void ImageWithHeaderAndTwoSingleLineBody_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void ToastBuilderBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        winrt::hstring getAudioSelection();
        void showArgumentToDialog(winrt::Windows::ApplicationModel::Activation::ToastNotificationActivatedEventArgs const& args);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct ToastPage : ToastPageT<ToastPage, implementation::ToastPage>
    {
    };
}
