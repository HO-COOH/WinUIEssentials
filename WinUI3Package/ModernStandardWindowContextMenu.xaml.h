#pragma once

#include "ModernStandardWindowContextMenu.g.h"
#include <winrt/Microsoft.UI.Content.h>
#include "MenuFlyoutItemPaddingWorkaroundWrapper.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct ModernStandardWindowContextMenu : 
        ModernStandardWindowContextMenuT<ModernStandardWindowContextMenu>,
        private MenuFlyoutItemPaddingWorkaroundWrapper
    {
        ModernStandardWindowContextMenu() = default;

        winrt::Microsoft::UI::Xaml::Window Window();
        void Window(winrt::Microsoft::UI::Xaml::Window const& value);

    private:
        static LRESULT CALLBACK subclassProc(
            HWND hwnd,
            UINT msg,
            WPARAM wparam,
            LPARAM lparam,
            UINT_PTR uIdSubclass,
            DWORD_PTR dwRefData
        );

        winrt::Microsoft::UI::Xaml::Window m_xamlRoot{ nullptr };
        HWND m_parent{};
        winrt::Microsoft::UI::Content::ContentCoordinateConverter m_converter{ nullptr };

        //{x:Bind} is not supported in this class, we need to set UI in code-behind!
        void setMenuItemText();
        static std::array<wchar_t, 64> getMenuItemText(HMENU hMenu, UINT item);
        
		//internal use only, set `MenuFlyoutItem` status when the value changes
        void isMaximized(bool value);

        //`WM_SIZE` is called very frequently, we cache the value to avoid frequent settings to items state
        bool m_isMaximized{};

        //isResizable only changes when `WM_STYLECHANGED`, which does not happens frequently, so we don't cache them
        void isResizable(bool value);
    public:
        void RestoreItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void MoveItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void SizeItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void MinimizeItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void MaximizeItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CloseItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct ModernStandardWindowContextMenu : ModernStandardWindowContextMenuT<ModernStandardWindowContextMenu, implementation::ModernStandardWindowContextMenu>
    {
    };
}
