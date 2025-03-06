#pragma once

#include "ModernStandardWindowContextMenu.g.h"
#include <winrt/Microsoft.UI.Content.h>

namespace winrt::WinUI3Package::implementation
{
    struct ModernStandardWindowContextMenu : ModernStandardWindowContextMenuT<ModernStandardWindowContextMenu>
    {
        ModernStandardWindowContextMenu() = default;

        winrt::Microsoft::UI::Xaml::Window Window();
        void Window(winrt::Microsoft::UI::Xaml::Window const& value);

        static LRESULT CALLBACK subclassProc(
            HWND hwnd,
            UINT msg,
            WPARAM wparam,
            LPARAM lparam,
            UINT_PTR uIdSubclass,
            DWORD_PTR dwRefData
        );

    private:
        winrt::Microsoft::UI::Xaml::Window m_xamlRoot{ nullptr };
        HWND m_parent{};
        winrt::Microsoft::UI::Content::ContentCoordinateConverter m_converter{ nullptr };
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
