#include "pch.h"
#include "StringResourceExtension.h"
#if __has_include("StringResourceExtension.g.cpp")
#include "StringResourceExtension.g.cpp"
#endif
#include <winrt/Microsoft.Windows.ApplicationModel.Resources.h>

namespace winrt::WinUI3Package::implementation
{
	winrt::hstring StringResourceExtension::Name()
	{
		return m_name;
	}

	void StringResourceExtension::Name(winrt::hstring const& value)
	{
		m_name = value;
	}

	winrt::hstring StringResourceExtension::ResourceMap()
	{
		return m_resourceMap;
	}

	void StringResourceExtension::ResourceMap(winrt::hstring const& value)
	{
		m_resourceMap = value;
	}

	winrt::hstring StringResourceExtension::PriPath()
	{
		return m_priPath;
	}

	void StringResourceExtension::PriPath(winrt::hstring const& value)
	{
		m_priPath = value;
	}

	winrt::Windows::Foundation::IInspectable StringResourceExtension::ProvideValue()
	{
		if (m_priPath.empty())
			return winrt::box_value(defaultResourceLoader().GetString(m_name));

		//m_priPath not empty
		return winrt::box_value(
			m_resourceMap.empty() ?
			winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceLoader{ m_priPath }.GetString(m_name) :
			winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceLoader{m_priPath, m_resourceMap}.GetString(m_name)
		);
	}

	winrt::Windows::Foundation::IInspectable StringResourceExtension::ProvideValue(winrt::WinUINamespace::UI::Xaml::IXamlServiceProvider const&)
	{
		return ProvideValue();
	}
	winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceLoader& StringResourceExtension::defaultResourceLoader()
	{
		static winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceLoader s_loader;
		return s_loader;
	}
}
