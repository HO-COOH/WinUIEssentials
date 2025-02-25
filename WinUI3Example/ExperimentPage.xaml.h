#pragma once

#include "ExperimentPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ExperimentPage : ExperimentPageT<ExperimentPage>
    {
        ExperimentPage() = default;
        void StackPanel_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ExperimentPage : ExperimentPageT<ExperimentPage, implementation::ExperimentPage>
    {
    };
}
