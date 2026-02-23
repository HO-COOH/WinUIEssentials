#pragma once
#include "AboutPage.g.h"
#include "PropertyChangeHelper.hpp"
#include "RepoInfo.h"
#include <winrt/Windows.Web.Http.h>

namespace winrt::WinUI3Example::implementation
{
    struct AboutPage : AboutPageT<AboutPage>, MvvmHelper::PropertyChangeHelper<AboutPage>
    {
        AboutPage();

        static winrt::hstring WASDKReleaseVersion();
        static winrt::hstring WASDKRuntimeVersion();
        static winrt::hstring FormatVersion(
            uint32_t major,
            uint32_t minor,
            uint32_t patch,
            uint32_t majorMinor,
            winrt::hstring const& channel
        );

        int Stars();
        int Forks();
        int Issues();
        winrt::hstring UpdatedAt();
        winrt::hstring CommitMessage();

        void SettingsCard_Click(
            winrt::Windows::Foundation::IInspectable const& sender, 
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Contributors();

        winrt::Microsoft::UI::Xaml::Visibility IsLoadingContributors();
        bool IsLoadingRepoInfo();
    private:
        std::optional<RepoInfo> m_repoInfo;
        winrt::hstring m_commitMessage;
        winrt::Windows::Web::Http::HttpClient client;
        bool m_isLoadingContributors = true;
        winrt::fire_and_forget loadContributors();
        winrt::fire_and_forget loadRepoInfos();
        winrt::fire_and_forget loadCommitMessage();

		winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> m_contributors{ nullptr };
    public:
        void Image_ImageOpened(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct AboutPage : AboutPageT<AboutPage, implementation::AboutPage>
    {
    };
}
