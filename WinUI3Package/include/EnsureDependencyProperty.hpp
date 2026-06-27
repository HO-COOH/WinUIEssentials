#pragma once

template <typename Derived>
class EnsureDependencyProperty
{
public:
    EnsureDependencyProperty()
    {
        Derived::EnsureDependencyProperties();
    }

    static Derived* GetSelf(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d)
    {
        return winrt::get_self<Derived>(d.as<typename Derived::class_type>());
    }
};

