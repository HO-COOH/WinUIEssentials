#pragma once

#include "TaskbarIcon.g.h"
#include "ThemeAdaptiveIcon.h"
#include "NormalTaskbarIcon.h"
#include <variant>
#include <winrt/Windows.Storage.h>
#include "TaskbarIconXamlEvents.h"
#include "include/EnsureDependencyProperty.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct TaskbarIcon : TaskbarIconT<TaskbarIcon>, EnsureDependencyProperty<TaskbarIcon>
    {
        TaskbarIcon();

        winrt::hstring ToolTip();
        void ToolTip(winrt::hstring const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ToolTipProperty();

        winrt::guid Guid();
        void Guid(winrt::guid value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty GuidProperty();

        winrt::Windows::Foundation::Uri Icon() { return nullptr; }
        void Icon(winrt::Windows::Foundation::Uri value);

        winrt::hstring IconFile();
        void IconFile(winrt::hstring const& value);

        WinUI3Package::GeneratedIconSource LightThemeIconSource();
        void LightThemeIconSource(WinUI3Package::GeneratedIconSource value);

        winrt::Windows::Foundation::Uri LightThemeIcon();
        void LightThemeIcon(winrt::Windows::Foundation::Uri value);

        winrt::hstring LightThemeIconFile();
        void LightThemeIconFile(winrt::hstring const& value);

        WinUI3Package::GeneratedIconSource DarkThemeIconSource();
        void DarkThemeIconSource(WinUI3Package::GeneratedIconSource value);

        winrt::Windows::Foundation::Uri DarkThemeIcon();
        void DarkThemeIcon(winrt::Windows::Foundation::Uri value);

        winrt::hstring DarkThemeIconFile();
        void DarkThemeIconFile(winrt::hstring const& value);

        winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase RightClickMenu() { return m_xamlMenuFlyout; }
        void RightClickMenu(winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase const& value);

        winrt::Microsoft::UI::Xaml::ElementTheme MenuTheme();
        void MenuTheme(winrt::Microsoft::UI::Xaml::ElementTheme value);

        void Show();
        void Remove();

        winrt::event_token LeftPressed(WinUI3Package::SignalDelegate const& handler);
        winrt::event_token LeftDoublePressed(WinUI3Package::SignalDelegate const& handler);
        winrt::event_token RightPressed(WinUI3Package::SignalDelegate const& handler);
        winrt::event_token PointerHover(WinUI3Package::SignalDelegate const& handler);

        void LeftPressed(winrt::event_token const& token);
        void LeftDoublePressed(winrt::event_token const& token);
        void RightPressed(winrt::event_token const& token);
        void PointerHover(winrt::event_token const& handler);

        static void EnsureDependencyProperties();
    private:
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_tooltipProperty{ nullptr };
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_guidProperty{ nullptr };

        ThemeAdaptiveIcon& getThemeAdaptiveIcon();
        NormalTaskbarIcon& getNormalIcon();

        winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase m_xamlMenuFlyout{ nullptr };
        TaskbarIconXamlEvents m_events;

        std::variant<std::monostate, ThemeAdaptiveIcon, NormalTaskbarIcon> m_icon;
        winrt::hstring m_tooltip;
        winrt::Microsoft::UI::Xaml::ElementTheme m_theme{ winrt::Microsoft::UI::Xaml::ElementTheme::Default };

        winrt::guid m_guid{};
        bool m_showCalled{};

        template<typename F>
        winrt::Windows::Foundation::IAsyncAction setIconFromUri(winrt::Windows::Foundation::Uri uri, F f)
        {
            if (auto file = co_await winrt::Windows::Storage::StorageFile::GetFileFromApplicationUriAsync(uri))
                f(file.Path());
            if (m_showCalled)
                Show();
        }

        static void onToolTipChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg
        );

        static void onGuidChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg
        );
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct TaskbarIcon : TaskbarIconT<TaskbarIcon, implementation::TaskbarIcon>
    {
    };
}
