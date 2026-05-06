#pragma once

#include "ContributorItem.g.h"

namespace winrt::PackageRoot::implementation
{
    struct ContributorItem : ContributorItemT<ContributorItem>
    {
        ContributorItem(
            winrt::hstring name,
            winrt::Windows::Foundation::Uri avator,
            winrt::Windows::Foundation::Uri profile
        );

		ContributorItem(winrt::Windows::Data::Json::JsonObject const& json);

		winrt::hstring Name();
		winrt::Windows::Foundation::Uri Avator();
		winrt::Windows::Foundation::Uri Profile();

        void OpenWebsite();
    private:
        winrt::hstring m_name;
        winrt::Windows::Foundation::Uri m_avator{ nullptr };
		winrt::Windows::Foundation::Uri m_profile{ nullptr };
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct ContributorItem : ContributorItemT<ContributorItem, implementation::ContributorItem>
    {
    };
}
