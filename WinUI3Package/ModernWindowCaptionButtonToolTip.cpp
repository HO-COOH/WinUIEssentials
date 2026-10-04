#include "pch.h"
#include "ModernWindowCaptionButtonToolTip.h"
#if __has_include("ModernWindowCaptionButtonToolTip.g.cpp")
#include "ModernWindowCaptionButtonToolTip.g.cpp"
#endif
#include "HwndHelper.hpp"
#include "SystemParametersInfo.h"
#include "User32String.h"

constexpr static std::chrono::milliseconds BetweenShowDelay{ 200 };
constexpr static std::chrono::milliseconds PointerCheckInterval{ 100 };
constexpr static float MouseOffset = 20.f;

namespace winrt::WinUI3Package::implementation
{
    ModernWindowCaptionButtonToolTip::ModernWindowCaptionButtonToolTip()
    {
        IsTabStop(false);
        IsHitTestVisible(false);

        Loaded([this](auto&&...) 
        {
            try
            {
                if (m_hwnd && !m_nonClientInputSink)
                    m_nonClientInputSink.Initialize(m_hwnd);
            }
            catch (...)
            {
            }
        });
        Unloaded([this](auto&&...) 
        {
            try
            {
                SetHoveredButton(CaptionButton::None);
            }
            catch (...)
            {
            }
        });
        ActualThemeChanged([this](auto&&...) 
        {
            try
            {
                updateToolTipTheme();
            }
            catch (...)
            {
            }
        });
    }

    ModernWindowCaptionButtonToolTip::ModernWindowCaptionButtonToolTip(winrt::Microsoft::UI::Xaml::Window const& window) :
        ModernWindowCaptionButtonToolTip()
    {
        setWindow(window);
    }

    ModernWindowCaptionButtonToolTip::~ModernWindowCaptionButtonToolTip()
    {
        try
        {
            detachWindow();
        }
        catch (...)
        {
        }
    }

    winrt::Microsoft::UI::Xaml::Window ModernWindowCaptionButtonToolTip::Window()
    {
        return m_window.get();
    }

    void ModernWindowCaptionButtonToolTip::Window(winrt::Microsoft::UI::Xaml::Window const& window)
    {
        if (window == m_window.get())
            return;

        detachWindow();
        setWindow(window);
    }

    void ModernWindowCaptionButtonToolTip::translateSelf(winrt::Windows::Foundation::Point anchor)
    {
        /*
            WinUI clamps the tooltip to the monitor under the PlacementTarget's top-left corner.
            We have to use a transform to move this invisible control to the correct monitor in case the window spans multiple monitors
        */
        if (!m_placementTransform)
        {
            m_placementTransform = winrt::Microsoft::UI::Xaml::Media::TranslateTransform{};
            RenderTransform(m_placementTransform);
        }
        auto const offset = TransformToVisual(nullptr).Inverse().TransformPoint(anchor);
        m_placementTransform.X(m_placementTransform.X() + offset.X);
        m_placementTransform.Y(m_placementTransform.Y() + offset.Y);
    }

    void ModernWindowCaptionButtonToolTip::setWindow(winrt::Microsoft::UI::Xaml::Window const& window)
    {
        if (!window)
            return;

        m_window = window;
        m_hwnd = GetHwnd(window);
        m_appWindow = window.AppWindow();
        if (m_appWindow)
        {
            m_appWindowChangedToken = m_appWindow.Changed([this](auto&&, winrt::Microsoft::UI::Windowing::AppWindowChangedEventArgs const& args)
            {
                if (args.DidPositionChange() || args.DidSizeChange() || args.DidPresenterChange() || args.DidVisibilityChange())
                    CloseToolTip();
            });
        }
        m_nonClientInputSink.Initialize(m_hwnd);
    }

    void ModernWindowCaptionButtonToolTip::detachWindow()
    {
        //Win32 cleanup first, so a throwing WinRT call below can never leave this object registered with Windows
        m_nonClientInputSink.Initialize(nullptr);

        m_hwnd = nullptr;
        m_window = nullptr;

        if (auto const appWindow = std::exchange(m_appWindow, nullptr))
            appWindow.Changed(std::exchange(m_appWindowChangedToken, {}));

        SetHoveredButton(CaptionButton::None);
    }

    void ModernWindowCaptionButtonToolTip::SetHoveredButton(CaptionButton button)
    {
        auto const previousButton = std::exchange(m_hoveredButton, button);

        if (button == previousButton)
            return;

        m_isSuppressedUntilButtonChanges = false;

        //A tooltip that is already showing moves to the next caption button without delay
        if (previousButton != CaptionButton::None && isButtonEnabled(button) && m_toolTip && m_toolTip.IsOpen())
        {
            showToolTip();
            return;
        }

        CloseToolTip();

        if (button == CaptionButton::None)
            return;

        ensureTimers();

        static const auto hoverTimeMs = SystemParametersInfo::Input::MouseHoverTime();
        auto const isReshow = std::chrono::steady_clock::now() - m_lastToolTipClosedTick < BetweenShowDelay;
        m_openTimer.Interval(std::chrono::milliseconds{ isReshow ? hoverTimeMs * 3 / 2 : hoverTimeMs * 2 });
        m_openTimer.Start();
    }

    void ModernWindowCaptionButtonToolTip::ensureTimers()
    {
        if (m_openTimer)
            return;

        auto const queue = DispatcherQueue();

        m_openTimer = queue.CreateTimer();
        m_openTimer.IsRepeating(false);
        m_openTimerRevoker = m_openTimer.Tick(winrt::auto_revoke, [this](auto&&, auto&&) 
        {
            try
            {
                if (m_hoveredButton != CaptionButton::None && !m_isSuppressedUntilButtonChanges)
                    showToolTip();
            }
            catch (...)
            {
            }
        });

        m_closeTimer = queue.CreateTimer();
        m_closeTimer.IsRepeating(false);
        m_closeTimerRevoker = m_closeTimer.Tick(winrt::auto_revoke, [this](auto&&, auto&&) 
        {
            try
            {
                CloseToolTip();
                m_isSuppressedUntilButtonChanges = true;
            }
            catch (...)
            {
            }
        });
    }

    bool ModernWindowCaptionButtonToolTip::isButtonEnabled(CaptionButton button) const
    {
        return button.IsEnabled(m_hwnd);
    }

    winrt::hstring ModernWindowCaptionButtonToolTip::getToolTipText(CaptionButton button) const
    {
        static User32String const s_user32String;
        switch (button)
        {
            case CaptionButton::Minimize:   return s_user32String.Minimize();
            case CaptionButton::Maximize:   return IsZoomed(m_hwnd) ? s_user32String.RestoreDown() : s_user32String.Maximize();
            case CaptionButton::Close:      return s_user32String.Close();
            default:                        return {};
        }
    }

	void ModernWindowCaptionButtonToolTip::ensureToolTip()
	{
		if (m_toolTip)
			return;
		m_toolTip = winrt::Microsoft::UI::Xaml::Controls::ToolTip{};
		m_toolTip.Placement(winrt::Microsoft::UI::Xaml::Controls::Primitives::PlacementMode::Bottom);
		m_toolTip.PlacementTarget(*this);
		winrt::WinUI3Package::ToolTipHelper::SetAcrylicWorkaround(m_toolTip, true);
		winrt::Microsoft::UI::Xaml::Controls::ToolTipService::SetToolTip(*this, m_toolTip);
	}

    void ModernWindowCaptionButtonToolTip::showToolTip()
    {
        auto const xamlRoot = XamlRoot();
        if (!xamlRoot || !m_hwnd || !isButtonEnabled(m_hoveredButton))
            return;

        POINT cursor{};
        GetCursorPos(&cursor);

        RECT captionRect{ .top = cursor.y };
        if (m_nonClientInputSink)
            GetWindowRect(m_nonClientInputSink, &captionRect);
        POINT captionTop{ cursor.x, (std::min)(captionRect.top, cursor.y) };
        ScreenToClient(m_hwnd, &cursor);
        ScreenToClient(m_hwnd, &captionTop);

        float const scale = xamlRoot.RasterizationScale();
        float const cursorY = cursor.y / scale;
        winrt::Windows::Foundation::Point const anchor
        {
            cursor.x / scale,
            captionTop.y / scale
        };

		translateSelf(anchor);

        ensureToolTip();
        auto const isOpen = m_toolTip.IsOpen();
        //WinUI only places an open tooltip again when PlacementRect changes, we have to force a re-assign
        if (isOpen)
            m_toolTip.PlacementRect(nullptr);

        //Below the cursor normally, but above the whole title bar when WinUI flips it for lack of space,
        //otherwise it would cover the cursor and the caption buttons
        m_toolTip.PlacementRect(winrt::Windows::Foundation::Rect{
            0.f,
            0.f,
            1.f,
            cursorY + MouseOffset - anchor.Y
        });
        m_toolTip.Content(winrt::box_value(getToolTipText(m_hoveredButton)));
        updateToolTipTheme();
        if (!isOpen)
            m_toolTip.IsOpen(true);

        m_closeTimer.Stop();
        m_closeTimer.Interval(std::chrono::seconds{ SystemParametersInfo::Accessibility::MessageDuration() });
        m_closeTimer.Start();
    }

    void ModernWindowCaptionButtonToolTip::CloseToolTip()
    {
        if (m_openTimer)
            m_openTimer.Stop();
        if (m_closeTimer)
            m_closeTimer.Stop();
        if (m_toolTip && m_toolTip.IsOpen())
        {
            m_toolTip.IsOpen(false);
            m_lastToolTipClosedTick = std::chrono::steady_clock::now();
        }
    }

    void ModernWindowCaptionButtonToolTip::updateToolTipTheme()
    {
        if (!m_toolTip)
            return;

        auto const theme = ActualTheme();
        m_toolTip.RequestedTheme(theme);

        //ToolTipHelper only themes the backdrop the first time the popup loads, but the popup is reused, so we need to update it here
        if (auto const popup = m_toolTip.Parent().try_as<winrt::Microsoft::UI::Xaml::Controls::Primitives::Popup>())
        {
            if (auto const backdrop = popup.SystemBackdrop().try_as<winrt::WinUI3Package::CustomAcrylicBackdrop>())
                backdrop.RequestedTheme(theme);
        }
    }
}
