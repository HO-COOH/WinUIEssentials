#include "pch.h"
#include "WebViewMouseHook.h"
#include "WebView.h"
#include <algorithm>


namespace winrt::WinUI3Package::implementation
{
    thread_local wil::unique_hhook WebViewMouseHook::s_hook;
    thread_local std::vector<WebView*> WebViewMouseHook::s_instances;

    WebViewMouseHook::WebViewMouseHook(WebView* self) : m_self{ self }
    {
        s_instances.push_back(self);
        if (!s_hook)
            s_hook.reset(::SetWindowsHookExW(WH_MOUSE_LL, &WebViewMouseHook::hookProc, ::GetModuleHandleW(nullptr), 0));
    }

    WebViewMouseHook::~WebViewMouseHook()
    {
        s_instances.erase(
            std::remove(s_instances.begin(), s_instances.end(), m_self),
            s_instances.end());

        if (s_instances.empty() && s_hook)
            s_hook = nullptr;
    }

    LRESULT CALLBACK WebViewMouseHook::hookProc(int code, WPARAM wparam, LPARAM lparam)
    {
        if (code == HC_ACTION && (wparam == WM_RBUTTONUP || wparam == WM_RBUTTONDOWN))
        {
            auto const* info = reinterpret_cast<MSLLHOOKSTRUCT*>(lparam);
            for (auto* self : s_instances)
            {
                if (self->isPointInWebView(info->pt))
                    return 1; // discard: do not deliver the click to any window
            }
        }
        return ::CallNextHookEx(nullptr, code, wparam, lparam);
    }
}
