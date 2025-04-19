#include "pch.h"
#include "UpdateChecker.h"
#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.Web.Http.h>
#include <winrt/Windows.Web.Http.Headers.h>
#include <winrt/Windows.Storage.h>
#include <wil/win32_helpers.h>
#include <wil/stl.h>
#include <wil/resource.h>
#include <filesystem>
#include <fstream>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.UI.Notifications.h>
#include <winrt/Windows.Data.Xml.Dom.h>

std::optional<UpdateChecker::LatestReleaseResult> UpdateChecker::s_latestReleaseResult;
winrt::Windows::Web::Http::HttpClient client{ nullptr };

std::chrono::year_month_day UpdateChecker::parseFromString(std::wstring_view str)
{
    int year{}, month{}, day{};
    swscanf_s(str.data(), L"%d.%d.%d", &year, &month, &day);
    return std::chrono::year_month_day{ std::chrono::year{year}, std::chrono::month{static_cast<unsigned>(month)}, std::chrono::day{static_cast<unsigned>(day)} };
}

std::wstring UpdateChecker::getFileDownloadPath()
{
    return wil::ExpandEnvironmentStringsW<std::wstring>(LR"(%localappdata%\Temp\WinUIEssentialsRelease.zip)");
}

std::wstring UpdateChecker::getUnzipFolderPath()
{
    return wil::ExpandEnvironmentStringsW<std::wstring>(LR"(%localappdata%\Temp\WinUIEssentialsRelease)");
}

winrt::Windows::Foundation::IAsyncOperation<bool> UpdateChecker::HasUpdate()
{
    try
    {
        client = {};
        client.DefaultRequestHeaders().UserAgent().TryParseAdd(LR"(Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/135.0.0.0 Safari/537.36 Edg/135.0.0.0)");
        s_latestReleaseResult.emplace(co_await (co_await client.GetAsync(winrt::Windows::Foundation::Uri{ checkUrl })).Content().ReadAsStringAsync());

        auto installDate = winrt::clock::to_sys(winrt::Windows::ApplicationModel::Package::Current().InstalledDate());
        std::chrono::year_month_day date{ std::chrono::floor<std::chrono::days>(installDate) };
        auto const latestReleaseDate = parseFromString(s_latestReleaseResult->TagName());
        
        //TODO: debug
        //co_return true;
        
        co_return 
            latestReleaseDate.year() > date.year() ||
            latestReleaseDate.month() > date.month() ||
            latestReleaseDate.day() > date.day();
    }
    catch (...)
    {
    }
    co_return false;
}

bool UpdateChecker::isAbleToDownloadAndUnzip()
{
    return true;
}

static void SendInitialUpdateNotification()
{
    winrt::Windows::Data::Xml::Dom::XmlDocument doc;
    doc.LoadXml(LR"(<toast>
  <visual>
    <binding template="ToastGeneric">
      <text>Downloading WinUI3Example</text>
      <progress
        value="{progressValue}"
        valueStringOverride="{progressValueString}"
        status="Downloading..."/>
    </binding>
  </visual>
</toast>)");
    winrt::Windows::UI::Notifications::ToastNotification notification{ doc };
    notification.Tag(L"updater");

    auto updateData = winrt::Windows::UI::Notifications::NotificationData{};
    updateData.Values().Insert(L"progressValue", L"0");
    updateData.Values().Insert(L"progressValueString", L"0 / 0");

    notification.Data(updateData);
    winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier().Show(notification);
}


void UpdateChecker::DownloadRelease()
{
    if (!isAbleToDownloadAndUnzip())
        return;

    auto downloadOp = client.GetBufferAsync(winrt::Windows::Foundation::Uri{
#ifdef _M_IX86
        s_latestReleaseResult->X86Release()
#elif defined _M_AMD64
        s_latestReleaseResult->X64Release()
#elif defined _M_ARM
        s_latestReleaseResult->ArmRelease()
#elif defined _M_ARM64
        s_latestReleaseResult->Arm64Release()
#endif
    });
    SendInitialUpdateNotification();
    downloadOp.Progress(
        [](auto&, winrt::Windows::Web::Http::HttpProgress const& progress)
        {
            if (progress.TotalBytesToReceive)
            {
                auto const totalBytes = progress.TotalBytesToReceive.GetUInt64();
                if (!totalBytes)
                    return;
                auto updateData = winrt::Windows::UI::Notifications::NotificationData{};
                updateData.Values().Insert(L"progressValue", winrt::to_hstring(static_cast<double>(progress.BytesReceived) / totalBytes));
                updateData.Values().Insert(L"progressValueString", std::format(L"{} / {}", progress.BytesReceived, totalBytes));
                //winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier().Update(updateData, L"updater");
                winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier().Update(updateData, L"updater");
            }    
        }
    );
    downloadOp.Completed([](
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Windows::Storage::Streams::IBuffer, winrt::Windows::Web::Http::HttpProgress> const& sender, 
        auto&)
    {
        auto const fileDownloadPath = getFileDownloadPath();
        auto const unzipFolder = getUnzipFolderPath();
        try
        {
            std::filesystem::create_directories(unzipFolder);
            // create a scope to release and flush the file
            {
                auto buffer = sender.GetResults();
                std::ofstream downloadFile{ fileDownloadPath, std::ios::binary };
                downloadFile.write(reinterpret_cast<char*>(buffer.data()), buffer.Length());
            }

            //unzip
            {
                wil::unique_process_information pi;
                STARTUPINFO info{ .cb = sizeof(info) };
                auto command = std::format(LR"("{}" -xf "{}")", wil::ExpandEnvironmentStringsW<std::wstring>(LR"(%windir%\system32\tar.exe)"), fileDownloadPath);

                winrt::check_bool(CreateProcessW(
                    nullptr,
                    command.data(),
                    nullptr,
                    nullptr,
                    false,
                    0,
                    nullptr,
                    unzipFolder.data(),
                    &info,
                    &pi
                ));
                
                winrt::check_bool(wil::handle_wait(pi.hProcess));
            }

            //Execute powershell
            {
                wil::unique_process_information pi;
                STARTUPINFO info{ .cb = sizeof(info) };
                auto command = std::format(
                    LR"("{}" -ExecutionPolicy ByPass -File "{}\AppPackages\WinUI3Example\WinUI3Example_1.0.0.0_x64_Release_CI2_Test\Add-AppDevPackage.ps1")",
                    wil::ExpandEnvironmentStringsW<std::wstring>(LR"(%windir%\system32\WindowsPowerShell\v1.0\powershell.exe)"),
                    unzipFolder
                );
                winrt::check_bool(CreateProcessW(
                    nullptr,
                    command.data(),
                    nullptr,
                    nullptr,
                    false,
                    0,
                    nullptr,
                    nullptr,
                    &info,
                    &pi
                ));
                ExitProcess(0);
            }
        }
        catch (...)
        {

        }
    });
}

winrt::Windows::Data::Json::JsonArray UpdateChecker::LatestReleaseResult::assets()
{
    return m_response.GetNamedArray(L"assets");
}

winrt::Windows::Data::Json::JsonObject UpdateChecker::LatestReleaseResult::findAsset(std::wstring_view name)
{
    for (auto asset : assets())
    {
        if (auto obj = asset.GetObjectW(); obj.GetNamedString(L"name") == name)
            return obj;
    }
    throw winrt::hresult_invalid_argument{ name };
}

UpdateChecker::LatestReleaseResult::LatestReleaseResult(winrt::hstring&& value) :
    m_response{ winrt::Windows::Data::Json::JsonObject::Parse(value) }
{
}

winrt::hstring UpdateChecker::LatestReleaseResult::TagName()
{
    return m_response.GetNamedString(L"tag_name");
}

winrt::hstring UpdateChecker::LatestReleaseResult::ArmRelease()
{
    return findAsset(L"WinUIEssential.Example.ARM.zip").GetNamedString(L"browser_download_url");
}

winrt::hstring UpdateChecker::LatestReleaseResult::Arm64Release()
{
    return findAsset(L"WinUIEssential.Example.ARM64.zip").GetNamedString(L"browser_download_url");
}

winrt::hstring UpdateChecker::LatestReleaseResult::X64Release()
{
    return findAsset(L"WinUIEssential.Example.x64.zip").GetNamedString(L"browser_download_url");
}

winrt::hstring UpdateChecker::LatestReleaseResult::X86Release()
{
    return findAsset(L"WinUIEssential.Example.x86.zip").GetNamedString(L"browser_download_url");
}
