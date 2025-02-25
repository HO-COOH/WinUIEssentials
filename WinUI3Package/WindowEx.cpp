#include "pch.h"
#include "WindowEx.h"
#if __has_include("WindowEx.g.cpp")
#include "WindowEx.g.cpp"
#endif
#include "HwndHelper.hpp"
#include <winrt/Microsoft.UI.Interop.h>
#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Microsoft.UI.Input.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include "WindowsVersion.hpp"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#include <CommCtrl.h>
#pragma comment(lib, "Comctl32.lib")
#include <dwmapi.h>
#pragma comment (lib, "dwmapi.lib")
// Compiles with -lntdll




namespace winrt::WinUI3Package::implementation
{
    std::unordered_map<winrt::Microsoft::UI::Xaml::FrameworkElement, winrt::event_token> WindowEx::s_sizeChangeHandlers;
    std::unordered_map<HWND, winrt::weak_ref<WindowEx>> WindowEx::s_allWindows;

    winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::s_isInteractiveProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
            L"IsInteractive",
            winrt::xaml_typename<bool>(),
            winrt::xaml_typename<class_type>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                winrt::box_value(false),
                [](winrt::Microsoft::UI::Xaml::DependencyObject const& d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
                {
                    auto element = d.as<winrt::Microsoft::UI::Xaml::FrameworkElement>();

                    if (e.NewValue())
                    {
                        s_sizeChangeHandlers[element] = element.SizeChanged(
                            [](auto const& sender, auto...)
                            {
                                auto element = sender.as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
                                if (auto rootWindow = getRootWindow(element))
                                {
                                    rootWindow->updateDragRegion();
                                }
                            });
                        element.Unloaded([](auto const& sender, auto...)
                            {
                                auto element = sender.as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
                                s_sizeChangeHandlers.erase(element);
                            });
                    }
                    else
                    {
                        element.SizeChanged(s_sizeChangeHandlers[element]);
                        s_sizeChangeHandlers.erase(element);
                    }
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
        Title(winrt::Windows::ApplicationModel::Package::Current().DisplayName());
        std::hash<winrt::Microsoft::UI::Xaml::FrameworkElement> hasher;
        s_allWindows[m_hwnd] = get_weak();
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
        OSVERSIONINFOEXW version{};
        auto hr = RtlGetVersion(&version);
        BOOL copy = value;
        DwmSetWindowAttribute(
            m_hwnd,
            version.dwBuildNumber >= 19041 ? 20 : 19,
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

    winrt::Microsoft::UI::Xaml::UIElement WindowEx::TitleBar()
    {
        return nullptr;
    }

    void WindowEx::TitleBar(winrt::Microsoft::UI::Xaml::UIElement value)
    {
        if (!value)
            return;

        auto oldContent = Content();
        Content(nullptr);

        if (!rootGrid)
        {
            rootGrid = {};
            rootGrid.SetValue(s_rootWindowProperty, winrt::box_value(reinterpret_cast<uint64_t>(this)));
        }
        {
            winrt::Microsoft::UI::Xaml::Controls::Grid titleBarGrid;
            titleBarGrid.Children().Append(value);
            titleBarGrid.VerticalAlignment(winrt::Microsoft::UI::Xaml::VerticalAlignment::Top);
            titleBarGrid.SizeChanged([this](auto...) {updateDragRegion(); });

            rootGrid.Children().Append(titleBarGrid);
            rootGrid.Loaded([this](auto...) { rootGrid.UpdateLayout(); updateDragRegion(); });
            SetTitleBar(titleBarGrid);
            if (oldContent) rootGrid.Children().Append(oldContent);
        }

        extendsContentIntoTitleBar(true);
        TitleBarDarkMode(!isLightTheme());
        Content(rootGrid);
        SizeChanged([this](auto...) {updateDragRegion(); });
    }

    winrt::Microsoft::UI::Windowing::AppWindow WindowEx::AppWindow()
    {
        return m_appWindow;
    }

    uint64_t WindowEx::Hwnd()
    {
        return reinterpret_cast<uint64_t>(m_hwnd);
    }

    winrt::Microsoft::UI::Xaml::UIElement WindowEx::WindowContent()
    {
        if (!rootGrid)
            return Content();

        //TODO: 
        return nullptr;
    }

    void WindowEx::WindowContent(winrt::Microsoft::UI::Xaml::UIElement value)
    {
        if (!rootGrid)
        {
            Content(value);
            return;
        }

        rootGrid.Children().Append(value);
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

    void WindowEx::SetIsInteractive(winrt::Microsoft::UI::Xaml::Controls::Control element, bool value)
    {
        element.SetValue(s_isInteractiveProperty, winrt::box_value(value));
    }

    bool WindowEx::GetIsInteractive(winrt::Microsoft::UI::Xaml::Controls::Control element)
    {
        return winrt::unbox_value<bool>(element.GetValue(s_isInteractiveProperty));
    }

    winrt::weak_ref<WindowEx> WindowEx::GetByHwnd(HWND hwnd)
    {
        return s_allWindows[hwnd];
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
        case WM_GETMINMAXINFO:
            return ptr->onGetMinMaxInfo(wparam, lparam);
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

    winrt::Windows::Graphics::RectInt32 WindowEx::scaleRect(winrt::Windows::Foundation::Rect const& bound, double scale)
    {
        return winrt::Windows::Graphics::RectInt32{
            .X = static_cast<int>(bound.X * scale),
            .Y = static_cast<int>(bound.Y * scale),
            .Width = static_cast<int>(bound.Width * scale),
            .Height = static_cast<int>(bound.Height * scale)
        };
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
    void WindowEx::updateDragRegion()
    {
        auto const scale = Content().XamlRoot().RasterizationScale();
        std::vector<winrt::Windows::Graphics::RectInt32> rectArray;
        rectArray.reserve(s_sizeChangeHandlers.size());

        for (auto [element, _] : s_sizeChangeHandlers)
        {
            auto transform = element.TransformToVisual(rootGrid);
            auto rect = transform.TransformBounds(winrt::Windows::Foundation::Rect{
                0.f,
                0.f,
                static_cast<float>(element.ActualWidth()),
                static_cast<float>(element.ActualHeight())
                });
            rectArray.push_back(scaleRect(rect, scale));
        }


        auto nonClientInputSource = winrt::Microsoft::UI::Input::InputNonClientPointerSource::GetForWindowId(winrt::Microsoft::UI::GetWindowIdFromWindow(m_hwnd));
        nonClientInputSource.SetRegionRects(winrt::Microsoft::UI::Input::NonClientRegionKind::Passthrough, rectArray);
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

    WindowEx* WindowEx::getRootWindow(winrt::Microsoft::UI::Xaml::FrameworkElement& element)
    {
        auto currentParent = winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetParent(element);
        do
        {
            auto gridParent = currentParent.try_as<decltype(rootGrid)>();
            if (gridParent)
            {
                auto rootWindowProperty = gridParent.GetValue(s_rootWindowProperty);
                if (rootWindowProperty)
                {
                    auto rootWindowPtr = reinterpret_cast<WindowEx*>(winrt::unbox_value<uint64_t>(rootWindowProperty));
                    return rootWindowPtr;
                }
            }
            currentParent = winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetParent(currentParent);
        } while (currentParent);
        return nullptr;
    }
    RECT WindowEx::getAdjustedWindowRect(HWND hwnd, unsigned dpi)
    {
        RECT rect{};
        AdjustWindowRectExForDpi(&rect, GetWindowLongPtr(hwnd, GWL_STYLE), false, GetWindowLongPtr(hwnd, GWL_EXSTYLE), dpi);
        return rect;
    }
}
