#pragma once

#include "ModernWindowCaptionButtonToolTip.g.h"
#include <chrono>
#include <winrt/Microsoft.UI.Windowing.h>
#include "CaptionButton.h"
#include "InputNonClientPointerSource.h"

namespace winrt::WinUI3Package::implementation
{
    struct ModernWindowCaptionButtonToolTip : ModernWindowCaptionButtonToolTipT<ModernWindowCaptionButtonToolTip>
    {
        ModernWindowCaptionButtonToolTip();
        ModernWindowCaptionButtonToolTip(winrt::Microsoft::UI::Xaml::Window const& window);
        ~ModernWindowCaptionButtonToolTip();

        winrt::Microsoft::UI::Xaml::Window Window();
        void Window(winrt::Microsoft::UI::Xaml::Window const& window);

        void SetHoveredButton(CaptionButton button);
        void CloseToolTip();
        bool m_isSuppressedUntilButtonChanges{};
    private:
        winrt::weak_ref<winrt::Microsoft::UI::Xaml::Window> m_window;
        HWND m_hwnd{};
        InputNonClientPointerSource m_nonClientInputSink{ this };
        CaptionButton m_hoveredButton{ CaptionButton::None };
        std::chrono::steady_clock::time_point m_lastToolTipClosedTick{};

        winrt::Microsoft::UI::Xaml::Controls::ToolTip m_toolTip{ nullptr };
        winrt::Microsoft::UI::Xaml::Media::TranslateTransform m_placementTransform{ nullptr };
        winrt::Microsoft::UI::Dispatching::DispatcherQueueTimer m_openTimer{ nullptr };
        winrt::Microsoft::UI::Dispatching::DispatcherQueueTimer m_closeTimer{ nullptr };
        winrt::Microsoft::UI::Dispatching::DispatcherQueueTimer::Tick_revoker m_openTimerRevoker;
        winrt::Microsoft::UI::Dispatching::DispatcherQueueTimer::Tick_revoker m_closeTimerRevoker;
        //AppWindow does not support weak references, so its event cannot use auto_revoke
        winrt::Microsoft::UI::Windowing::AppWindow m_appWindow{ nullptr };
        winrt::event_token m_appWindowChangedToken{};

        void translateSelf(winrt::Windows::Foundation::Point anchor);
        void setWindow(winrt::Microsoft::UI::Xaml::Window const& window);
        void detachWindow();
        void ensureTimers();
        void ensureToolTip();
        void showToolTip();

        void updateToolTipTheme();
        bool isButtonEnabled(CaptionButton button) const;
        winrt::hstring getToolTipText(CaptionButton button) const;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct ModernWindowCaptionButtonToolTip : ModernWindowCaptionButtonToolTipT<ModernWindowCaptionButtonToolTip, implementation::ModernWindowCaptionButtonToolTip>
    {
    };
}
