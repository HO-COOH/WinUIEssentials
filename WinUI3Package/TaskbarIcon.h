#pragma once

#include "TaskbarIcon.g.h"

#include "TaskbarIconMessageWindow.h"
#include "GuidWrapper.h"
#include "ThemeAdaptiveIcon.h"
#include "NormalTaskbarIcon.h"
#include <variant>
#include <winrt/Windows.Storage.h>


namespace winrt::WinUI3Package::implementation
{
    struct TaskbarIcon : TaskbarIconT<TaskbarIcon>
    {
        TaskbarIcon() = default;

        winrt::Microsoft::UI::Xaml::UIElement ToolTip() { return nullptr; }
        void ToolTip(winrt::Microsoft::UI::Xaml::UIElement value) {}

        WinUI3Package::GeneratedIconSource IconSource();
        void IconSource(WinUI3Package::GeneratedIconSource value);

        winrt::Windows::Foundation::Uri Icon() { return nullptr; }
        void Icon(winrt::Windows::Foundation::Uri value);

        winrt::hstring IconFile() { return L""; }
        void IconFile(winrt::hstring const& value);

        WinUI3Package::GeneratedIconSource LightThemeIconSource();
        void LightThemeIconSource(WinUI3Package::GeneratedIconSource value);

        winrt::Windows::Foundation::Uri LightThemeIcon();
        void LightThemeIcon(winrt::Windows::Foundation::Uri value);

        winrt::hstring LightThemeIconFile() { return L""; }
        void LightThemeIconFile(winrt::hstring const& value);

        WinUI3Package::GeneratedIconSource DarkThemeIconSource();
        void DarkThemeIconSource(WinUI3Package::GeneratedIconSource value);

        winrt::Windows::Foundation::Uri DarkThemeIcon();
        void DarkThemeIcon(winrt::Windows::Foundation::Uri value);

        winrt::hstring DarkThemeIconFile() { return L""; }
        void DarkThemeIconFile(winrt::hstring const& value);

        winrt::Microsoft::UI::Xaml::Controls::MenuFlyout RightClickMenu() { return m_xamlMenuFlyout; }
        void RightClickMenu(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& value);

        winrt::Microsoft::UI::Xaml::ElementTheme MenuTheme();
        void MenuTheme(winrt::Microsoft::UI::Xaml::ElementTheme value);

        void Show();
        void Remove();

        //winrt::Windows::Foundation::IInspectable RightClickMenu() { return nullptr; }
        //void RightClickMenu(winrt::Windows::Foundation::IInspectable) {}

    private:
        WinUI3Package::GeneratedIconSource m_iconSource{ nullptr };

        ThemeAdaptiveIcon& getThemeAdaptiveIcon();
        NormalTaskbarIcon& getNormalIcon();

        winrt::Microsoft::UI::Xaml::Controls::MenuFlyout m_xamlMenuFlyout{ nullptr };

        std::variant<std::monostate, ThemeAdaptiveIcon, NormalTaskbarIcon> m_icon;


        template<typename F>
        winrt::Windows::Foundation::IAsyncAction setIconFromUri(winrt::Windows::Foundation::Uri uri, F&& f)
        {
            if (auto file = co_await winrt::Windows::Storage::StorageFile::GetFileFromApplicationUriAsync(uri))
                f(file.Path());
        }
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct TaskbarIcon : TaskbarIconT<TaskbarIcon, implementation::TaskbarIcon>
    {
    };
}
