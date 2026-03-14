#pragma once

#include "TypeNameExtension.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct TypeNameExtension : TypeNameExtensionT<TypeNameExtension>
    {
        TypeNameExtension() = default;
        TypeNameExtension(winrt::Windows::UI::Xaml::Interop::TypeName const& type);

        winrt::Windows::UI::Xaml::Interop::TypeName Type();
		void Type(winrt::Windows::UI::Xaml::Interop::TypeName const& value);

        winrt::Windows::Foundation::IInspectable ProvideValue();
        winrt::Windows::Foundation::IInspectable ProvideValue(
            winrt::Microsoft::UI::Xaml::IXamlServiceProvider provider
        )
        {
            return ProvideValue();
        }

    private:
        winrt::Windows::UI::Xaml::Interop::TypeName m_type;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct TypeNameExtension : TypeNameExtensionT<TypeNameExtension, implementation::TypeNameExtension>
    {
    };
}
