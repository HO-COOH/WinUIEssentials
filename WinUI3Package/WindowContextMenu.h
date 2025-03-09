#pragma once

#include "WindowContextMenu.g.h"
#include "MenuFlyoutItemPaddingWorkaroundWrapper.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct WindowContextMenu : 
        WindowContextMenuT<WindowContextMenu>,
        private MenuFlyoutItemPaddingWorkaroundWrapper
    {
        WindowContextMenu() = default;

        winrt::Microsoft::UI::Xaml::Window Window();
        void Window(winrt::Microsoft::UI::Xaml::Window const& window);

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
        winrt::Microsoft::UI::Xaml::Window m_xamlRoot{ nullptr };
        HWND m_parent{};
        winrt::Microsoft::UI::Content::ContentCoordinateConverter m_converter{ nullptr };
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct WindowContextMenu : WindowContextMenuT<WindowContextMenu, implementation::WindowContextMenu>
    {
    };
}
