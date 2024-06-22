#include "pch.h"
#include "Person.h"
#if __has_include("Person.g.cpp")
#include "Person.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	Person::Person(winrt::hstring name) : m_name{std::move(name)}
	{
	}
	winrt::hstring Person::Name()
	{
		return m_name;
	}
}
