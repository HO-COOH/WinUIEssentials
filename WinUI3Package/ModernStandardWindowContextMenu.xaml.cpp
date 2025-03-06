#include "pch.h"
#include "ModernStandardWindowContextMenu.xaml.h"
#if __has_include("ModernStandardWindowContextMenu.g.cpp")
#include "ModernStandardWindowContextMenu.g.cpp"
#endif
#include <CommCtrl.h>
#include "HwndHelper.hpp"
#include <winrt/Microsoft.UI.Windowing.h>
#include <windowsx.h>
using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Package::implementation
{
    winrt::Microsoft::UI::Xaml::Window ModernStandardWindowContextMenu::Window()
    {
        return winrt::Microsoft::UI::Xaml::Window();
    }
    void ModernStandardWindowContextMenu::Window(winrt::Microsoft::UI::Xaml::Window const& value)
    {
        m_xamlRoot = value;
        m_converter = winrt::Microsoft::UI::Content::ContentCoordinateConverter::CreateForWindowId(value.AppWindow().Id());
        m_parent = GetHwnd(value);
        SetWindowSubclass(m_parent, &subclassProc, 0x22001, reinterpret_cast<DWORD_PTR>(this));
    }
    LRESULT ModernStandardWindowContextMenu::subclassProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
    {
        if (msg == WM_CONTEXTMENU || msg == WM_NCRBUTTONDOWN)
        {
            auto ptr = reinterpret_cast<ModernStandardWindowContextMenu*>(dwRefData);
            winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutShowOptions options;
            options.ShowMode(winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutShowMode::Standard);
            winrt::Windows::Graphics::PointInt32 screenPoint{ static_cast<int>(GET_X_LPARAM(lparam)),  static_cast<int>(GET_Y_LPARAM(lparam)) };
            auto localPoint = ptr->m_converter.ConvertScreenToLocal(screenPoint);
            auto const dpiScale = GetDpiForWindow(ptr->m_parent) / 96.0f;
            options.Position(winrt::Windows::Foundation::Point{ localPoint.X / dpiScale,  localPoint.Y / dpiScale });
			ptr->XamlRoot(ptr->m_xamlRoot.Content().XamlRoot());
			ptr->operator winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase().ShowAt(nullptr, options);
			//ptr->ShowAt(nullptr, options);

            return 0;
        }
        return DefSubclassProc(hwnd, msg, wparam, lparam);
    }


    void ModernStandardWindowContextMenu::RestoreItem_Click(
        winrt::Windows::Foundation::IInspectable const&, 
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
		SendMessage(m_parent, WM_SYSCOMMAND, SC_RESTORE, 0);
    }


    void ModernStandardWindowContextMenu::MoveItem_Click(
        winrt::Windows::Foundation::IInspectable const& sender, 
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
		SendMessage(m_parent, WM_SYSCOMMAND, SC_MOVE, 0);
    }

    void ModernStandardWindowContextMenu::SizeItem_Click(
        winrt::Windows::Foundation::IInspectable const& sender, 
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
		SendMessage(m_parent, WM_SYSCOMMAND, SC_SIZE, 0);
    }

    void ModernStandardWindowContextMenu::MinimizeItem_Click(
        winrt::Windows::Foundation::IInspectable const& sender, 
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
		SendMessage(m_parent, WM_SYSCOMMAND, SC_MINIMIZE, 0);
    }

    void ModernStandardWindowContextMenu::MaximizeItem_Click(
        winrt::Windows::Foundation::IInspectable const& sender, 
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
		SendMessage(m_parent, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    }

    void ModernStandardWindowContextMenu::CloseItem_Click(
        winrt::Windows::Foundation::IInspectable const& sender, 
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
		SendMessage(m_parent, WM_SYSCOMMAND, SC_CLOSE, 0);
    }
}

