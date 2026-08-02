#pragma once

#include "WebViewPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct WebViewPage : WebViewPageT<WebViewPage>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct WebViewPage : WebViewPageT<WebViewPage, implementation::WebViewPage>
    {
    };
}
