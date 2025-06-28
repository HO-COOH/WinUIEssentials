#pragma once

#include "ModernMessageBoxPage.g.h"
#include <PropertyChangeHelper.hpp>

namespace winrt::WinUI3Example::implementation
{
	struct ModernMessageBoxPage : ModernMessageBoxPageT<ModernMessageBoxPage>, MvvmHelper::PropertyChangeHelper<ModernMessageBoxPage>
    {
        ModernMessageBoxPage() = default;

        winrt::hstring ClassicMessageBoxOutput();

        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void Button_Click_1(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    private:
        UINT getClassicMessageBoxFlags();
        static UINT getClassicMessageBoxButtons(int selection);
		static UINT getClassicMessageBoxIcon(int selection);
		static UINT getClassicMessageBoxDefaultButton(int selection);

        void classicMessageBoxReturn(int value);
        int m_classicMessageBoxReturn = -1;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ModernMessageBoxPage : ModernMessageBoxPageT<ModernMessageBoxPage, implementation::ModernMessageBoxPage>
    {
    };
}
