#pragma once
#include <chrono>
#include <optional>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Data.Json.h>

class UpdateChecker
{
	constexpr static auto checkUrl = L"https://api.github.com/repos/HO-COOH/WinUIEssentials/releases/latest";
	
	class LatestReleaseResult
	{
		winrt::Windows::Data::Json::JsonObject m_response;
		winrt::Windows::Data::Json::JsonArray assets();
		winrt::Windows::Data::Json::JsonObject findAsset(std::wstring_view name);
	public:
		LatestReleaseResult(winrt::hstring&& value);

		winrt::hstring TagName();
		winrt::hstring ArmRelease();
		winrt::hstring Arm64Release();
		winrt::hstring X64Release();
		winrt::hstring X86Release();
	};

	static std::optional<LatestReleaseResult> s_latestReleaseResult;
	static std::chrono::year_month_day parseFromString(std::wstring_view str);
	static std::wstring getUnzipFolderPath();
	static std::wstring getFileDownloadPath();
	static bool isAbleToDownloadAndUnzip();
public:
	/**
	 * @brief Check github whether a new release that has a newer date than current installed package
	 */
	static winrt::Windows::Foundation::IAsyncOperation<bool> HasUpdate();

	static void DownloadRelease();
};