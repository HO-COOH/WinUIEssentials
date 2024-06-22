#pragma once

#include "SettingsPaneEx.g.h"
#include <winrt/Windows.UI.ApplicationSettings.h>

namespace winrt::UWPPackage::implementation
{
    struct SettingsPaneEx : SettingsPaneExT<SettingsPaneEx>
    {
        SettingsPaneEx() = default;

        static winrt::Windows::UI::Xaml::DependencyProperty SettingsProperty();

        static void SetSettings(
            winrt::Windows::Foundation::IInspectable element,
            winrt::Windows::Foundation::Collections::IVector<winrt::UWPPackage::SettingsCommandEx> value
        );

        static winrt::Windows::Foundation::Collections::IVector<winrt::UWPPackage::SettingsCommandEx> GetSettings(winrt::Windows::Foundation::IInspectable element);

        static void Show();
        void ShowCurrent();

        static winrt::Windows::UI::Xaml::DependencyProperty KeyboardAcceleratorProperty();
        static void SetKeyboardAccelerator(winrt::Windows::Foundation::IInspectable element, winrt::Windows::UI::Xaml::Input::KeyboardAccelerator key);
        static winrt::Windows::UI::Xaml::Input::KeyboardAccelerator GetKeyboardAccelerator(winrt::Windows::Foundation::IInspectable element);

        winrt::Windows::Foundation::Collections::IVector<winrt::UWPPackage::SettingsCommandEx> Content();
    private:

        static void addCommandToPane(auto&& commandVector, winrt::Windows::UI::ApplicationSettings::SettingsPaneCommandsRequestedEventArgs& args)
        {
            auto toAdd = args.Request().ApplicationCommands();
            toAdd.Clear();
            for (auto&& item : commandVector)
            {
                toAdd.Append(winrt::Windows::UI::ApplicationSettings::SettingsCommand(winrt::box_value(L""), item.Label(), item.Invoked()));
            }
        }


        winrt::Windows::Foundation::Collections::IVector<UWPPackage::SettingsCommandEx> m_content = winrt::single_threaded_vector<winrt::UWPPackage::SettingsCommandEx>();
        bool m_init = true;

        static winrt::Windows::Foundation::Collections::IVector<UWPPackage::SettingsCommandEx> s_globalSettingsCommands;
        static winrt::Windows::UI::Xaml::DependencyProperty s_settingsProperty;
        static winrt::weak_ref<UWPPackage::SettingsPaneEx> s_lastInvokedInstance;

        static winrt::Windows::UI::Xaml::DependencyProperty s_keyboardAcceleratorProperty;
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct SettingsPaneEx : SettingsPaneExT<SettingsPaneEx, implementation::SettingsPaneEx>
    {
    };
}
