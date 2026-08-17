#pragma once

#include "WindowEx.g.h"
#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <unordered_map>
#include "TransparentMenuFlyoutHost.h"
#include <winrt/Microsoft.UI.Interop.h>
#include "include/EnsureDependencyProperty.hpp"
#include "include/PropertyChangeHelper.hpp"
#include <HwndHelper.hpp>

#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max
#include <tiny/optional.h>
#pragma pop_macro("max")
#pragma pop_macro("min")

namespace winrt::WinUI3Package::implementation
{
    struct WindowEx : WindowExT<WindowEx>, EnsureDependencyProperty<WindowEx>, MvvmHelper::PropertyChangeHelper<WindowEx>
    {
        WindowEx();
        ~WindowEx();

        static void EnsureDependencyProperties();

        winrt::Microsoft::UI::Xaml::Window Window();


#pragma region WindowForwarding
        winrt::hstring Title();
        void Title(winrt::hstring const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty TitleProperty();

        bool ExtendsContentIntoTitleBar();
        void ExtendsContentIntoTitleBar(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ExtendsContentIntoTitleBarProperty();

        winrt::Microsoft::UI::Xaml::Media::SystemBackdrop SystemBackdrop();
        void SystemBackdrop(winrt::Microsoft::UI::Xaml::Media::SystemBackdrop const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty SystemBackdropProperty();

        void Activate();
        void Close();
        void SetTitleBar(winrt::Microsoft::UI::Xaml::UIElement const& titleBar);

        winrt::event_token Activated(winrt::Windows::Foundation::TypedEventHandler<
            winrt::Windows::Foundation::IInspectable,
            winrt::Microsoft::UI::Xaml::WindowActivatedEventArgs> const& handler);
        void Activated(winrt::event_token const& token);

        winrt::event_token Closed(winrt::Windows::Foundation::TypedEventHandler<
            winrt::Windows::Foundation::IInspectable,
            winrt::Microsoft::UI::Xaml::WindowEventArgs> const& handler);
        void Closed(winrt::event_token const& token);

        winrt::event_token VisibilityChanged(winrt::Windows::Foundation::TypedEventHandler<
            winrt::Windows::Foundation::IInspectable,
            winrt::Microsoft::UI::Xaml::WindowVisibilityChangedEventArgs> const& handler);
        void VisibilityChanged(winrt::event_token const& token);
#pragma endregion


#pragma region Size
        /*
            Width / Height / MinWidth / MaxWidth / MinHeight / MaxHeight come from FrameworkElement
        */
        int RawWidth();
        int RawHeight();

        int LeftInset();
        int LeftInsetRaw();
        int RightInset();
        int RightInsetRaw();

        unsigned int Dpi();

        /*Width/Height are the whole window, only the client area is ours to lay out in*/
        winrt::Windows::Foundation::Size MeasureOverride(winrt::Windows::Foundation::Size availableSize);
        winrt::Windows::Foundation::Size ArrangeOverride(winrt::Windows::Foundation::Size finalSize);
#pragma endregion


#pragma region CaptionButton
        bool IsMinimizable();
        void IsMinimizable(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty IsMinimizableProperty();

        bool IsMaximizable();
        void IsMaximizable(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty IsMaximizableProperty();

        bool IsResizable();
        void IsResizable(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty IsResizableProperty();

        bool IsAlwaysOnTop();
        void IsAlwaysOnTop(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty IsAlwaysOnTopProperty();

        bool IsShownInSwitcher();
        void IsShownInSwitcher(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty IsShownInSwitcherProperty();
#pragma endregion


#pragma region Win32WindowStyle
        bool HasBorder();
        void HasBorder(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty HasBorderProperty();

        bool HasTitleBar();
        void HasTitleBar(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty HasTitleBarProperty();

        bool TitleBarDarkMode();
        void TitleBarDarkMode(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty TitleBarDarkModeProperty();

        bool TitleBarAutoDarkMode();
        void TitleBarAutoDarkMode(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty TitleBarAutoDarkModeProperty();

        winrt::hstring Icon();
        void Icon(winrt::hstring const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty IconProperty();

        winrt::Microsoft::UI::Xaml::Controls::MenuFlyout ContextMenu();
        void ContextMenu(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ContextMenuProperty();
#pragma endregion

        winrt::Microsoft::UI::Windowing::AppWindow AppWindow();
        uint64_t Hwnd();

        /*For transparent backdrop*/
        void Transparent(bool value);


        static winrt::Microsoft::UI::Xaml::DependencyProperty NonClientRegionKindProperty();
        static void SetNonClientRegionKind(winrt::Microsoft::UI::Xaml::FrameworkElement const& element, winrt::Microsoft::UI::Input::NonClientRegionKind value);
        static winrt::Microsoft::UI::Input::NonClientRegionKind GetNonClientRegionKind(winrt::Microsoft::UI::Xaml::FrameworkElement const& element);

        constexpr static winrt::Windows::Graphics::RectInt32 scaleRect(winrt::Windows::Foundation::Rect const& bound, double scale)
        {
            scale /= 96.0;
            return winrt::Windows::Graphics::RectInt32{
                .X = static_cast<int>(bound.X * scale),
                .Y = static_cast<int>(bound.Y * scale),
                .Width = static_cast<int>(bound.Width * scale),
                .Height = static_cast<int>(bound.Height * scale)
            };
        }

    private:
        winrt::Microsoft::UI::Xaml::Window m_window;
        HWND m_hwnd = GetHwnd(m_window);
        winrt::Microsoft::UI::Windowing::AppWindow m_appWindow = m_window.AppWindow();
        winrt::Microsoft::UI::Windowing::OverlappedPresenter m_overlappedPresenter = m_appWindow.Presenter().as<decltype(m_overlappedPresenter)>();
        winrt::Microsoft::UI::Windowing::AppWindowTitleBar m_appWindowTitleBar = m_appWindow.TitleBar();

        static winrt::Microsoft::UI::Xaml::DependencyProperty s_titleProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_extendsContentIntoTitleBarProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_systemBackdropProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_isMinimizableProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_isMaximizableProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_isResizableProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_isAlwaysOnTopProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_isShownInSwitcherProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_hasBorderProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_hasTitleBarProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_titleBarDarkModeProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_titleBarAutoDarkModeProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_iconProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_contextMenuProperty;

        static winrt::Microsoft::UI::Xaml::DependencyProperty s_nonClientRegionKindProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_rootWindowProperty;
        static inline std::unordered_map<HWND, std::list<winrt::weak_ref<winrt::Microsoft::UI::Xaml::FrameworkElement>>> s_allWindows;
        static std::unordered_map<HWND, winrt::event_token> s_windowResizeRevokers;
        bool m_setMinMax{};
        bool m_registered{};
        bool m_transparent{};
        /*Set while we are pushing the live window size into Width/Height, so the
          property changed handlers don't resize the window right back*/
        bool m_syncingSizeFromWindow{};
        bool m_attachedToWindow{};
        /*Nothing may hand out a reference to us before the constructor returned*/
        bool m_constructed{};

        /*Both sources can outlive us, and both handlers hold us raw, so revoke by hand*/
        winrt::event_token m_appWindowChangedToken{};
        winrt::Microsoft::UI::Xaml::Window::Closed_revoker m_windowClosedToken{};




        static int scaleForDpi(int value, int dpi);
        static int unscaleForDpi(int value, int dpi);

        tiny::optional<int, -1> m_minWidth;
        tiny::optional<int, -1> m_minHeight;
        tiny::optional<int, -1> m_maxWidth;
        tiny::optional<int, -1> m_maxHeight;
  
        HBRUSH m_backgroundBlackBrush = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));

        TransparentMenuFlyoutHost m_contextMenuHost{ nullptr };



        constexpr static UINT SubClassId = 101;


        void setSubClassIfNeeded();

        static LRESULT CALLBACK subclassProc(
            HWND hwnd,
            UINT msg,
            WPARAM wparam,
            LPARAM lparam,
            UINT_PTR uIdSubclass,
            DWORD_PTR dwRefData
        );

        LRESULT onGetMinMaxInfo(WPARAM, LPARAM pMinMaxInfo);
        void onSettingChange();
        void clampWindowSize();
        static void updateNonClientRegions(winrt::Microsoft::UI::Input::NonClientRegionKind kind, HWND hwnd);
        bool clearBackground(HWND hwnd, HDC hdc);

        static bool isLightTheme();

        static HWND getHwndFromElement(winrt::Microsoft::UI::Xaml::FrameworkElement const& element);
        static winrt::Microsoft::UI::Windowing::AppWindow getAppWindowFromElement(winrt::Microsoft::UI::Xaml::FrameworkElement const& element);

#pragma region PropertyChangedHandlers
        static void onTitleChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
        static void onExtendsContentIntoTitleBarChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
        static void onSystemBackdropChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
        static void onIsMinimizableChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
        static void onIsMaximizableChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
        static void onIsResizableChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
        static void onIsAlwaysOnTopChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
        static void onIsShownInSwitcherChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
        static void onHasBorderChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
        static void onHasTitleBarChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
        static void onTitleBarDarkModeChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
        static void onTitleBarAutoDarkModeChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
        static void onIconChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
        static void onContextMenuChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
        static void onNonClientRegionKindChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);

        void onFrameworkWidthChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& sender,
            winrt::Microsoft::UI::Xaml::DependencyProperty const& property);
        void onFrameworkHeightChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& sender,
            winrt::Microsoft::UI::Xaml::DependencyProperty const& property);
        void onFrameworkMinWidthChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& sender,
            winrt::Microsoft::UI::Xaml::DependencyProperty const& property);
        void onFrameworkMaxWidthChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& sender,
            winrt::Microsoft::UI::Xaml::DependencyProperty const& property);
        void onFrameworkMinHeightChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& sender,
            winrt::Microsoft::UI::Xaml::DependencyProperty const& property);
        void onFrameworkMaxHeightChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& sender,
            winrt::Microsoft::UI::Xaml::DependencyProperty const& property);

        void onAppWindowChanged(
            winrt::Microsoft::UI::Windowing::AppWindow const& sender,
            winrt::Microsoft::UI::Windowing::AppWindowChangedEventArgs const& args);

        void onContentChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& sender,
            winrt::Microsoft::UI::Xaml::DependencyProperty const& property);
#pragma endregion

        /*The window rect, i.e. the size Spy++ reports, in physical pixels*/
        winrt::Windows::Graphics::SizeInt32 windowSizeInPixels();
        void resizeWindowInPixels(int widthInPixels, int heightInPixels);

        /*The same rect in DIPs, the FrameworkElement Width/Height may well be NaN*/
        int currentWidth();
        int currentHeight();
        void resizeWindow(int widthInDips, int heightInDips);

        /*The window rect minus whatever the current window styles take*/
        winrt::Windows::Foundation::Size clientSizeInDips();
        winrt::Windows::Foundation::Size layoutSize(winrt::Windows::Foundation::Size const& availableSize);
        void addFrameworkPropertyCallbacks();
        void syncWindowStateToProperties();
        void revokeAppWindowChanged() noexcept;

        /*Makes the window show us, once we are allowed to hand out a reference to ourselves*/
        void attachToWindow();
        /*Everything that can put the window on screen goes through here*/
        void prepareToShow();
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct WindowEx : WindowExT<WindowEx, implementation::WindowEx>
    {
    };
}
