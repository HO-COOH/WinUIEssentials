#pragma once

namespace winrt::Windows::Data::Json
{
	struct JsonObject;
}

struct RepoInfo
{
	int Stars{};
	int Forks{};
	int Issues{};

	constexpr RepoInfo() = default;
	RepoInfo(winrt::Windows::Data::Json::JsonObject const& json);
};