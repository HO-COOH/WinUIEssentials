#pragma once

struct TaskbarIconXamlEvents
{
    winrt::event<winrt::WinUI3Package::SignalDelegate> m_leftPressed;
    winrt::event<winrt::WinUI3Package::SignalDelegate> m_leftDoublePressed;
    winrt::event<winrt::WinUI3Package::SignalDelegate> m_rightPressed;
    winrt::event<winrt::WinUI3Package::SignalDelegate> m_pointerHover;
};
