// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "Global.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"
#include <winrt/Microsoft.Windows.AppNotifications.h>
#include <microsoft.ui.xaml.window.h>

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
        using namespace winrt;
        using namespace Windows::Foundation;
        using namespace Microsoft::UI::Xaml;
        using namespace Microsoft::UI::Xaml::Controls;
        using namespace Microsoft::UI::Xaml::Navigation;
        InitializeComponent();

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
        UnhandledException([this](IInspectable const&, UnhandledExceptionEventArgs const& e)
            {
                if (IsDebuggerPresent())
                {
                    auto errorMessage = e.Message();
                    __debugbreak();
                }
            });
#endif
    }




    static HWND GetHWNDFromWindow(winrt::Microsoft::UI::Xaml::Window const& window)
    {
        HWND nativeWindow{ nullptr };
        winrt::check_hresult(window.as<::IWindowNative>()->get_WindowHandle(&nativeWindow));
        return nativeWindow;
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
        MainHwnd() = GetHWNDFromWindow(window);


    }
}