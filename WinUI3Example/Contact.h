#pragma once

#include "Contact.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct Contact : ContactT<Contact>
    {
        Contact(
            winrt::hstring const& firstName,
            winrt::hstring const& lastName,
            winrt::hstring const& company
        );

        winrt::hstring FirstName();
        winrt::hstring LastName();
        winrt::hstring Company();
        winrt::hstring Name();
    private:
        winrt::hstring m_firstName;
        winrt::hstring m_lastName;
        winrt::hstring m_company;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct Contact : ContactT<Contact, implementation::Contact>
    {
    };
}
