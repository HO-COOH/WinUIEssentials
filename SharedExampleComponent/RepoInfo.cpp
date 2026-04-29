#include "pch.h"
#include "RepoInfo.h"
#include <winrt/Windows.Data.Json.h>
#include <sstream>
#include <chrono>
#include <winrt/Windows.Globalization.DateTimeFormatting.h>

static winrt::hstring convertDateTime(winrt::hstring const& str)
{
	std::wistringstream ss{ str.data() };
	std::chrono::sys_seconds timePoint;
	ss >> std::chrono::parse(L"%FT%TZ", timePoint);
	if (ss.fail())
		return L"Invalid Date";

	return winrt::Windows::Globalization::DateTimeFormatting::DateTimeFormatter{ L"longdate shorttime" }.Format(winrt::clock::from_sys(timePoint));
}

RepoInfo::RepoInfo(winrt::Windows::Data::Json::JsonObject const& json) : 
	Stars{static_cast<int>(json.GetNamedNumber(L"stargazers_count"))},
	Forks{static_cast<int>(json.GetNamedNumber(L"forks_count"))},
	Issues{static_cast<int>(json.GetNamedNumber(L"open_issues_count"))},
	UpdatedAt{convertDateTime(json.GetNamedString(L"updated_at"))}
{
}
