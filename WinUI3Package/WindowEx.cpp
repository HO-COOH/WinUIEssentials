#include "pch.h"
#include "WindowEx.h"
#if __has_include("WindowEx.g.cpp")
#include "WindowEx.g.cpp"
#endif
#include "HwndHelper.hpp"

#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Microsoft.UI.Input.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include "WindowsVersion.hpp"
#include <windowsx.h> //For GET_X_LPARAM and GET_Y_LPARAM

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#include <CommCtrl.h>
#pragma comment(lib, "Comctl32.lib")
#include <dwmapi.h>
#pragma comment (lib, "dwmapi.lib")
// Compiles with -lntdll
#include <winrt/Microsoft.UI.Content.h>


namespace winrt::WinUI3Package::implementation
{
    //std::unordered_map<HWND, std::unordered_set<void*>> WindowEx::s_allWindows;
	std::unordered_map<HWND, winrt::event_token> WindowEx::s_windowResizeRevokers;

    HWND WindowEx::getHwndFromElement(winrt::Microsoft::UI::Xaml::FrameworkElement const& element)
    {
        auto xamlRoot = element.XamlRoot();
        if (!xamlRoot)
            return {};

        auto contentIslandEnv = xamlRoot.ContentIslandEnvironment();
        if (!contentIslandEnv)
            return{};

        auto appWindowId = contentIslandEnv.AppWindowId();
        return reinterpret_cast<HWND>(appWindowId.Value);
    }

    winrt::Microsoft::UI::Windowing::AppWindow WindowEx::getAppWindowFromElement(winrt::Microsoft::UI::Xaml::FrameworkElement const& element)
    {
        return winrt::Microsoft::UI::Windowing::AppWindow::GetFromWindowId(winrt::Microsoft::UI::GetWindowIdFromWindow(getHwndFromElement(element)));
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::s_nonClientRegionKindProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
            L"NonClientRegionKind",
            winrt::xaml_typename<winrt::Microsoft::UI::Input::NonClientRegionKind>(),
            winrt::xaml_typename<class_type>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                winrt::box_value(false),
                [](winrt::Microsoft::UI::Xaml::DependencyObject const& d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
                {
                    auto newValue = e.NewValue();
                    if (!newValue)
                        return;

                    auto element = d.try_as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
                    if (!element)
                        return;

                    element.LayoutUpdated([weakRef = winrt::make_weak(element), refAdded = false, lastBounds = winrt::Windows::Foundation::Rect{}](auto const& sender, auto...) mutable
                    {
                        if (auto element = weakRef.get())
                        {
                            auto const hwnd = getHwndFromElement(element);
                            if (!hwnd || !element.IsLoaded())
                                return;

                            if (!refAdded)
                            {
                                s_allWindows[hwnd].push_back(winrt::make_weak(element));
                                auto elementRefIter = --s_allWindows[hwnd].end();
                               
                                element.Unloaded([hwnd, elementRefIter](auto&&...) {
                                    auto& thisWindow = s_allWindows.at(hwnd);
                                    thisWindow.erase(elementRefIter);
                                    if (thisWindow.empty())
                                        s_allWindows.erase(hwnd);
                                });

								refAdded = true;
                            }

                            auto transform = element.TransformToVisual(nullptr);
                            auto const newBounds = transform.TransformBounds(winrt::Windows::Foundation::Rect{
                                0.f,
                                0.f,
                                static_cast<float>(element.ActualWidth()),
                                static_cast<float>(element.ActualHeight())
                            });
                            if (newBounds == lastBounds)
                                return;

                            lastBounds = newBounds;
                            updateNonClientRegions(GetNonClientRegionKind(element), hwnd);
                        }
					});

                }
            }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::s_rootWindowProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
            L"RootWindow",
            winrt::xaml_typename<uint64_t>(),
            winrt::xaml_typename<class_type>(),
            nullptr
        );



    WindowEx::WindowEx() :
        m_hwnd{ GetHwnd(*this) },
        m_appWindow{ GetAppWindow(m_hwnd) },
        m_overlappedPresenter{ m_appWindow.Presenter().as<decltype(m_overlappedPresenter)>() },
        m_appWindowTitleBar{ m_appWindow.TitleBar() }
    {
        try
        {
            if (auto package = winrt::Windows::ApplicationModel::Package::Current())
                Title(package.DisplayName());
        }
        catch (...)
        {
        }
    }

    int WindowEx::MinWidth()
    {
        return m_minWidth.value_or();
    }
    void WindowEx::MinWidth(int value)
    {
        setSubClassIfNeeded();
        m_minWidth = value;
        m_setMinMax = true;
        clampWindowSize();
    }
    int WindowEx::MaxWidth()
    {
        return m_maxWidth.value_or();
    }
    void WindowEx::MaxWidth(int value)
    {
        setSubClassIfNeeded();
        m_maxWidth = value;
        m_setMinMax = true;
        clampWindowSize();
    }

    int WindowEx::MinHeight()
    {
        return m_minHeight.value_or();
    }
    void WindowEx::MinHeight(int value)
    {
        setSubClassIfNeeded();
        m_minHeight = value;
        m_setMinMax = true;
        clampWindowSize();
    }
    int WindowEx::MaxHeight()
    {
        return m_maxHeight.value_or();
    }
    void WindowEx::MaxHeight(int value)
    {
        setSubClassIfNeeded();
        m_maxHeight = value;
        m_setMinMax = true;
        clampWindowSize();
    }
    int WindowEx::Width()
    {
        return unscaleForDpi(RawWidth(), Dpi());
    }
    void WindowEx::Width(int value)
    {
        auto const dpi = Dpi();
        m_appWindow.Resize({
            scaleForDpi(std::clamp(value, MinWidth(), MaxWidth()), dpi),
            scaleForDpi(Height(), dpi)
            });
    }
    int WindowEx::Height()
    {
        return unscaleForDpi(RawHeight(), Dpi());
    }
    void WindowEx::Height(int value)
    {
        auto const dpi = Dpi();
        m_appWindow.Resize({
            scaleForDpi(Width(), dpi),
            scaleForDpi(std::clamp(value, MinHeight(), MaxHeight()), dpi)
            });
    }
    int WindowEx::RawWidth()
    {
        return m_appWindow.Size().Width;
    }
    void WindowEx::RawWidth(int value)
    {
        m_appWindow.Resize({ value, RawHeight() });
    }
    int WindowEx::RawHeight()
    {
        return m_appWindow.Size().Height;
    }
    void WindowEx::RawHeight(int value)
    {
        m_appWindow.Resize({ RawWidth(), value });
    }
    int WindowEx::LeftInset()
    {
        return LeftInsetRaw() * 96 / Dpi();
    }
    int WindowEx::LeftInsetRaw()
    {
        return m_appWindowTitleBar.LeftInset();
    }
    int WindowEx::RightInset()
    {
        return RightInsetRaw() * 96 / Dpi();
    }
    int WindowEx::RightInsetRaw()
    {
        return m_appWindowTitleBar.RightInset();
    }
    unsigned int WindowEx::Dpi()
    {
        return GetDpiForWindow(m_hwnd);
    }
    bool WindowEx::IsMinimizable()
    {
        return m_overlappedPresenter.IsMinimizable();
    }
    void WindowEx::IsMinimizable(bool value)
    {
        m_overlappedPresenter.IsMinimizable(value);
    }
    bool WindowEx::IsMaximizable()
    {
        return m_overlappedPresenter.IsMaximizable();
    }
    void WindowEx::IsMaximizable(bool value)
    {
        if (!value)
            setSubClassIfNeeded();
        m_overlappedPresenter.IsMaximizable(value);
    }
    bool WindowEx::IsResizable()
    {
        return m_overlappedPresenter.IsResizable();
    }
    void WindowEx::IsResizable(bool value)
    {
        m_overlappedPresenter.IsResizable(value);
    }
    bool WindowEx::IsAlwaysOnTop()
    {
        return m_overlappedPresenter.IsAlwaysOnTop();
    }
    void WindowEx::IsAlwaysOnTop(bool value)
    {
        m_overlappedPresenter.IsAlwaysOnTop(value);
    }
    bool WindowEx::IsShownInSwitcher()
    {
        return m_appWindow.IsShownInSwitchers();
    }
    void WindowEx::IsShownInSwitcher(bool value)
    {
        m_appWindow.IsShownInSwitchers(value);
    }
    bool WindowEx::HasBorder()
    {
        return m_titleBarBorderSetting.m_hasBorder.value_or(TitleBarAndBorderSetting::DefaultValue::HasBorder);
    }
    void WindowEx::HasBorder(bool value)
    {
        m_titleBarBorderSetting.m_hasBorder = value;
        
        auto hasTitleBarValue = HasTitleBar();
        if (!value && hasTitleBarValue)
            hasTitleBarValue = false;
        m_overlappedPresenter.SetBorderAndTitleBar(value, hasTitleBarValue);
    }
    bool WindowEx::HasTitleBar()
    {
        return m_titleBarBorderSetting.m_hasTitleBar.value_or(TitleBarAndBorderSetting::DefaultValue::HasTitleBar);
    }
    void WindowEx::HasTitleBar(bool value)
    {
        m_titleBarBorderSetting.m_hasTitleBar = value;
        auto hasBorderValue = HasBorder();
        if (value && !hasBorderValue)
            hasBorderValue = true;
        m_overlappedPresenter.SetBorderAndTitleBar(hasBorderValue, value);
    }
    bool WindowEx::TitleBarDarkMode()
    {
        return m_titleBarDarkMode;
    }
    void WindowEx::TitleBarDarkMode(bool value)
    {
        BOOL copy = value;
        DwmSetWindowAttribute(
            m_hwnd,
            GetWindowsVersion().dwBuildNumber >= 19041 ? 20 : 19,
            &copy,
            sizeof(copy)
        );
        if (extendsContentIntoTitleBar())
        {
            m_appWindowTitleBar.ButtonForegroundColor(value ?
                winrt::Windows::UI::Colors::White() :
                winrt::Windows::UI::Colors::Black()
            );
        }
        m_titleBarDarkMode = value;
    }
    bool WindowEx::TitleBarAutoDarkMode()
    {
        return m_titleBarAutoDarkMode;
    }
    void WindowEx::TitleBarAutoDarkMode(bool value)
    {
        if (value && !m_titleBarAutoDarkMode)
        {
            //subscribe
            setSubClassIfNeeded();
            TitleBarDarkMode(!isLightTheme());
        }
        m_titleBarAutoDarkMode = true;
    }

    winrt::hstring WindowEx::Icon()
    {
        return m_icon;
    }

    void WindowEx::Icon(winrt::hstring value)
    {
        m_appWindow.SetIcon(value);
        m_icon = value;
    }

    winrt::Microsoft::UI::Xaml::Controls::MenuFlyout WindowEx::ContextMenu()
    {
        return m_contextMenu;
    }

    void WindowEx::ContextMenu(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout value)
    {
		m_contextMenu = value;
        if (auto modernStandardMenu = m_contextMenu.try_as<WinUI3Package::ModernStandardWindowContextMenu>())
            modernStandardMenu.Window(*this);
    }

    winrt::Microsoft::UI::Windowing::AppWindow WindowEx::AppWindow()
    {
        return m_appWindow;
    }

    uint64_t WindowEx::Hwnd()
    {
        return reinterpret_cast<uint64_t>(m_hwnd);
    }


    void WindowEx::Transparent(bool value)
    {
        if (value)
        {
            setSubClassIfNeeded();
            MARGINS margin{};
            DwmExtendFrameIntoClientArea(m_hwnd, &margin);
        }
        m_transparent = value;
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::NonClientRegionKindProperty()
    {
        return s_nonClientRegionKindProperty;
    }

    void WindowEx::SetNonClientRegionKind(winrt::Microsoft::UI::Xaml::FrameworkElement const& element, winrt::Microsoft::UI::Input::NonClientRegionKind value)
    {
		element.SetValue(s_nonClientRegionKindProperty, winrt::box_value(value));
    }

    winrt::Microsoft::UI::Input::NonClientRegionKind WindowEx::GetNonClientRegionKind(winrt::Microsoft::UI::Xaml::FrameworkElement const& element)
    {
        return winrt::unbox_value<winrt::Microsoft::UI::Input::NonClientRegionKind>(element.GetValue(s_nonClientRegionKindProperty));
    }


    int WindowEx::scaleForDpi(int value, int dpi)
    {
        return value * dpi / 96;
    }

    int WindowEx::unscaleForDpi(int value, int dpi)
    {
        return value * 96 / dpi;
    }

    void WindowEx::setSubClassIfNeeded()
    {
        if (m_registered)
            return;


        if (SetWindowSubclass(m_hwnd, &subclassProc, SubClassId, reinterpret_cast<DWORD_PTR>(this)))
        {
            m_registered = true;
        }
    }

    LRESULT CALLBACK WindowEx::subclassProc(
        HWND hwnd,
        UINT msg,
        WPARAM wparam,
        LPARAM lparam,
        UINT_PTR uIdSubclass,
        DWORD_PTR dwRefData)
    {
        if (uIdSubclass != SubClassId)
            return DefSubclassProc(hwnd, msg, wparam, lparam);

        auto ptr = reinterpret_cast<WindowEx*>(dwRefData);
        switch (msg)
        {
            case WM_ERASEBKGND:
                if (ptr->clearBackground(hwnd, reinterpret_cast<HDC>(wparam)))
                    return 1;
                break;
            case WM_SETTINGCHANGE:
                ptr->onSettingChange();
                break;
            case WM_CONTEXTMENU:
            {
                if (ptr->m_contextMenu)
                {
                    if (!ptr->m_contextMenuHost)
                        ptr->m_contextMenuHost = {};
                    ptr->m_contextMenuHost.Move({ GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) });
				    ptr->m_contextMenu.ShowAt(ptr->m_contextMenuHost);
                    return 0;
                }
                break;
            }
            case WM_GETMINMAXINFO:
                return ptr->onGetMinMaxInfo(wparam, lparam);
            case WM_SYSCOMMAND:
                if (wparam == SC_MAXIMIZE && !ptr->m_overlappedPresenter.IsMaximizable())
                    return 1;
                break;
        }
        return DefSubclassProc(hwnd, msg, wparam, lparam);
    }

    LRESULT WindowEx::onGetMinMaxInfo(WPARAM, LPARAM pMinMaxInfo)
    {
        if (!m_setMinMax)
            return 1;

        auto pt = reinterpret_cast<MINMAXINFO*>(pMinMaxInfo);


        auto const dpi = Dpi();
        RECT const rect = getAdjustedWindowRect(m_hwnd, dpi);
        if (m_minWidth)
            pt->ptMinTrackSize.x = scaleForDpi(*m_minWidth, dpi) + rect.right - rect.left - 2;
        if (m_maxWidth)
            pt->ptMaxTrackSize.x = scaleForDpi(*m_maxWidth, dpi) + rect.right - rect.left - 2;
        if (m_minHeight)
            pt->ptMinTrackSize.y = scaleForDpi(*m_minHeight, dpi) + rect.right - 1;
        if (m_maxHeight)
            pt->ptMaxTrackSize.y = scaleForDpi(*m_maxHeight, dpi) + rect.right - 1;
        return 0;
    }

    bool WindowEx::isLightTheme()
    {
        HKEY key{};
        RegOpenKeyEx(HKEY_CURRENT_USER, LR"(Software\Microsoft\Windows\CurrentVersion\Themes\Personalize)", 0, KEY_READ, &key);
        DWORD value{};
        DWORD bytes = sizeof(value);
        auto hr = RegGetValue(key, nullptr, LR"(AppsUseLightTheme)", RRF_RT_DWORD, nullptr, &value, &bytes);
        return static_cast<bool>(value);
    }

    void WindowEx::onSettingChange()
    {
        if (m_titleBarAutoDarkMode || m_extendContents)
            TitleBarDarkMode(!isLightTheme());;
    }
    void WindowEx::clampWindowSize()
    {
        auto const [width, height] = m_appWindow.Size();

        auto const clampedWidth = std::clamp(width, MinWidth(), MaxWidth());
        auto const clampedHeight = std::clamp(height, MinHeight(), MaxHeight());
        if (width != clampedWidth || height != clampedHeight)
            m_appWindow.Resize({ .Width = clampedWidth, .Height = clampedHeight });
    }

    void WindowEx::updateNonClientRegions(winrt::Microsoft::UI::Input::NonClientRegionKind kind, HWND hwnd)
    {
        auto const scale = GetDpiForWindow(hwnd);
        std::vector<winrt::Windows::Graphics::RectInt32> rectArray;
        for (auto controlRef : s_allWindows.at(hwnd))
        {
            if (auto strongControl = controlRef.get())
            {
                if (auto const kindValue = GetNonClientRegionKind(strongControl); kindValue == kind)
                {
                    auto transform = strongControl.TransformToVisual(nullptr);
                    auto rect = transform.TransformBounds(winrt::Windows::Foundation::Rect{
                        0.f,
                        0.f,
                        static_cast<float>(strongControl.ActualWidth()),
                        static_cast<float>(strongControl.ActualHeight())
                    });
                    rectArray.push_back(scaleRect(rect, scale));
                }
			}
        }

        winrt::Microsoft::UI::Input::InputNonClientPointerSource::GetForWindowId(winrt::Microsoft::UI::GetWindowIdFromWindow(hwnd))
            .SetRegionRects(kind, rectArray);
    }

    void WindowEx::extendsContentIntoTitleBar(bool value)
    {
        if (value == m_extendContents)
            return;
        //register to change the caption button color
        setSubClassIfNeeded();
        ExtendsContentIntoTitleBar(value);
        m_extendContents = value;
    }

    bool WindowEx::extendsContentIntoTitleBar()
    {
        return m_extendContents;
    }

    bool WindowEx::clearBackground(HWND hwnd, HDC hdc)
    {
        RECT rect{};
        if (GetClientRect(hwnd, &rect))
        {
            auto brush = CreateSolidBrush({});
            FillRect(hdc, &rect, brush);
            return true;
        }
        return true;
    }


    RECT WindowEx::getAdjustedWindowRect(HWND hwnd, unsigned dpi)
    {
        RECT rect{};
        AdjustWindowRectExForDpi(&rect, GetWindowLongPtr(hwnd, GWL_STYLE), false, GetWindowLongPtr(hwnd, GWL_EXSTYLE), dpi);
        return rect;
    }
}
