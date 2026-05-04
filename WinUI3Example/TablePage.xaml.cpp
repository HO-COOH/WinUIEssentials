#include "pch.h"
#include "TablePage.xaml.h"
#if __has_include("TablePage.g.cpp")
#include "TablePage.g.cpp"
#endif

#include <VisualTreeHelper.hpp>

namespace winrt::WinUI3Example::implementation
{
    void TablePage::OnLoaded(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        //Walk up the visual tree to find the hosting ScrollViewer so we can
        //size this page to its viewport. The Frame that hosts us lives inside
        //a ScrollViewer in MainWindow, which feeds infinite height downward —
        //without this we can't honor VerticalAlignment=Stretch.
        if (auto sv = VisualTreeHelper::FindVisualParentByType<winrt::Microsoft::UI::Xaml::Controls::ScrollViewer>(*this))
        {
            m_scrollViewer = sv;
            m_sizeChangedRevoker = sv.SizeChanged(winrt::auto_revoke, { this, &TablePage::OnScrollViewerSizeChanged });
        }
        syncHeight();
    }

    void TablePage::OnUnloaded(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        m_sizeChangedRevoker.revoke();
        m_scrollViewer = nullptr;
    }

    void TablePage::OnScrollViewerSizeChanged(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const&)
    {
        syncHeight();
    }

    void TablePage::syncHeight()
    {
        if (!m_scrollViewer)
            return;
        auto const h = m_scrollViewer.ViewportHeight();
        if (h > 0)
            Height(h);
    }
}
