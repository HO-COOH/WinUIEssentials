#pragma once
#include <winrt/Microsoft.UI.Content.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Windowing.h>
#include <HwndHelper.hpp>
#include <CommCtrl.h>
#include <utility>
#include "MenuFlyoutItemPaddingWorkaroundWrapper.hpp"
#include "WindowContextMenuUtils.h"

template<typename Derived, UINT_PTR SubclassId>
class WindowContextMenuBase : protected MenuFlyoutItemPaddingWorkaroundWrapper
{
    auto getSelf()
    {
        return static_cast<Derived*>(this);
    }
public:
    winrt::Microsoft::UI::Xaml::Window Window()
    {
        return m_window.get();
    }

    [[maybe_unused]] bool Window(winrt::Microsoft::UI::Xaml::Window const& window)
    {
        if (m_window.get() == window)
            return false;

        removeSubclassIfSet();
        m_window = window;
        m_parent = window ? GetHwnd(window) : HWND{};
        m_converter = window ?
            winrt::Microsoft::UI::Content::ContentCoordinateConverter::CreateForWindowId(window.AppWindow().Id()) :
            nullptr;

        if (!window)
            return false;

        m_setSubclass = SetWindowSubclass(
            m_parent,
            &Derived::subclassProc,
            SubclassId,
            reinterpret_cast<DWORD_PTR>(getSelf())
        );
        return true;
    }

    ~WindowContextMenuBase()
    {
        removeSubclassIfSet();
    }
protected:
    /**
     * @brief Show `menu` at the point carried by the `lparam` of a right click message
     * @return false when there is nothing to show, so the caller can let the message through
     */
    bool showMenu(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& menu, LPARAM lparam)
    {
        auto const window = m_window.get();
        if (!menu || !window)
            return false;

        //The menu is not in the window's tree, so it has no XamlRoot to inherit
        if (IsFirstShow())
            menu.XamlRoot(window.Content().XamlRoot());

        ShowAtImpl(menu, nullptr, WindowContextMenuUtils::GetFlyoutShowOptions(m_parent, lparam, m_converter));
        return true;
    }

    /*Call from `WM_NCDESTROY`, the window is about to take the subclass with it*/
    void removeSubclassIfSet()
    {
        if (std::exchange(m_setSubclass, false) && m_parent)
            RemoveWindowSubclass(m_parent, &Derived::subclassProc, SubclassId);
    }

    /*Weak, or the reference the window holds to this menu closes a cycle and neither is ever freed*/
    winrt::weak_ref<winrt::Microsoft::UI::Xaml::Window> m_window{ nullptr };
    winrt::Microsoft::UI::Content::ContentCoordinateConverter m_converter{ nullptr };
    HWND m_parent{};
    bool m_setSubclass{};
};
