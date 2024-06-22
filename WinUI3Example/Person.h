#pragma once

#include "Person.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct Person : PersonT<Person>
    {
        Person(winrt::hstring name);

        winrt::hstring Name();
    private:
        winrt::hstring m_name;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct Person : PersonT<Person, implementation::Person>
    {
    };
}
