#pragma once
#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>

struct WinUIAsyncEventArgs : 
    winrt::implements<WinUIAsyncEventArgs, winrt::Windows::Foundation::IInspectable>, 
    winrt::deferrable_event_args<WinUIAsyncEventArgs>
{
    WinUIAsyncEventArgs() = default;
    
    bool Cancel{};
};