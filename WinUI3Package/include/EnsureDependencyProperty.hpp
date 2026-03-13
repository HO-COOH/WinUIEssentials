#pragma once

template <typename Derived>
class EnsureDependencyProperty
{
    static inline bool s_registered = false;
public:
    EnsureDependencyProperty()
    {
        if (s_registered)
            return;
        Derived::EnsureDependencyProperties();
        s_registered = true;
    }
};

