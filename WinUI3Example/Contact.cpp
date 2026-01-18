#include "pch.h"
#include "Contact.h"
#if __has_include("Contact.g.cpp")
#include "Contact.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
    Contact::Contact(
        winrt::hstring const& firstName, 
        winrt::hstring const& lastName, 
        winrt::hstring const& company) :
        m_firstName{firstName},
        m_lastName{lastName},
        m_company{company}
    {
    }

    winrt::hstring Contact::FirstName()
    {
        return m_firstName;
    }

    winrt::hstring Contact::LastName()
    {
        return m_lastName;
    }

    winrt::hstring Contact::Company()
    {
        return m_company;
    }

    winrt::hstring Contact::Name()
    {
        return FirstName() + L" " + LastName();
    }
}
