#pragma once

#include "TypeNameExtension.g.h"

namespace winrt::PackageRoot::implementation
{
    struct TypeNameExtension : TypeNameExtensionT<TypeNameExtension>
    {
        TypeNameExtension() = default;
        TypeNameExtension(winrt::Windows::UI::Xaml::Interop::TypeName const& type);

        winrt::Windows::UI::Xaml::Interop::TypeName Type();
		void Type(winrt::Windows::UI::Xaml::Interop::TypeName const& value);

        winrt::Windows::Foundation::IInspectable ProvideValue();

#if defined Build_WinUIPackage
        winrt::Windows::Foundation::IInspectable ProvideValue(
            winrt::WindowsNamespace::UI::Xaml::IXamlServiceProvider provider
        )
        {
            return ProvideValue();
        }
#endif
    private:
        winrt::Windows::UI::Xaml::Interop::TypeName m_type;
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct TypeNameExtension : TypeNameExtensionT<TypeNameExtension, implementation::TypeNameExtension>
    {
    };
}
