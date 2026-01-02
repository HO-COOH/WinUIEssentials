#include "pch.h"
#include "RepoInfo.h"
#include <winrt/Windows.Data.Json.h>

RepoInfo::RepoInfo(winrt::Windows::Data::Json::JsonObject const& json) : 
	Stars{static_cast<int>(json.GetNamedNumber(L"stargazers_count"))},
	Forks{static_cast<int>(json.GetNamedNumber(L"forks_count"))},
	Issues{static_cast<int>(json.GetNamedNumber(L"open_issues_count"))}
{
}
