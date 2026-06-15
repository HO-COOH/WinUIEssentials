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

    static Derived* GetSelf(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d)
    {
        return winrt::get_self<Derived>(d.as<typename Derived::class_type>());
    }
};

