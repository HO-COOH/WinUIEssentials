#pragma once

#include "NugetPackageInfo.g.h"
#include "PropertyChangeHelper.hpp"

namespace winrt::PackageRoot::implementation
{
	struct NugetPackageInfo : NugetPackageInfoT<NugetPackageInfo>, MvvmHelper::PropertyChangeHelper<NugetPackageInfo>
    {
        NugetPackageInfo() = default;
        
		winrt::hstring PackageId();
		void PackageId(winrt::hstring const& value);

		winrt::hstring Version();
		int Downloads();

		winrt::Windows::Foundation::Uri Url();

		winrt::fire_and_forget request(winrt::Windows::Web::Http::HttpClient const& client, winrt::hstring const& endPoint);
	private:
		winrt::hstring m_packageId;
		winrt::hstring m_version;
		int m_downloads{};
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct NugetPackageInfo : NugetPackageInfoT<NugetPackageInfo, implementation::NugetPackageInfo>
    {
    };
}
