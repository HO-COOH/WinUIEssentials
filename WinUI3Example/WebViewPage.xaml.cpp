#include "pch.h"
#include "WebViewPage.xaml.h"
#if __has_include("WebViewPage.g.cpp")
#include "WebViewPage.g.cpp"
#endif
#include "PageTagRegister.h"

namespace winrt::WinUI3Example::implementation
{
    static PageTagRegister<WebViewPage> s_tags{ L"webview", L"webview2", L"browser", L"control" };

}
