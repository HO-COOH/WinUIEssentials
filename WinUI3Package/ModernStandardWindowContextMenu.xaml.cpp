#include "pch.h"
#include "ModernStandardWindowContextMenu.xaml.h"
#if __has_include("ModernStandardWindowContextMenu.g.cpp")
#include "ModernStandardWindowContextMenu.g.cpp"
#endif
#include <CommCtrl.h>
#include "HwndHelper.hpp"
#include <winrt/Microsoft.UI.Windowing.h>
#include "WindowContextMenuUtils.h"
#include <wil/resource.h>
#include "WinUIEssentialError.hpp"

#undef IsMaximized


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Package::implementation
{
    ModernStandardWindowContextMenu::ModernStandardWindowContextMenu(winrt::Microsoft::UI::Xaml::Window const& value)
    {
        InitializeComponent();
        Window(value);
    }

    winrt::Microsoft::UI::Xaml::Window ModernStandardWindowContextMenu::Window()
    {
        return m_xamlRoot;
    }

    void ModernStandardWindowContextMenu::Window(winrt::Microsoft::UI::Xaml::Window const& value)
    {
		if (m_xamlRoot == value)
            return;

        m_xamlRoot = value;
        m_converter = winrt::Microsoft::UI::Content::ContentCoordinateConverter::CreateForWindowId(value.AppWindow().Id());
        m_parent = GetHwnd(value);
        
        //force refresh isMaximized
        m_isMaximized = !IsZoomed(m_parent);
		isMaximized(!m_isMaximized);

        // By default all MenuFlyoutItems are shown, so if the window is resizable (which is most likely)
        // we do not need to hide them
        auto const windowStyle = GetWindowLongPtr(m_parent, GWL_STYLE);
        if (!(windowStyle & WS_THICKFRAME))
            isResizable(false);

        //After getting the text from default system menu, we remove it from window
        setMenuItemText();
        SetWindowSubclass(m_parent, &subclassProc, 0x22001, reinterpret_cast<DWORD_PTR>(this));
    }

    LRESULT ModernStandardWindowContextMenu::subclassProc(
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
                auto self = reinterpret_cast<ModernStandardWindowContextMenu*>(dwRefData);
                auto wrapperBase = static_cast<MenuFlyoutItemPaddingWorkaroundWrapper*>(self);
                if (wrapperBase->IsFirstShow())
                    self->XamlRoot(self->m_xamlRoot.Content().XamlRoot());
                wrapperBase->ShowAtImpl(
                    winrt::Microsoft::UI::Xaml::Controls::MenuFlyout{ *self }, 
                    nullptr, 
                    WindowContextMenuUtils::GetFlyoutShowOptions(self->m_parent, lparam, self->m_converter)
                );
                return 0;
            }
            case WM_SIZE:
            {
				//handle menu state changes by detecting if the window is maximized
				auto ptr = reinterpret_cast<ModernStandardWindowContextMenu*>(dwRefData);
				ptr->isMaximized(wparam == SIZE_MAXIMIZED);
                break;
            }
            case WM_STYLECHANGED:
            {
				if (auto ptr = reinterpret_cast<ModernStandardWindowContextMenu*>(dwRefData); wparam == GWL_STYLE)
				{
					auto const style = reinterpret_cast<STYLESTRUCT*>(lparam);
					ptr->isResizable(style->styleNew & WS_THICKFRAME);
				}
				break;
            }
        }
        return DefSubclassProc(hwnd, msg, wparam, lparam);
    }

    void ModernStandardWindowContextMenu::setMenuItemText()
    {
        wil::unique_hmenu systemMenu{ GetSystemMenu(m_parent, false) };
        auto const systemMenuItemCount = GetMenuItemCount(systemMenu.get());
        
        std::vector<MENUITEMINFOW> items;
        for (int i = 0; i < systemMenuItemCount; ++i)
        {
            MENUITEMINFOW item{ .cbSize = sizeof(item), .fMask = MIIM_BITMAP | MIIM_FTYPE };
            winrt::check_bool(GetMenuItemInfoW(systemMenu.get(), i, true, &item));
            items.push_back(item);
        }

        if (systemMenuItemCount >= nonResizableWindowContextMenuItemCount)
        {
            //restore
            //close
            RestoreItem().Text(getMenuItemText(systemMenu.get(), 0).data());
            auto closeItemTextOriginal = getMenuItemText(systemMenu.get(), systemMenuItemCount - 1); //last item should be close
            std::wstring_view view{ closeItemTextOriginal.data() };
            auto const index = view.find(L'\t') + 1;
            closeItemTextOriginal[index] = {};
            CloseItem().Text(view.substr(0, index));
        }
        else
        {
            //less than 2 items? How is it possible
            throw WinUIEssentialError<winrt::hresult_invalid_argument>
            {
                L"Invalid number of window context menu item."
                L"A valid window context menu should at least contain 2 items (non-resizable window)."
                L"And they most like should only contain 2 (non-resizable window) / 5 (standard window) items."
                L"This might be a bug of WinUIEssential. Please report!"
            };
        }

        if (systemMenuItemCount >= standardWindowContextMenuItemCount)
        {
            //move
            //size
            //minimize
			//maximize
            MoveItem().Text(getMenuItemText(systemMenu.get(), 1).data());
            SizeItem().Text(getMenuItemText(systemMenu.get(), 2).data());
            MinimizeItem().Text(getMenuItemText(systemMenu.get(), 3).data());
            MaximizeItem().Text(getMenuItemText(systemMenu.get(), 4).data());
        }
        
		if (systemMenuItemCount > standardWindowContextMenuItemCount)
			addAdditionalItems(systemMenu.get(), systemMenuItemCount);
    }

    std::array<wchar_t, 64> ModernStandardWindowContextMenu::getMenuItemText(HMENU hMenu, UINT item)
    {
        std::array<wchar_t, 64> ret{};
        wchar_t buf[64]{};
        winrt::check_hresult(GetMenuString(hMenu, item, buf, std::size(buf), MF_BYPOSITION));
        std::copy_if(std::begin(buf), std::end(buf), std::begin(ret), [](wchar_t c) {return c != L'&'; });
        return ret;
    }

    void ModernStandardWindowContextMenu::isMaximized(bool value)
	{
        if (m_isMaximized != value)
        {
            m_isMaximized = value;
            RestoreItem().IsEnabled(value);
            SizeItem().IsEnabled(!value);
            MaximizeItem().IsEnabled(!value);
        }
	}

    void ModernStandardWindowContextMenu::isResizable(bool value)
    {
        auto const visibility = value ? 
            winrt::Microsoft::UI::Xaml::Visibility::Visible : 
            winrt::Microsoft::UI::Xaml::Visibility::Collapsed;
        RestoreItem().Visibility(visibility);
		SizeItem().Visibility(visibility);
		MaximizeItem().Visibility(visibility);
		MinimizeItem().Visibility(visibility);
        Separator().Visibility(visibility);
    }

    void ModernStandardWindowContextMenu::addAdditionalItems(HMENU hMenu, int itemsCount)
    {
        auto items = Items();
        //there are more than 7 items in system menu, append them before "Close"
        for (int i = standardWindowContextMenuItemCount - 1; i < itemsCount - 1; ++i)
        {
            auto text = getMenuItemText(hMenu, i);
            winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItem item;
            item.Text(text.data());
            items.InsertAt(items.Size() - 1, item);
        }
    }

    void ModernStandardWindowContextMenu::RestoreItem_Click(
        winrt::Windows::Foundation::IInspectable const&, 
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
		SendMessage(m_parent, WM_SYSCOMMAND, SC_RESTORE, 0);
    }


    void ModernStandardWindowContextMenu::MoveItem_Click(
	winrt::Windows::Foundation::IInspectable const&,
	winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
	    Hide();
	    SendMessage(m_parent, WM_SYSCOMMAND, SC_MOVE, 0);
    }

    void ModernStandardWindowContextMenu::SizeItem_Click(
		winrt::Windows::Foundation::IInspectable const&,
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
	    Hide();
	    SendMessage(m_parent, WM_SYSCOMMAND, SC_SIZE, 0);
    }

    void ModernStandardWindowContextMenu::MinimizeItem_Click(
        winrt::Windows::Foundation::IInspectable const&, 
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        //This is necessary to workaround https://github.com/microsoft/microsoft-ui-xaml/issues/11068
        Hide();
		SendMessage(m_parent, WM_SYSCOMMAND, SC_MINIMIZE, 0);
    }

    void ModernStandardWindowContextMenu::MaximizeItem_Click(
        winrt::Windows::Foundation::IInspectable const&, 
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
		SendMessage(m_parent, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    }

    void ModernStandardWindowContextMenu::CloseItem_Click(
        winrt::Windows::Foundation::IInspectable const&, 
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
		SendMessage(m_parent, WM_SYSCOMMAND, SC_CLOSE, 0);
    }
}

