#pragma once

#include "RowRequestedEventArgs.g.h"

namespace winrt::PackageRoot::implementation
{
    struct RowRequestedEventArgs : RowRequestedEventArgsT<RowRequestedEventArgs>
    {
        RowRequestedEventArgs(int startRow, int endRow);

        int StartRow();
        int EndRow();
        void SetRow(int row, winrt::array_view<winrt::hstring const> const& content);
        bool IsCanceled();

        winrt::event_token Canceled(winrt::Windows::Foundation::EventHandler<winrt::PackageRoot::RowRequestedEventArgs> const& handler);
        void Canceled(winrt::event_token const& token);
    private:
        winrt::event<winrt::Windows::Foundation::EventHandler<winrt::PackageRoot::RowRequestedEventArgs>> m_canceled;
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct RowRequestedEventArgs : RowRequestedEventArgsT<RowRequestedEventArgs, implementation::RowRequestedEventArgs>
    {
    };
}
