#pragma once
#include <vector>
#include <wil/resource.h>

namespace winrt::WinUI3Package::implementation
{
    struct WebView;

    class WebViewMouseHook
    {
    public:
        explicit WebViewMouseHook(WebView* self);
        ~WebViewMouseHook();

        WebViewMouseHook(WebViewMouseHook const&) = delete;
        WebViewMouseHook& operator=(WebViewMouseHook const&) = delete;
        WebViewMouseHook(WebViewMouseHook&&) = delete;
        WebViewMouseHook& operator=(WebViewMouseHook&&) = delete;

    private:
        static LRESULT CALLBACK hookProc(int code, WPARAM wparam, LPARAM lparam);

        WebView* m_self;

        static thread_local wil::unique_hhook s_hook;
        static thread_local std::vector<WebView*> s_instances;
    };
}
