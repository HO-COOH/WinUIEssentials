#pragma once

#include "StringResourceExtension.g.h"

namespace winrt::Windows::ApplicationModel::Resources
{
    struct ResourceLoader;
}

namespace winrt::UWPPackage::implementation
{
    struct StringResourceExtension : StringResourceExtensionT<StringResourceExtension>
    {
        winrt::hstring Name();
        void Name(winrt::hstring const& value);

        winrt::hstring ResourceMap();
        void ResourceMap(winrt::hstring const& value);

        winrt::Windows::Foundation::IInspectable ProvideValue();
    private:
        static winrt::Windows::ApplicationModel::Resources::ResourceLoader& defaultResourceLoader();
        winrt::hstring m_name;
        winrt::hstring m_resourceMap;
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct StringResourceExtension : StringResourceExtensionT<StringResourceExtension, implementation::StringResourceExtension>
    {
    };
}
