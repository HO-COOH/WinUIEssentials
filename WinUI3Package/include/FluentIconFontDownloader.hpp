#pragma once
#include <winrt/Windows.Web.Http.h>
#include <winrt/Windows.Foundation.h>
#include <filesystem>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.Web.Http.Filters.h>
#include <wil/resource.h>

class FluentIconFontDownloader
{
	constexpr static auto FontDownloadLink = L"https://aka.ms/SegoeFluentIcons";
public:
	template<typename F>
	static winrt::Windows::Foundation::IAsyncAction DownloadAsync(winrt::Windows::Storage::StorageFolder folder, F&& onProgress)
	{
		winrt::Windows::Web::Http::HttpClient client{ winrt::Windows::Web::Http::Filters::HttpBaseProtocolFilter{} };
		auto op = client.GetBufferAsync(winrt::Windows::Foundation::Uri{ FontDownloadLink });
		op.Progress(onProgress);
		auto fileCopy = co_await folder.CreateFileAsync(L"file.zip", winrt::Windows::Storage::CreationCollisionOption::ReplaceExisting);
		auto buffer = co_await op;
		auto stream = co_await fileCopy.OpenAsync(winrt::Windows::Storage::FileAccessMode::ReadWrite);
		co_await stream.WriteAsync(buffer);
		stream.Close();

		wil::unique_process_information pi;
		STARTUPINFO si{};
		auto cmd = std::format(
			L"tar -xvf \"{}\"",
			fileCopy.Path()
		);
		CreateProcessW(
			nullptr,
			cmd.data(),
			nullptr,
			nullptr,
			false,
			NULL,
			nullptr,
			std::filesystem::path{fileCopy.Path().data()}.parent_path().wstring().data(),
			&si,
			&pi
		);
		WaitForSingleObject(pi.hProcess, INFINITE);
	}
};