#pragma once

#include "TaskbarIconPage.g.h"
#include <PropertyChangeHelper.hpp>

namespace winrt::WinUI3Example::implementation
{
    struct TaskbarIconPage : TaskbarIconPageT<TaskbarIconPage>, MvvmHelper::PropertyChangeHelper<TaskbarIconPage>
    {
        TaskbarIconPage();
        void NormalIconAdd_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ThemeAdaptiveIconAddButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void MenuFlyoutItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void TaskbarIcon_LeftPressed();
        void TaskbarIcon_LeftDoublePressed();
        void TaskbarIcon_RightPressed();
        void TaskbarIcon_PointerHover();
        void PopupMenuFlyoutItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void NormalIconWithPopupMenuAdd_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        bool IsNormalIconWithXamlMenuAdded();
        bool IsNormalIconWithPopupMenuAdded();
        bool IsThemeAdaptiveIconWithXamlMenuAdded();
        bool IsThemeAdaptiveIconWithPopupMenuAdded();
        static bool BoolAnd(bool v1, bool v2);
        static bool NegateBool(bool v);

        int LeftPressedCount();
        int LeftDoublePressedCount();
        int HoverCount();
        int RightPressedCount();
    private:
        bool m_isNormalIconWithXamlMenuAdded{};
        bool m_isNormalIconWithPopupMenuAdded{};
        bool m_isThemeAdaptiveIconWithXamlMenuAdded{};
        bool m_isThemeAdaptiveIconWithPopupMenuAdded{};

        void isNormalIconWithXamlMenuAdded(bool value);
        void isNormalIconWithPopupMenuAdded(bool value);
        void isThemeAdaptiveIconWithXamlMenuAdded(bool value);
        void isThemeAdaptiveIconWithPopupMenuAdded(bool value);

        int m_radioSelection = -1;
        int m_leftPressedCount{};
        int m_leftDoublePressedCount{};
        int m_hoverCount{};
        int m_rightPressedCount{};
    public:
        void ThemeAdaptiveIconWithPopupMenuAdd_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ToggleSwitch_Toggled(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TaskbarIconPage : TaskbarIconPageT<TaskbarIconPage, implementation::TaskbarIconPage>
    {
    };
}
