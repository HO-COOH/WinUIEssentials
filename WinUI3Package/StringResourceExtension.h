#pragma once

#include "StringResourceExtension.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct StringResourceExtension : StringResourceExtensionT<StringResourceExtension>
    {
        winrt::hstring Name();
        void Name(winrt::hstring const& value);

        winrt::hstring ResourceMap();
        void ResourceMap(winrt::hstring const& value);

        winrt::hstring PriPath();
        void PriPath(winrt::hstring const& value);

        winrt::Windows::Foundation::IInspectable ProvideValue();
        winrt::Windows::Foundation::IInspectable ProvideValue(winrt::WinUINamespace::UI::Xaml::IXamlServiceProvider const& provider);
    private:
        static winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceLoader& defaultResourceLoader();
        winrt::hstring m_name;
        winrt::hstring m_resourceMap;
        winrt::hstring m_priPath;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct StringResourceExtension : StringResourceExtensionT<StringResourceExtension, implementation::StringResourceExtension>
    {
    };
}
