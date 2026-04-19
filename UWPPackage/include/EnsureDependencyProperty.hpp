#pragma once

template <typename Derived>
struct EnsureDependencyProperty
{
    EnsureDependencyProperty()
    {
        Derived::EnsureDependencyProperties();
    }
};

