#pragma once

#include "TaskbarIcon.g.h"
#include <shellapi.h>
#include "NotifyIconData.h"
#include <gdiplus.h>
#include <filesystem>
#include "TaskbarIconMessageWindow.h"
#include "GuidWrapper.h"
#pragma comment(lib, "gdiplus.lib")

namespace winrt::WinUI3Package::implementation
{
    struct TaskbarIcon : TaskbarIconT<TaskbarIcon>
    {
        TaskbarIcon()
        {
            HICON hicon{};
            {
                ULONG_PTR gdiPlusToken;
                Gdiplus::GdiplusStartupInput gdiPlusStartupInput;
                Gdiplus::GdiplusStartup(&gdiPlusToken, &gdiPlusStartupInput, nullptr);

                wchar_t path[MAX_PATH]{};
                GetModuleFileName(NULL, path, MAX_PATH);
                auto iconPath = std::filesystem::path{ path }.parent_path() / L"Assets/Owl.jpg";
                
                Gdiplus::Image iconImage{ iconPath.wstring().data() };
                INT const width = iconImage.GetWidth();
                INT const height = iconImage.GetHeight();

                Gdiplus::Bitmap bitmap{ width, height };
                auto graphics = Gdiplus::Graphics::FromImage(&bitmap);

                graphics->Clear(Gdiplus::Color::Transparent);
                graphics->DrawImage(&iconImage, 0, 0, width, height);

                bitmap.GetHICON(&hicon);
            }
            NotifyIconData data;

            //data.guidItem({ 0x10cb84cc, 0xaa8f, 0x42ed, { 0xb1, 0x1c, 0x3a, 0x83, 0x9f, 0xb0, 0x74, 0x73 } });
            data.guidItem(GuidWrapper{});
            data.hIcon(hicon);
            data.szInfoTitle(L"My icon");
            data.uCallbackMessage(0x1000);
            data.hWnd(TaskbarIconMessageWindow::Get());
            data.Add();
        }

        winrt::Microsoft::UI::Xaml::UIElement ToolTip() { return nullptr; }
        void ToolTip(winrt::Microsoft::UI::Xaml::UIElement value) {}

        WinUI3Package::GeneratedIconSource IconSource();
        void IconSource(WinUI3Package::GeneratedIconSource value);

        winrt::Windows::Foundation::Uri Icon() { return nullptr; }
        void Icon(winrt::Windows::Foundation::Uri value) {}

        WinUI3Package::GeneratedIconSource LightThemeIconSource();
        void LightThemeIconSource(WinUI3Package::GeneratedIconSource value);

        winrt::Windows::Foundation::Uri LightThemeIcon();
        void LightThemeIcon(winrt::Windows::Foundation::Uri value);

        WinUI3Package::GeneratedIconSource DarkThemeIconSource();
        void DarkThemeIconSource(WinUI3Package::GeneratedIconSource value);

        winrt::Windows::Foundation::Uri DarkThemeIcon();
        void DarkThemeIcon(winrt::Windows::Foundation::Uri value);

        winrt::Microsoft::UI::Xaml::Controls::MenuFlyout RightClickMenu() { return nullptr; }
        void RightClickMenu(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout) {}

        void Show();
        void Remove();

        //winrt::Windows::Foundation::IInspectable RightClickMenu() { return nullptr; }
        //void RightClickMenu(winrt::Windows::Foundation::IInspectable) {}

    private:
        WinUI3Package::GeneratedIconSource m_iconSource{ nullptr };

        
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct TaskbarIcon : TaskbarIconT<TaskbarIcon, implementation::TaskbarIcon>
    {
    };
}
