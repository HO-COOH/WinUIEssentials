#pragma once
#include "ModalWindow.h"
#include "ModernMessageBox.g.h"


namespace winrt::WinUI3Package::implementation
{
    struct ModernMessageBox : winrt::Microsoft::UI::Xaml::Markup::ComponentConnectorT<ModernMessageBoxT<ModernMessageBox>>
    {
        ModernMessageBox()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
        
        static winrt::Windows::Foundation::IAsyncOperation<int32_t> ShowAsync(
            winrt::Microsoft::UI::Xaml::Window const& owner,
            winrt::hstring const& text,
            winrt::hstring const& caption,
			uint16_t type
        );
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    private:
        winrt::handle h{ CreateEvent(nullptr, true, false, nullptr) };
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct ModernMessageBox : ModernMessageBoxT<ModernMessageBox, implementation::ModernMessageBox>
    {
    };
}
