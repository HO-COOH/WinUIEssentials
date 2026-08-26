#include "pch.h"
#include "XamlOptionalSettingsStore.h"
#include <winrt/Windows.Storage.h>

constexpr static auto Key = L"XamlOptionalSettings";

void XamlOptionalSettingsStore::save()
{
	m_settings.Insert(Key, winrt::box_value(m_flags));
}

XamlOptionalSettingsStore::XamlOptionalSettingsStore() :
	XamlOptionalSettingsStore{ winrt::Windows::Storage::ApplicationData::Current().LocalSettings().Values() }
{
}

XamlOptionalSettingsStore::XamlOptionalSettingsStore(winrt::Windows::Foundation::Collections::IPropertySet const& settings) :
	m_settings{settings}
{
	if (auto boxed = settings.TryLookup(Key))
		m_flags = winrt::unbox_value<uint32_t>(boxed);
}