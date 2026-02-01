// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"
#include "TenMicaWindow.xaml.h"
#include <winrt/Microsoft.Windows.AppNotifications.h>
#include "UpdateChecker.h"
#include <winrt/Windows.Services.Store.h>
#include <wil/cppwinrt.h>


namespace winrt::WinUI3Example::implementation
{
    // To learn more about WinUI, the WinUI project structure,
    // and more about our project templates, see: http://aka.ms/winui-project-info.

    /// <summary>
    /// Initializes the singleton application object.  This is the first line of authored code
    /// executed, and as such is the logical equivalent of main() or WinMain().
    /// </summary>
    App::App()
    {
        InitializeComponent();

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
        UnhandledException([this](winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::UnhandledExceptionEventArgs const& e)
            {
                if (IsDebuggerPresent())
                {
                    auto errorMessage = e.Message();
                    __debugbreak();
                }
            });
#else
        UnhandledException([](winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::UnhandledExceptionEventArgs const& e)
            {
                MessageBox(nullptr, e.Message().data(), L"Unhandled exception", 0);
                e.Handled(true);
            });
#endif
    }


    /// <summary>
    /// Invoked when the application is launched.
    /// </summary>
    /// <param name="e">Details about the launch request and process.</param>
    /// 
    void App::OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&)
    {
        window = make<MainWindow>();
        window.Activate();
        //winrt::WinUI3Example::TenMicaWindow{}.Activate();

        //We don't need this, as we publish to Microsoft Store
        //if (co_await UpdateChecker::HasUpdate())
        //    UpdateChecker::DownloadRelease();
    }
}
