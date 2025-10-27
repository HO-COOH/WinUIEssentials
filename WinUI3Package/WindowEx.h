#pragma once

#include "WindowEx.g.h"
#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <unordered_map>
#include <unordered_set>
#include "TransparentMenuFlyoutHost.h"
#include <winrt/Microsoft.UI.Interop.h>

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

        winrt::Microsoft::UI::Xaml::Controls::MenuFlyout ContextMenu();
        void ContextMenu(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout value);
#pragma endregion

        winrt::Microsoft::UI::Windowing::AppWindow AppWindow();
        uint64_t Hwnd();

        winrt::Microsoft::UI::Xaml::UIElement WindowContent();
        void WindowContent(winrt::Microsoft::UI::Xaml::UIElement value);

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
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_nonClientRegionKindProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_rootWindowProperty;
        static inline std::unordered_map<HWND, std::list<winrt::weak_ref<winrt::Microsoft::UI::Xaml::FrameworkElement>>> s_allWindows;
        static std::unordered_map<HWND, winrt::event_token> s_windowResizeRevokers;
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

        winrt::Microsoft::UI::Xaml::Controls::MenuFlyout m_contextMenu{ nullptr };
        TransparentMenuFlyoutHost m_contextMenuHost{ nullptr };

        winrt::Microsoft::UI::Windowing::AppWindow m_appWindow{ nullptr };
        winrt::Microsoft::UI::Windowing::OverlappedPresenter m_overlappedPresenter{ nullptr };
        winrt::Microsoft::UI::Windowing::AppWindowTitleBar m_appWindowTitleBar{ nullptr };


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
        void extendsContentIntoTitleBar(bool value);
        bool extendsContentIntoTitleBar();
        bool clearBackground(HWND hwnd, HDC hdc);

        static bool isLightTheme();
        static RECT getAdjustedWindowRect(HWND hwnd, unsigned dpi);

        static HWND getHwndFromElement(winrt::Microsoft::UI::Xaml::FrameworkElement const& element);
        static winrt::Microsoft::UI::Windowing::AppWindow getAppWindowFromElement(winrt::Microsoft::UI::Xaml::FrameworkElement const& element);
    };

    template<typename Container>
    struct InputNonClientPointerSourceSet
    {
        using RectType = winrt::Windows::Graphics::RectInt32;
        std::vector<RectType> close;
        std::vector<RectType> maximize;
        std::vector<RectType> minimize;
        std::vector<RectType> icon;
        std::vector<RectType> caption;
        std::vector<RectType> topBorder;
        std::vector<RectType> leftBorder;
        std::vector<RectType> bottomBorder;
        std::vector<RectType> rightBorder;
        std::vector<RectType> passthrough;

        winrt::Microsoft::UI::Input::InputNonClientPointerSource m_source;
    public:
        InputNonClientPointerSourceSet(Container& elementContainer, HWND hwnd)
            : m_source{ winrt::Microsoft::UI::Input::InputNonClientPointerSource::GetForWindowId(winrt::Microsoft::UI::GetWindowIdFromWindow(hwnd)) }
        {
            winrt::Microsoft::UI::Xaml::UIElement rootElement{ nullptr };
            for (auto& element : elementContainer)
            {
                if (!rootElement)
                    rootElement = element.XamlRoot().Content();

                auto const dpi = GetDpiForWindow(hwnd);
                auto transformedBounds = WindowEx::scaleRect(element.TransformToVisual(rootElement).TransformBounds(
                    winrt::Windows::Foundation::Rect
                    {
                        winrt::Windows::Foundation::Point{0, 0},
                        winrt::Windows::Foundation::Size
                        {
                            static_cast<float>(WindowEx::element.ActualWidth()),
                            static_cast<float>(WindowEx::element.ActualHeight())
                        }
                    }
                ));

                switch (WindowEx::GetNonClientRegionKind(element))
                {
                    case winrt::Microsoft::UI::Input::NonClientRegionKind::Close:
                        close.push_back(transformedBounds);
                        break;
                    case winrt::Microsoft::UI::Input::NonClientRegionKind::Maximize:
                        maximize.push_back(transformedBounds);
                        break;
                    case winrt::Microsoft::UI::Input::NonClientRegionKind::Minimize:
                        minimize.push_back(transformedBounds);
                        break;
                    case winrt::Microsoft::UI::Input::NonClientRegionKind::Icon:
                        icon.push_back(transformedBounds);
                        break;
                    case winrt::Microsoft::UI::Input::NonClientRegionKind::Caption:
                        caption.push_back(transformedBounds);
                        break;
                    case winrt::Microsoft::UI::Input::NonClientRegionKind::TopBorder:
                        topBorder.push_back(transformedBounds);
                        break;
                    case winrt::Microsoft::UI::Input::NonClientRegionKind::LeftBorder:
                        leftBorder.push_back(transformedBounds);
                        break;
                    case winrt::Microsoft::UI::Input::NonClientRegionKind::BottomBorder:
                        bottomBorder.push_back(transformedBounds);
                        break;
                    case winrt::Microsoft::UI::Input::NonClientRegionKind::RightBorder:
                        rightBorder.push_back(transformedBounds);
                        break;
                    case winrt::Microsoft::UI::Input::NonClientRegionKind::Passthrough:
                        passthrough.push_back(transformedBounds);
                        break;
                }
            }
        }

        void Apply()
        {
            if (!close.empty())
                m_source.SetRegionRects(winrt::Microsoft::UI::Input::NonClientRegionKind::Close, close);

            if (!maximize.empty())
                m_source.SetRegionRects(winrt::Microsoft::UI::Input::NonClientRegionKind::Maximize, maximize);

            if (!minimize.empty())
                m_source.SetRegionRects(winrt::Microsoft::UI::Input::NonClientRegionKind::Minimize, minimize);

            if (!icon.empty())
                m_source.SetRegionRects(winrt::Microsoft::UI::Input::NonClientRegionKind::Icon, icon);

            if (!caption.empty())
                m_source.SetRegionRects(winrt::Microsoft::UI::Input::NonClientRegionKind::Caption, caption);

            if (!topBorder.empty())
                m_source.SetRegionRects(winrt::Microsoft::UI::Input::NonClientRegionKind::TopBorder, topBorder);

            if (!leftBorder.empty())
                m_source.SetRegionRects(winrt::Microsoft::UI::Input::NonClientRegionKind::LeftBorder, leftBorder);

            if (!bottomBorder.empty())
                m_source.SetRegionRects(winrt::Microsoft::UI::Input::NonClientRegionKind::BottomBorder, bottomBorder);

            if (!rightBorder.empty())
                m_source.SetRegionRects(winrt::Microsoft::UI::Input::NonClientRegionKind::RightBorder, rightBorder);

            if (!passthrough.empty())
                m_source.SetRegionRects(winrt::Microsoft::UI::Input::NonClientRegionKind::Passthrough, passthrough);
        }
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct WindowEx : WindowExT<WindowEx, implementation::WindowEx>
    {
    };
}
