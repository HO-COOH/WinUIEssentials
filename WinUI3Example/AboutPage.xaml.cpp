#include "pch.h"
#include "AboutPage.xaml.h"
#if __has_include("AboutPage.g.cpp")
#include "AboutPage.g.cpp"
#endif
#include <WindowsAppSDK-VersionInfo.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.Web.Http.h>
#include <winrt/Windows.Web.Http.Headers.h>
#include <winrt/Windows.Data.Json.h>

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	AboutPage::AboutPage()
	{
		loadContributors();
	}

	winrt::hstring AboutPage::WASDKReleaseVersion()
	{
		return winrt::hstring{ std::format(
			L"{}.{}.{}.{}-{}",
			WINDOWSAPPSDK_RELEASE_MAJOR,
			WINDOWSAPPSDK_RELEASE_MINOR,
			WINDOWSAPPSDK_RELEASE_PATCH,
			WINDOWSAPPSDK_RELEASE_MAJORMINOR,
			WINDOWSAPPSDK_RELEASE_CHANNEL_W
		) };
	}

	winrt::hstring AboutPage::WASDKRuntimeVersion()
	{
		return WINDOWSAPPSDK_RUNTIME_VERSION_DOTQUADSTRING_W;
	}

	winrt::hstring AboutPage::FormatVersion(
		uint32_t major, 
		uint32_t minor, 
		uint32_t patch,
		uint32_t majorMinor,
		winrt::hstring const& channel)
	{
		return winrt::hstring{ std::format(
			L"{}.{}.{}.{}-{}",
			major,
			minor,
			patch,
			majorMinor,
			channel
		) };
	}

	void AboutPage::SettingsCard_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Windows::System::Launcher::LaunchUriAsync(winrt::Windows::Foundation::Uri{ L"https://github.com/HO-COOH/WinUIEssentials" });
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> AboutPage::Contributors()
	{
		return m_contributors;
	}

	winrt::Microsoft::UI::Xaml::Visibility AboutPage::IsLoadingContributors()
	{
		return m_isLoadingContributors ? winrt::Microsoft::UI::Xaml::Visibility::Visible : winrt::Microsoft::UI::Xaml::Visibility::Collapsed;
	}

	winrt::fire_and_forget AboutPage::loadContributors()
	{
		try
		{
			winrt::Windows::Web::Http::HttpClient client;
			winrt::Windows::Web::Http::HttpRequestMessage message
			{
				winrt::Windows::Web::Http::HttpMethod::Get(),
				winrt::Windows::Foundation::Uri{ L"https://api.github.com/repos/HO-COOH/WinUIEssentials/contributors" }
			};
			message.Headers().Append(L"User-Agent", L"WinUI3ExampleApp");
			auto result = co_await client.SendRequestAsync(message);
			auto resultStr = co_await result.Content().ReadAsStringAsync();

			auto contributorsJsonArray = winrt::Windows::Data::Json::JsonArray::Parse(resultStr);
			std::vector<winrt::Windows::Foundation::IInspectable> contributors;
			std::ranges::transform(
				contributorsJsonArray,
				std::back_inserter(contributors),
				[](auto&& jsonObj) {return winrt::WinUI3Example::ContributorItem{ jsonObj.GetObjectW() }; }
			);
			m_contributors = winrt::single_threaded_vector(std::move(contributors));
			m_isLoadingContributors = false;
			raisePropertyChange(L"Contributors");
			raisePropertyChange(L"IsLoadingContributors");
			co_return;
		}
		catch (winrt::hresult_error const& e)
		{
			GetContributorFailedBar().Message(GetContributorFailedBar().Message() + e.message());
		}
		catch (...)
		{
		}
		m_isLoadingContributors = false;
		raisePropertyChange(L"IsLoadingContributors");
		winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"GetContributorFailed", false);
	}

	void winrt::WinUI3Example::implementation::AboutPage::Image_ImageOpened(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		sender.as<winrt::Microsoft::UI::Xaml::FrameworkElement>().Parent().as<winrt::WinUI3Package::Shimmer>().IsLoading(false);
	}

}
