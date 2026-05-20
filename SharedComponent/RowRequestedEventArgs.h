#pragma once

#include "RowRequestedEventArgs.g.h"

class TextLayoutCache;

namespace winrt::PackageRoot::implementation
{
    struct RowRequestedEventArgs : RowRequestedEventArgsT<RowRequestedEventArgs>
    {
        RowRequestedEventArgs(int startRow, int endRow, TextLayoutCache& cache);

        int StartRow();
        int EndRow();
        void SetRow(int row, winrt::array_view<winrt::hstring const> const& content);
        bool IsCanceled();

        winrt::event_token Canceled(winrt::Windows::Foundation::EventHandler<winrt::PackageRoot::RowRequestedEventArgs> const& handler);
        void Canceled(winrt::event_token const& token);

    private:
        winrt::event<winrt::Windows::Foundation::EventHandler<winrt::PackageRoot::RowRequestedEventArgs>> m_canceled;
        int m_startRow{};
        int m_endRow{};
        TextLayoutCache& m_cache;
    };
}

