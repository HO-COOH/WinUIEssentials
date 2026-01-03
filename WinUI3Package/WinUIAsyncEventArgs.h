#pragma once

#include "WinUIAsyncEventArgs.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct WinUIAsyncEventArgs : WinUIAsyncEventArgsT<WinUIAsyncEventArgs>, winrt::deferrable_event_args<WinUIAsyncEventArgs>
    {
        WinUIAsyncEventArgs() = default;


        bool Cancel();
        void Cancel(bool Value);



    private:

        bool m_Cancel{};
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct WinUIAsyncEventArgs : WinUIAsyncEventArgsT<WinUIAsyncEventArgs, implementation::WinUIAsyncEventArgs>
    {
    };
}
