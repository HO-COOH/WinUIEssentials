#pragma once

#include "CursorWorkaroundPage.g.h"
#include "PropertyChangeHelper.hpp"

namespace winrt::WinUI3Example::implementation
{
	struct CursorWorkaroundPage : CursorWorkaroundPageT<CursorWorkaroundPage>, MvvmHelper::PropertyChangeHelper<CursorWorkaroundPage>
    {
        void ToggleButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
		bool WorkaroundApplied();
		static winrt::hstring GetButtonText(bool applied);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct CursorWorkaroundPage : CursorWorkaroundPageT<CursorWorkaroundPage, implementation::CursorWorkaroundPage>
    {
    };
}
