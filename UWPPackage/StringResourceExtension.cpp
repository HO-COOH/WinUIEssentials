#include "pch.h"
#include "StringResourceExtension.h"
#if __has_include("StringResourceExtension.g.cpp")
#include "StringResourceExtension.g.cpp"
#endif
#include <winrt/Windows.ApplicationModel.Resources.h>

namespace winrt::UWPPackage::implementation
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

	winrt::Windows::ApplicationModel::Resources::ResourceLoader& StringResourceExtension::defaultResourceLoader()
	{
		static auto s_loader = winrt::Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView();
		return s_loader;
	}

	winrt::Windows::Foundation::IInspectable StringResourceExtension::ProvideValue()
	{
		return  winrt::box_value(m_resourceMap.empty() ?
			defaultResourceLoader().GetString(m_name) :
			winrt::Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView(m_resourceMap).GetString(m_name)
		);
	}
}
