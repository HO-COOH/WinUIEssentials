#pragma once

#include "WindowEx.g.h"
#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <unordered_map>

namespace winrt::WinUI3Package::implementation
{
    //Prevent order of setter causing invalid combination
    struct TitleBarAndBorderSetting
    {
        struct DefaultValue
        {
            constexpr static auto HasTitleBar = true;
            constexpr static auto HasBorder = true;
        };

        std::optional<bool> m_hasTitleBar;
        std::optional<bool> m_hasBorder;
    };
    struct WindowEx : WindowExT<WindowEx>
    {
        WindowEx();

#pragma region MinimumSize
        int MinWidth();
        void MinWidth(int value);

        int MaxWidth();
        void MaxWidth(int value);

        int MinHeight();
        void MinHeight(int value);

        int MaxHeight();
        void MaxHeight(int value);
#pragma endregion


#pragma region Size
        int Width();
        void Width(int value);

        int Height();
        void Height(int value);

        int RawWidth();
        void RawWidth(int value);

        int RawHeight();
        void RawHeight(int value);

        int LeftInset();
        int LeftInsetRaw();
        int RightInset();
        int RightInsetRaw();

        unsigned int Dpi();
#pragma endregion


#pragma region CaptionButton
        bool IsMinimizable();
        void IsMinimizable(bool value);

        bool IsMaximizable();
        void IsMaximizable(bool value);

        bool IsResizable();
        void IsResizable(bool value);

        bool IsAlwaysOnTop();
        void IsAlwaysOnTop(bool value);

        bool IsShownInSwitcher();
        void IsShownInSwitcher(bool value);
#pragma endregion


#pragma region Win32WindowStyle
        bool HasBorder();
        void HasBorder(bool value);

        bool HasTitleBar();
        void HasTitleBar(bool value);

        bool TitleBarDarkMode();
        void TitleBarDarkMode(bool value);

        bool TitleBarAutoDarkMode();
        void TitleBarAutoDarkMode(bool value);

        winrt::hstring Icon();
        void Icon(winrt::hstring value);
#pragma endregion

        winrt::Microsoft::UI::Xaml::UIElement TitleBar();
        void TitleBar(winrt::Microsoft::UI::Xaml::UIElement value);

        winrt::Microsoft::UI::Windowing::AppWindow AppWindow();
        uint64_t Hwnd();

        winrt::Microsoft::UI::Xaml::UIElement WindowContent();
        void WindowContent(winrt::Microsoft::UI::Xaml::UIElement value);

        /*For transparent backdrop*/
        void Transparent(bool value);

        static winrt::Microsoft::UI::Xaml::DependencyProperty IsInteractiveProperty() { return nullptr; }
        static void SetIsInteractive(winrt::Microsoft::UI::Xaml::Controls::Control element, bool value);
        static bool GetIsInteractive(winrt::Microsoft::UI::Xaml::Controls::Control element);

        static winrt::weak_ref<WindowEx> GetByHwnd(HWND hwnd);
    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_isInteractiveProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_rootWindowProperty;
        static std::unordered_map<HWND, winrt::weak_ref<WindowEx>> s_allWindows;

        template<typename T, T Sentinel>
        class Optional
        {
            T m_value = Sentinel;
        public:
            Optional& operator=(T value) { m_value = value; return *this; }
            T value_or(T value)
            {
                return m_value == Sentinel ? value : m_value;
            }
            T value_or()
            {
                return m_value;
            }

            constexpr operator bool()
            {
                return m_value != Sentinel;
            }

            constexpr bool has_value()
            {
                return (bool)*this;
            }

            T operator*() const
            {
                return m_value;
            }
        };

        bool m_titleBarDarkMode{};
        bool m_setMinMax{};
        bool m_titleBarAutoDarkMode{};
        bool m_registered{};
        bool m_extendContents{};
        bool m_transparent{};
        TitleBarAndBorderSetting m_titleBarBorderSetting;


        static int scaleForDpi(int value, int dpi);
        static int unscaleForDpi(int value, int dpi);


        Optional<int, -1> m_minWidth;
        Optional<int, -1> m_minHeight;
        Optional<int, INT_MAX> m_maxWidth;
        Optional<int, INT_MAX> m_maxHeight;
        HWND m_hwnd{};
        winrt::hstring m_icon;

        winrt::Microsoft::UI::Xaml::Controls::Grid rootGrid{ nullptr };


        winrt::Microsoft::UI::Windowing::AppWindow m_appWindow{ nullptr };
        winrt::Microsoft::UI::Windowing::OverlappedPresenter m_overlappedPresenter{ nullptr };
        winrt::Microsoft::UI::Windowing::AppWindowTitleBar m_appWindowTitleBar{ nullptr };


        constexpr static UINT SubClassId = 101;


        void setSubClassIfNeeded();

        static LRESULT subclassProc(
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
        void updateDragRegion();
        void extendsContentIntoTitleBar(bool value);
        bool extendsContentIntoTitleBar();
        bool clearBackground(HWND hwnd, HDC hdc);

        static bool isLightTheme();
        static winrt::Windows::Graphics::RectInt32 scaleRect(winrt::Windows::Foundation::Rect const& bound, double scale);
        static std::unordered_map<winrt::Microsoft::UI::Xaml::FrameworkElement, winrt::event_token> s_sizeChangeHandlers;

        static WindowEx* getRootWindow(winrt::Microsoft::UI::Xaml::FrameworkElement& element);

        static RECT getAdjustedWindowRect(HWND hwnd, unsigned dpi);

    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct WindowEx : WindowExT<WindowEx, implementation::WindowEx>
    {
    };
}
