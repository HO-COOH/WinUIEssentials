#pragma once

#include "SettingsCommandEx.g.h"

namespace winrt::UWPPackage::implementation
{
    struct SettingsCommandEx : SettingsCommandExT<SettingsCommandEx>
    {
        SettingsCommandEx() = default;

        winrt::Windows::Foundation::IInspectable Id();
        void Id(winrt::Windows::Foundation::IInspectable value);

        winrt::hstring Label();
        void Label(winrt::hstring value);

        winrt::event_token Invoke(winrt::Windows::Foundation::EventHandler<winrt::Windows::UI::Popups::IUICommand> const handler);
        void Invoke(winrt::event_token const& token) noexcept;

        winrt::Windows::UI::Popups::UICommandInvokedHandler Invoked();
        void Invoked(winrt::Windows::UI::Popups::UICommandInvokedHandler value);

    private:
        winrt::Windows::Foundation::IInspectable m_id;
        winrt::hstring m_label;
        winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::UI::Popups::IUICommand>> m_InvokeEvent;
        winrt::Windows::UI::Popups::UICommandInvokedHandler m_invokeHandler = [this](auto...)
            {
                Title(m_label);
                Show();
                m_InvokeEvent(*this, *this);
            };
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct SettingsCommandEx : SettingsCommandExT<SettingsCommandEx, implementation::SettingsCommandEx>
    {
    };
}
