#pragma once

#include "ExperimentPage.g.h"
#include <winrt/Microsoft.UI.Composition.h>

namespace winrt::WinUI3Example::implementation
{
    struct ExperimentPage : ExperimentPageT<ExperimentPage>
    {
        ExperimentPage() = default;
        void SelfDrawnWindowButton_Click(
            winrt::Windows::Foundation::IInspectable const&, 
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const&);

        void TestWindowBtn_Click(
            winrt::Windows::Foundation::IInspectable const& sender, 
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateNonResizableBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateNonResizableWithWorkaroundBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void FlipWindowButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ButtonMorph_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void SlowButtonMorph_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void AddValueButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        winrt::fire_and_forget morphButtonToProgressBar(
            winrt::Microsoft::UI::Xaml::Controls::Button button,
            winrt::Microsoft::UI::Xaml::Controls::ProgressBar progressBar,
            std::chrono::milliseconds duration = {}
        );

        winrt::Microsoft::UI::Composition::CompositionAnimationGroup buttonAnimationGroup{ nullptr };
        winrt::Microsoft::UI::Composition::CompositionAnimationGroup progressBarAnimationGroup{ nullptr };
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ExperimentPage : ExperimentPageT<ExperimentPage, implementation::ExperimentPage>
    {
    };
}
