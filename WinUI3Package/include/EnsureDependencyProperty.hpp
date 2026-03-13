#pragma once

template <typename Derived>
struct EnsureDependencyProperty
{
    EnsureDependencyProperty()
    {
        static bool registered = [this] {
            Derived::EnsureDependencyProperties();
            return true;
        }();
    }
};

