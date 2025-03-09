#include "pch.h"
#include "WindowContextMenu.h"
#if __has_include("WindowContextMenu.g.cpp")
#include "WindowContextMenu.g.cpp"
#endif
#include "HwndHelper.hpp"
#include <winrt/Microsoft.UI.Content.h>
#include <CommCtrl.h>
#include "WindowContextMenuUtils.h"

namespace winrt::WinUI3Package::implementation
{
    winrt::Microsoft::UI::Xaml::Window WindowContextMenu::Window()
    {
        return m_xamlRoot;
    }

    void WindowContextMenu::Window(winrt::Microsoft::UI::Xaml::Window const& value)
    {
        m_xamlRoot = value;
        m_converter = winrt::Microsoft::UI::Content::ContentCoordinateConverter::CreateForWindowId(value.AppWindow().Id());
        m_parent = GetHwnd(value);
        SetWindowSubclass(m_parent, &subclassProc, 0x22002, reinterpret_cast<DWORD_PTR>(this));
    }

    winrt::Microsoft::UI::Xaml::Controls::MenuFlyout WindowContextMenu::Menu()
    {
        return m_menu;
    }

    void WindowContextMenu::Menu(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& value)
    {
        m_menu = value;
    }

    LRESULT WindowContextMenu::subclassProc(
        HWND hwnd,
        UINT msg,
        WPARAM wparam,
        LPARAM lparam,
        UINT_PTR uIdSubclass,
        DWORD_PTR dwRefData)
    {
        switch (msg)
        {
            case WM_CONTEXTMENU:
            case WM_NCRBUTTONDOWN:
            case WM_NCRBUTTONUP:
            {
                auto self = reinterpret_cast<WindowContextMenu*>(dwRefData);
                auto wrapperBase = static_cast<MenuFlyoutItemPaddingWorkaroundWrapper*>(self);
                if (wrapperBase->IsFirstShow())
                    self->m_menu.XamlRoot(self->m_xamlRoot.Content().XamlRoot());
                wrapperBase->ShowAtImpl(
                    winrt::Microsoft::UI::Xaml::Controls::MenuFlyout{ self->Menu() },
                    nullptr,
                    WindowContextMenuUtils::GetFlyoutShowOptions(self->m_parent, lparam, self->m_converter)
                );
                return 0;
            }
            default:
                break;
        }
        return DefSubclassProc(hwnd, msg, wparam, lparam);
    }
}
