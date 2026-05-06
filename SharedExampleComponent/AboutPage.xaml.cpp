#include "pch.h"
#include "AboutPage.xaml.h"
#if __has_include("AboutPage.g.cpp")
#include "AboutPage.g.cpp"
#endif
#if defined Build_WinUIExample
#include <WindowsAppSDK-VersionInfo.h>
#endif

#include <winrt/Windows.System.h>
#include <winrt/Windows.ApplicationModel.h>
#include "GithubRequest.h"
#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Foundation.Metadata.h>
#if defined GetObjectW
#undef GetObjectW
#endif

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::PackageRoot::implementation
{
	AboutPage::AboutPage()
	{
		loadContributors();
		loadRepoInfos();
		loadCommitMessage();
		loadNugetInfo();

		InitializeComponent();

		auto m_compositor = winrt::WinUINamespace::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(*this).Compositor();
		addImplicitAnimationToLoading(m_compositor);
		addHeartbeatAnimation(m_compositor);
	}

	winrt::hstring AboutPage::WASDKReleaseVersion()
	{
#if defined Build_WinUIExample
		return winrt::hstring{ std::format(
			L"{}.{}.{}.{}-{}",
			WINDOWSAPPSDK_RELEASE_MAJOR,
			WINDOWSAPPSDK_RELEASE_MINOR,
			WINDOWSAPPSDK_RELEASE_PATCH,
			WINDOWSAPPSDK_RELEASE_MAJORMINOR,
			WINDOWSAPPSDK_RELEASE_CHANNEL_W
		) };
#else
		return {};
#endif
	}

	winrt::hstring AboutPage::WASDKRuntimeVersion()
	{
#ifdef Build_UWPExample
		for (auto const& dep : winrt::Windows::ApplicationModel::Package::Current().Dependencies())
		{
			auto const id = dep.Id();
			std::wstring_view name{ id.Name() };
			if (name.starts_with(L"Microsoft.UI.Xaml."))
			{
				auto const v = id.Version();
				return winrt::hstring{ std::format(L"{}.{}.{}.{}", v.Major, v.Minor, v.Build, v.Revision) };
			}
		}
		return L"";
#else
		return WINDOWSAPPSDK_RUNTIME_VERSION_DOTQUADSTRING_W;
#endif
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

	int AboutPage::Stars()
	{
		return m_repoInfo? m_repoInfo->Stars : 0;
	}

	int AboutPage::Forks()
	{
		return m_repoInfo? m_repoInfo->Forks : 0;
	}

	int AboutPage::Issues()
	{
		return m_repoInfo ? m_repoInfo->Issues : 0;
	}

	winrt::hstring AboutPage::UpdatedAt()
	{
		return m_repoInfo ? m_repoInfo->UpdatedAt : L"";
	}

	winrt::hstring AboutPage::CommitMessage()
	{
		return m_commitMessage;
	}

	winrt::hstring AboutPage::WinUINugetPackageVersion()
	{
		return m_winuiNugetPackageVersion;
	}

	int AboutPage::WinUINugetPackageDownloads()
	{
		return m_winuiNugetPackageDownloads;
	}

	winrt::hstring AboutPage::UWPNugetPackageVersion()
	{
		return m_uwpNugetPackageVersion;
	}

	int AboutPage::UWPNugetPackageDownloads()
	{
		return m_uwpNugetPackageDownloads;
	}

	void AboutPage::SettingsCard_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Windows::System::Launcher::LaunchUriAsync(winrt::Windows::Foundation::Uri{ L"https://github.com/HO-COOH/WinUIEssentials" });
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> AboutPage::Contributors()
	{
		return m_contributors;
	}

	winrt::WinUINamespace::UI::Xaml::Visibility AboutPage::IsLoadingContributors()
	{
		return m_isLoadingContributors ? winrt::WinUINamespace::UI::Xaml::Visibility::Visible : winrt::WinUINamespace::UI::Xaml::Visibility::Collapsed;
	}

	bool AboutPage::IsLoadingRepoInfo()
	{
		return !m_repoInfo.has_value();
	}

	winrt::fire_and_forget AboutPage::loadContributors()
	{
		try
		{
			auto strongThis = get_strong();
			auto result = co_await client.SendRequestAsync(GithubRequest{ L"https://api.github.com/repos/HO-COOH/WinUIEssentials/contributors" });
			auto resultStr = co_await result.Content().ReadAsStringAsync();

			auto contributorsJsonArray = winrt::Windows::Data::Json::JsonArray::Parse(resultStr);
			std::vector<winrt::Windows::Foundation::IInspectable> contributors;
			std::ranges::transform(
				contributorsJsonArray,
				std::back_inserter(contributors),
				[](auto&& jsonObj) {return winrt::PackageRoot::ContributorItem{ jsonObj.GetObject() }; }
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
		winrt::WinUINamespace::UI::Xaml::VisualStateManager::GoToState(*this, L"GetContributorFailed", false);
	}

	winrt::fire_and_forget AboutPage::loadRepoInfos()
	{
		try
		{
			auto strongThis = get_strong();
			auto result = co_await client.SendRequestAsync(GithubRequest{ L"https://api.github.com/repos/HO-COOH/WinUIEssentials" });
			auto resultStr = co_await result.Content().ReadAsStringAsync();

			m_repoInfo.emplace(winrt::Windows::Data::Json::JsonObject::Parse(resultStr));
			raisePropertyChange(L"IsLoadingRepoInfo");
			raisePropertyChange(L"Stars");
			raisePropertyChange(L"Forks");
			raisePropertyChange(L"Issues");
			raisePropertyChange(L"UpdatedAt");
		}
		catch (...)
		{
		}
	}

	winrt::fire_and_forget AboutPage::loadCommitMessage()
	{
		try
		{
			auto strongThis = get_strong();
			auto result = co_await client.SendRequestAsync(GithubRequest{ L"https://api.github.com/repos/HO-COOH/WinUIEssentials/commits?per_page=1" });
			auto resultStr = co_await result.Content().ReadAsStringAsync();
			m_commitMessage = winrt::Windows::Data::Json::JsonArray::Parse(resultStr).GetAt(0).GetObject().GetNamedObject(L"commit").GetNamedString(L"message");
			raisePropertyChange(L"CommitMessage");
		}
		catch (...)
		{
		}
	}

	winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Data::Json::JsonObject> AboutPage::getNugetInfoFromId(std::wstring_view endPoint, std::wstring_view packageId)
	{
		auto url = std::format(L"{}?q=packageid:{}", endPoint, packageId);
		auto nugetInfo = co_await client.GetStringAsync(winrt::Windows::Foundation::Uri{ url });
		co_return winrt::Windows::Data::Json::JsonObject::Parse(nugetInfo).GetNamedArray(L"data").GetAt(0).GetObject();
	}

	winrt::fire_and_forget AboutPage::loadNugetInfoForWinUIPackage(std::wstring_view endPoint)
	{
		auto data = co_await getNugetInfoFromId(endPoint, L"WinUIEssential.WinUI3");
		m_winuiNugetPackageVersion = data.GetNamedString(L"version");
		m_winuiNugetPackageDownloads = data.GetNamedNumber(L"totalDownloads");
		raisePropertyChange(L"WinUINugetPackageVersion");
		raisePropertyChange(L"WinUINugetPackageDownloads");
	}

	winrt::fire_and_forget AboutPage::loadNugetInfoForUWPPackage(std::wstring_view endPoint)
	{
		auto data = co_await getNugetInfoFromId(endPoint, L"WinUIEssential.UWP");
		m_uwpNugetPackageVersion = data.GetNamedString(L"version");
		m_uwpNugetPackageDownloads = data.GetNamedNumber(L"totalDownloads");
		raisePropertyChange(L"UWPNugetPackageVersion");
		raisePropertyChange(L"UWPNugetPackageDownloads");
	}

	winrt::fire_and_forget AboutPage::loadNugetInfo()
	{
		try
		{
			auto strongThis = get_strong();
			auto result = co_await client.GetStringAsync(winrt::Windows::Foundation::Uri{ L"https://nuget.azure.cn/v3/index.json" });
			auto resources = winrt::Windows::Data::Json::JsonObject::Parse(result).GetNamedArray(L"resources");
			for (auto resource : resources)
			{
				auto object = resource.GetObject();
				if (object.GetNamedString(L"@type") != L"SearchQueryService")
					continue;
				
				auto endPoint = object.GetNamedString(L"@id");
				loadNugetInfoForWinUIPackage(endPoint);
				loadNugetInfoForUWPPackage(endPoint);
			}
		}
		catch (...)
		{
		}
	}

	void AboutPage::addImplicitAnimationToLoading(winrt::WinUINamespace::UI::Composition::Compositor const& compositor)
	{
		auto opacityAnimation = compositor.CreateScalarKeyFrameAnimation();
		opacityAnimation.InsertKeyFrame(0.0f, 1.0f);
		opacityAnimation.InsertKeyFrame(1.0f, 0.0f);
		opacityAnimation.Target(L"Opacity");

		winrt::WinUINamespace::UI::Composition::CompositionEasingFunction accelerateEasing{ nullptr };
#ifdef Build_UWPExample
		if (winrt::Windows::Foundation::Metadata::ApiInformation::IsMethodPresent(
			L"Windows.UI.Composition.CompositionEasingFunction",
			L"CreateExponentialEasingFunction"))
		{
			accelerateEasing = winrt::WinUINamespace::UI::Composition::CompositionEasingFunction::CreateExponentialEasingFunction(
				compositor,
				winrt::WinUINamespace::UI::Composition::CompositionEasingFunctionMode::In,
				4.5f);
		}
		else
		{
			accelerateEasing = compositor.CreateCubicBezierEasingFunction({ 0.7f, 0.0f }, { 0.84f, 0.0f });
		}
#else
		accelerateEasing = winrt::WinUINamespace::UI::Composition::CompositionEasingFunction::CreateExponentialEasingFunction(
			compositor,
			winrt::WinUINamespace::UI::Composition::CompositionEasingFunctionMode::In,
			4.5f);
#endif

		auto offsetAnimation = compositor.CreateScalarKeyFrameAnimation();
		offsetAnimation.InsertKeyFrame(0.f, 0.f);
		offsetAnimation.InsertExpressionKeyFrame(1.f, L"this.Target.Size.X / 3", accelerateEasing);
		offsetAnimation.Target(L"Offset.X");

		auto group = compositor.CreateAnimationGroup();
		group.Add(opacityAnimation);
		group.Add(offsetAnimation);

		winrt::WinUINamespace::UI::Xaml::Hosting::ElementCompositionPreview::SetImplicitHideAnimation(LoadingContributorPanel(), group);
	}

	void AboutPage::addHeartbeatAnimation(winrt::WinUINamespace::UI::Composition::Compositor const& compositor)
	{
		constexpr auto overshooot = 0.15f;

		auto scaleAnimation = compositor.CreateVector2KeyFrameAnimation();
		winrt::WinUINamespace::UI::Composition::CompositionEasingFunction bounceEasing{ nullptr };
#ifdef Build_UWPExample
		if (winrt::Windows::Foundation::Metadata::ApiInformation::IsMethodPresent(
			L"Windows.UI.Composition.CompositionEasingFunction",
			L"CreateBackEasingFunction"))
		{
			bounceEasing = winrt::WinUINamespace::UI::Composition::CompositionEasingFunction::CreateBackEasingFunction(
				compositor,
				winrt::WinUINamespace::UI::Composition::CompositionEasingFunctionMode::Out,
				1);
		}
		else
		{
			bounceEasing = compositor.CreateCubicBezierEasingFunction({ 0.34f, 1.56f }, { 0.64f, 1.0f });
		}
#else
		bounceEasing = winrt::WinUINamespace::UI::Composition::CompositionEasingFunction::CreateBackEasingFunction(
			compositor,
			winrt::WinUINamespace::UI::Composition::CompositionEasingFunctionMode::Out,
			1);
#endif

		scaleAnimation.InsertKeyFrame(0.15f, { 1.f + overshooot, 1.f + overshooot }, bounceEasing);
		scaleAnimation.InsertKeyFrame(0.3f, { 1.f - overshooot / 2.f, 1.f - overshooot / 2.f }, bounceEasing);
		scaleAnimation.InsertKeyFrame(0.45f, { 1.f, 1.f }, bounceEasing);
		scaleAnimation.IterationBehavior(winrt::WinUINamespace::UI::Composition::AnimationIterationBehavior::Forever);
		scaleAnimation.Duration(std::chrono::milliseconds{ 1500 });
		scaleAnimation.Target(L"Scale.XY");

		auto centerAnimation = compositor.CreateExpressionAnimation(L"Vector2(this.Target.Size.X / 2.0f, this.Target.Size.Y / 2.0f)");

		auto visual = winrt::WinUINamespace::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(HeartIcon());
		visual.StartAnimation(L"CenterPoint.XY", centerAnimation);
		visual.StartAnimation(L"Scale.XY", scaleAnimation);
	}

	void AboutPage::Image_ImageOpened(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const&)
	{
#if defined Build_WinUIExample
		sender.as<winrt::WinUINamespace::UI::Xaml::FrameworkElement>().Parent().as<winrt::WinUI3Package::Shimmer>().IsLoading(false);
#else
		sender.as<winrt::WinUINamespace::UI::Xaml::FrameworkElement>().Parent().as<winrt::UWPPackage::Shimmer>().IsLoading(false);
#endif
	}
}
