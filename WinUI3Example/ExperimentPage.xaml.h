#pragma once

#include "ExperimentPage.g.h"
#include <winrt/Microsoft.UI.Composition.h>

namespace winrt::WinUI3Example::implementation
{
    struct ExperimentPage : ExperimentPageT<ExperimentPage>
    {
        ExperimentPage();
        ~ExperimentPage();

        void OnTick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e);

        void SelfDrawnWindowButton_Click(
            winrt::Windows::Foundation::IInspectable const&, 
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const&);
       
        void FlipWindowButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ButtonMorph_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void SlowButtonMorph_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void AddValueButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        winrt::fire_and_forget morphButtonToProgressBar(
            winrt::Microsoft::UI::Xaml::Controls::Button button,
            winrt::Microsoft::UI::Xaml::Controls::ProgressBar progressBar,
            std::chrono::milliseconds duration = {}
        );

        void NormalInnerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ToggleInnerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        winrt::Microsoft::UI::Xaml::DispatcherTimer m_timer;

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
