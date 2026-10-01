#pragma once
#include <winrt/Microsoft.UI.Content.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Microsoft.UI.Windowing.h>
#include <HwndHelper.hpp>
#include <CommCtrl.h>
#include <utility>
#include "MenuFlyoutItemPaddingWorkaroundWrapper.hpp"
#include "WindowContextMenuUtils.h"

template<typename Derived, UINT_PTR SubclassId>
class WindowContextMenuBase : protected MenuFlyoutItemPaddingWorkaroundWrapper
{
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
        if (!window)
        {
            m_parent = {};
            m_converter = nullptr;
            return false;
        }

        m_parent = GetHwnd(window);
        m_converter = winrt::Microsoft::UI::Content::ContentCoordinateConverter::CreateForWindowId(window.AppWindow().Id());
        m_setSubclass = SetWindowSubclass(
            m_parent,
            &Derived::subclassProc,
            SubclassId,
            reinterpret_cast<DWORD_PTR>(static_cast<Derived*>(this))
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
        if (!prepareMenu(menu))
            return false;

        ShowAtImpl(menu, nullptr, WindowContextMenuUtils::GetFlyoutShowOptions(m_parent, lparam, m_converter));
        return true;
    }

    /**
     * @brief Show `menu` in place of the system menu that Alt+Space opens, 
     * which arrives as a `WM_SYSCOMMAND` of `SC_KEYMENU` carrying the space character in `lparam`
     * @return false when the message is not Alt+Space or there is nothing to show, so the caller can let the message through
     */
    bool showMenuOnAltSpace(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& menu, WPARAM wparam, LPARAM lparam)
    {
        //The low four bits of wparam are used internally by the system.
        //A minimized window has no content to show the menu in, so leave that to the system menu
        if ((wparam & 0xFFF0) != SC_KEYMENU || lparam != VK_SPACE || IsIconic(m_parent))
            return false;

        auto const window = prepareMenu(menu);
        if (!window)
            return false;

        removeFocus(menu);
        ShowAtImpl(menu, nullptr, WindowContextMenuUtils::GetFlyoutShowOptions(m_parent, window.AppWindow().TitleBar()));
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
private:
    winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase::Opened_revoker m_openedRevoker;

    /**
     * @return the window to show `menu` in, or null when there is nothing to show or nowhere to show it
     */
    winrt::Microsoft::UI::Xaml::Window prepareMenu(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& menu)
    {
        auto window = m_window.get();
        if (!menu || !window)
            return nullptr;

        //The menu is not in the window's tree, so it has no XamlRoot to inherit.
        //Window has no XamlRoot of its own, so an empty window leaves the menu nowhere to show
        if (IsFirstShow())
        {
            auto const content = window.Content();
            auto const xamlRoot = content ? content.XamlRoot() : nullptr;
            if (!xamlRoot)
                return nullptr;
            menu.XamlRoot(xamlRoot);
        }

        return window;
    }

    /**
     * @brief Remove the focus visual `menu` draws on its first item the next time it opens from keyboard
     * @details Opening from keyboard gives the menu presenter keyboard focus, which it later hands to its first item, drawing a focus visual on it.
     * Downgrade it to pointer focus before that happens, which keeps arrow key navigation working but draws nothing
     */
    void removeFocus(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& menu)
    {
        m_openedRevoker = menu.Opened(winrt::auto_revoke, [this](winrt::Windows::Foundation::IInspectable const& sender, auto&&)
        {
            auto const focusedElement = winrt::Microsoft::UI::Xaml::Input::FocusManager::GetFocusedElement(
                sender.as<winrt::Microsoft::UI::Xaml::Controls::MenuFlyout>().XamlRoot()
            ).try_as<winrt::Microsoft::UI::Xaml::UIElement>();
            if (focusedElement && focusedElement.FocusState() == winrt::Microsoft::UI::Xaml::FocusState::Keyboard)
                focusedElement.Focus(winrt::Microsoft::UI::Xaml::FocusState::Pointer);
            m_openedRevoker.revoke();
        });
    }
};
