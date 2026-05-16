#pragma once

#include "SvgPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct SvgPage : SvgPageT<SvgPage>
    {
        SvgPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Svgs();
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Pngs();

        void ListViewScrollViewer_ViewChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs const& e);

    private:
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> m_svgs{ nullptr };
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> m_pngs{ nullptr };

        winrt::Microsoft::UI::Xaml::Controls::ScrollViewer m_svgScroll{ nullptr };
        winrt::Microsoft::UI::Xaml::Controls::ScrollViewer m_pngScroll{ nullptr };
        bool m_isSyncing{ false };

        void SyncFrom(winrt::Microsoft::UI::Xaml::Controls::ScrollViewer const& source, winrt::Microsoft::UI::Xaml::Controls::ScrollViewer const& target);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct SvgPage : SvgPageT<SvgPage, implementation::SvgPage>
    {
    };
}
