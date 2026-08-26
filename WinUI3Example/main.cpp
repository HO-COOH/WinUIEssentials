#include "pch.h"
#include "App.xaml.h"
#include "XamlOptionalSettingsStore.h"
#include <winrt/Microsoft.UI.Xaml.Settings.h>

static void applyXamlOptionalSettings()
{
    XamlOptionalSettingsStore xamlOptionalSettings;
    if (xamlOptionalSettings.DefaultStyleOptimizations())
        winrt::Microsoft::UI::Xaml::Settings::XamlOptionalChanges::EnableChange(winrt::Microsoft::UI::Xaml::Settings::XamlChangeId::DefaultStyleOptimizations);
    if (xamlOptionalSettings.DeferContextFlyoutInit())
        winrt::Microsoft::UI::Xaml::Settings::XamlOptionalChanges::EnableChange(winrt::Microsoft::UI::Xaml::Settings::XamlChangeId::DeferContextFlyoutInit);
    if (xamlOptionalSettings.IconNoGridOptimization())
        winrt::Microsoft::UI::Xaml::Settings::XamlOptionalChanges::EnableChange(winrt::Microsoft::UI::Xaml::Settings::XamlChangeId::IconNoGridOptimization);
    if (xamlOptionalSettings.OptimizeApplyStyles())
        winrt::Microsoft::UI::Xaml::Settings::XamlOptionalChanges::EnableChange(winrt::Microsoft::UI::Xaml::Settings::XamlChangeId::OptimizeApplyStyles);
}

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    winrt::init_apartment(winrt::apartment_type::single_threaded);
    applyXamlOptionalSettings();

    ::winrt::Microsoft::UI::Xaml::Application::Start([](auto&&)
    {
        ::winrt::make<::winrt::WinUI3Example::implementation::App>();
    });
}