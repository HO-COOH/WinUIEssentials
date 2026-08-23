#pragma once

#include "WindowContextMenu.g.h"
#include "WindowContextMenuBase.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct WindowContextMenu : 
        WindowContextMenuT<WindowContextMenu>,
        WindowContextMenuBase<WindowContextMenu, 0x22002>
    {
        winrt::Microsoft::UI::Xaml::Controls::MenuFlyout Menu();
        void Menu(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& value);

        static LRESULT CALLBACK subclassProc(
            HWND hwnd,
            UINT msg,
            WPARAM wparam,
            LPARAM lparam,
            UINT_PTR uIdSubclass,
            DWORD_PTR dwRefData
        );
    private:
        winrt::Microsoft::UI::Xaml::Controls::MenuFlyout m_menu{ nullptr };
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct WindowContextMenu : WindowContextMenuT<WindowContextMenu, implementation::WindowContextMenu>
    {
    };
}
