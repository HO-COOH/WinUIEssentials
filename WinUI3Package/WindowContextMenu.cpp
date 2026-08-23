#include "pch.h"
#include "WindowContextMenu.h"
#if __has_include("WindowContextMenu.g.cpp")
#include "WindowContextMenu.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
    winrt::Microsoft::UI::Xaml::Controls::MenuFlyout WindowContextMenu::Menu()
    {
        return m_menu;
    }

    void WindowContextMenu::Menu(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& value)
    {
        m_menu = value;
    }

    LRESULT CALLBACK WindowContextMenu::subclassProc(
        HWND hwnd,
        UINT msg,
        WPARAM wparam,
        LPARAM lparam,
        UINT_PTR,
        DWORD_PTR dwRefData)
    {
        auto self = reinterpret_cast<WindowContextMenu*>(dwRefData);
        switch (msg)
        {
            case WM_CONTEXTMENU:
            case WM_NCRBUTTONDOWN:
            case WM_NCRBUTTONUP:
                //Without a menu there is nothing to replace the system menu with, so leave it alone
                if (self->showMenu(self->m_menu, lparam))
                    return 0;
                break;
            case WM_NCDESTROY:
                self->removeSubclassIfSet();
                break;
        }
        return DefSubclassProc(hwnd, msg, wparam, lparam);
    }
}
