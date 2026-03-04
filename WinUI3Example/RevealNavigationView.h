#pragma once

#include "RevealNavigationView.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct RevealNavigationView : RevealNavigationViewT<RevealNavigationView>
    {
        RevealNavigationView() = default;

        void OnApplyTemplate();

    private:
		winrt::WinUI3Package::RevealFocusPanel m_revealFocusPanel{ nullptr };
        void onItemsRepeaterElementPrepared(
            winrt::Microsoft::UI::Xaml::Controls::ItemsRepeater const& itemsRepeater,
            winrt::Microsoft::UI::Xaml::Controls::ItemsRepeaterElementPreparedEventArgs const& args
        );
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct RevealNavigationView : RevealNavigationViewT<RevealNavigationView, implementation::RevealNavigationView>
    {
    };
}
