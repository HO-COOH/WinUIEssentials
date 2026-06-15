#include "pch.h"
#include "NugetPackageInfo.h"
#if __has_include("NugetPackageInfo.g.cpp")
#include "NugetPackageInfo.g.cpp"
#endif

#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Web.Http.h>
#include <winrt/Windows.Foundation.h>

namespace winrt::PackageRoot::implementation
{
	winrt::hstring NugetPackageInfo::PackageId()
	{
		return m_packageId;
	}

	void NugetPackageInfo::PackageId(winrt::hstring const& value)
	{
		if (m_packageId == value) return;
		m_packageId = value;
		raisePropertyChange(L"PackageId");
		raisePropertyChange(L"Url");
	}

	winrt::hstring NugetPackageInfo::Version()
	{
		return m_version;
	}

	int NugetPackageInfo::Downloads()
	{
		return m_downloads;
	}

	winrt::Windows::Foundation::Uri NugetPackageInfo::Url()
	{
		return winrt::Windows::Foundation::Uri{
			std::format(L"https://www.nuget.org/packages/{}", m_packageId)
		};
	}

	winrt::fire_and_forget NugetPackageInfo::request(
		winrt::Windows::Web::Http::HttpClient const& client,
		winrt::hstring const& endPoint)
	{
		auto strongThis = get_strong();
		try
		{
			auto url = std::format(L"{}?q=packageid:{}", endPoint, m_packageId);
			auto body = co_await client.GetStringAsync(winrt::Windows::Foundation::Uri{ url });
			auto data = winrt::Windows::Data::Json::JsonObject::Parse(body)
				.GetNamedArray(L"data")
				.GetAt(0)
				.GetObject();

			m_version = data.GetNamedString(L"version");
			m_downloads = static_cast<int>(data.GetNamedNumber(L"totalDownloads"));
			raisePropertyChange(L"Version");
			if (m_downloads != 0)
				raisePropertyChange(L"Downloads");
		}
		catch (...)
		{
		}
	}
}
