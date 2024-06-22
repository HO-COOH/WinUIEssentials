#include "pch.h"
#include "SettingsPaneEx.h"
#if __has_include("SettingsPaneEx.g.cpp")
#include "SettingsPaneEx.g.cpp"
#endif
#include <winrt/Windows.System.Threading.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include "SettingsCommandEx.g.h"

namespace winrt::UWPPackage::implementation
{
    winrt::Windows::Foundation::Collections::IVector<UWPPackage::SettingsCommandEx> SettingsPaneEx::s_globalSettingsCommands
        = winrt::single_threaded_vector<UWPPackage::SettingsCommandEx>();

    winrt::Windows::UI::Xaml::DependencyProperty SettingsPaneEx::s_settingsProperty =
        winrt::Windows::UI::Xaml::DependencyProperty::RegisterAttached(
            L"Settings",
            winrt::xaml_typename<winrt::Windows::Foundation::Collections::IVector<UWPPackage::SettingsCommandEx>>(),
            winrt::xaml_typename<UWPPackage::SettingsPaneEx>(),
            nullptr
        );

    winrt::Windows::UI::Xaml::DependencyProperty SettingsPaneEx::s_keyboardAcceleratorProperty =
        winrt::Windows::UI::Xaml::DependencyProperty::RegisterAttached(
            L"KeyboardAccelerator",
            winrt::xaml_typename<winrt::Windows::UI::Xaml::Input::KeyboardAccelerator>(),
            winrt::xaml_typename<UWPPackage::SettingsPaneEx>(),
            nullptr
        );

    winrt::weak_ref<UWPPackage::SettingsPaneEx> SettingsPaneEx::s_lastInvokedInstance{ nullptr };

    winrt::Windows::UI::Xaml::DependencyProperty SettingsPaneEx::SettingsProperty()
    {
        return s_settingsProperty;
    }

    void SettingsPaneEx::SetSettings(
        winrt::Windows::Foundation::IInspectable element,
        winrt::Windows::Foundation::Collections::IVector<winrt::UWPPackage::SettingsCommandEx> value)
    {
        s_globalSettingsCommands = value;
    }

    winrt::Windows::Foundation::Collections::IVector<winrt::UWPPackage::SettingsCommandEx> SettingsPaneEx::GetSettings(winrt::Windows::Foundation::IInspectable element)
    {
        return s_globalSettingsCommands;
    }


    void SettingsPaneEx::Show()
    {
        auto view = winrt::Windows::UI::ApplicationSettings::SettingsPane::GetForCurrentView();
        static bool init = true;
        if (init || s_lastInvokedInstance)
        {
            view.CommandsRequested([](auto, winrt::Windows::UI::ApplicationSettings::SettingsPaneCommandsRequestedEventArgs args)
                {
                    addCommandToPane(s_globalSettingsCommands, args);
                });
            init = false;
        }
        s_lastInvokedInstance = nullptr;
        view.Show();
    }


    void SettingsPaneEx::ShowCurrent()
    {
        auto view = winrt::Windows::UI::ApplicationSettings::SettingsPane::GetForCurrentView();
        if (m_init || s_lastInvokedInstance != winrt::make_weak<UWPPackage::SettingsPaneEx>(*this))
        {
            view.CommandsRequested([this](auto, winrt::Windows::UI::ApplicationSettings::SettingsPaneCommandsRequestedEventArgs args)
                {
                    addCommandToPane(m_content, args);
                });
            m_init = false;
        }
        s_lastInvokedInstance = winrt::make_weak<UWPPackage::SettingsPaneEx>(*this);
        view.Show();
    }

    winrt::Windows::Foundation::Collections::IVector<winrt::UWPPackage::SettingsCommandEx> SettingsPaneEx::Content()
    {
        return m_content;
    }

    winrt::Windows::UI::Xaml::DependencyProperty SettingsPaneEx::KeyboardAcceleratorProperty()
    {
        return s_keyboardAcceleratorProperty;
    }

    static bool isAnyKeyDown(auto... virtualKeys)
    {
        return ((static_cast<uint32_t>(winrt::Windows::UI::Core::CoreWindow::GetForCurrentThread().GetKeyState(virtualKeys)) & static_cast<uint32_t>(winrt::Windows::UI::Core::CoreVirtualKeyStates::Down)) || ...);
    }

    void SettingsPaneEx::SetKeyboardAccelerator(winrt::Windows::Foundation::IInspectable element, winrt::Windows::UI::Xaml::Input::KeyboardAccelerator key)
    {
        winrt::Windows::System::Threading::ThreadPool::RunAsync([key](auto...) -> winrt::Windows::Foundation::IAsyncAction {
            auto keyCopy = key;
            while (true)
            {
                co_await std::chrono::milliseconds{ 100 };

                auto coreWindow = winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow();
                if (!coreWindow)
                    continue;

                auto coreDispatcher = coreWindow.Dispatcher();
                if (!coreDispatcher)
                    continue;

                coreDispatcher.AcceleratorKeyActivated([keyCopy](auto, winrt::Windows::UI::Core::AcceleratorKeyEventArgs arg)
                    {
                        arg.Handled(true);
                        bool modifierKeyCorrect = false;
                        auto coreWindow = winrt::Windows::UI::Core::CoreWindow::GetForCurrentThread();
                        switch (keyCopy.Modifiers())
                        {
                        case winrt::Windows::System::VirtualKeyModifiers::Control:
                            modifierKeyCorrect = isAnyKeyDown(winrt::Windows::System::VirtualKey::Control);
                            break;
                        case winrt::Windows::System::VirtualKeyModifiers::Menu:
                            modifierKeyCorrect = isAnyKeyDown(winrt::Windows::System::VirtualKey::Control);
                            break;
                        case winrt::Windows::System::VirtualKeyModifiers::Shift:
                            modifierKeyCorrect = isAnyKeyDown(
                                winrt::Windows::System::VirtualKey::Shift,
                                winrt::Windows::System::VirtualKey::LeftShift,
                                winrt::Windows::System::VirtualKey::RightShift);
                            break;
                        case winrt::Windows::System::VirtualKeyModifiers::Windows:
                            modifierKeyCorrect = isAnyKeyDown(
                                winrt::Windows::System::VirtualKey::LeftWindows,
                                winrt::Windows::System::VirtualKey::RightShift
                            );
                            break;
                        default:
                            modifierKeyCorrect = true;
                            break;
                        }
                        if (modifierKeyCorrect && arg.VirtualKey() == keyCopy.Key())
                            Show();
                    });
                break;
            }

            });
    }

    winrt::Windows::UI::Xaml::Input::KeyboardAccelerator SettingsPaneEx::GetKeyboardAccelerator(winrt::Windows::Foundation::IInspectable element)
    {
        return {};
    }
}
