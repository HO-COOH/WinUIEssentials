#include "pch.h"
#include "TypeNameExtension.h"
#if __has_include("TypeNameExtension.g.cpp")
#include "TypeNameExtension.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	TypeNameExtension::TypeNameExtension(winrt::Windows::UI::Xaml::Interop::TypeName const& type) : m_type{type}
	{
	}

	winrt::Windows::UI::Xaml::Interop::TypeName TypeNameExtension::Type()
	{
		return m_type;
	}

	void TypeNameExtension::Type(winrt::Windows::UI::Xaml::Interop::TypeName const& value)
	{
		m_type = value;
	}

	winrt::Windows::Foundation::IInspectable TypeNameExtension::ProvideValue()
	{
		return winrt::box_value(m_type);
	}
}
