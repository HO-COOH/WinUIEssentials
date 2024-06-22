#include "pch.h"
#include "ToastPage.h"
#if __has_include("ToastPage.g.cpp")
#include "ToastPage.g.cpp"
#endif
#include <ToastTemplates.hpp>
#include <ToastBuilder.hpp>

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::UWPExample::implementation
{
	void ToastPage::BodyTextOnlyBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier().Show(ToastTemplates::BodyTextOnly{ L"bodyText" });
	}


	void ToastPage::SingleLineHeaderWithBodyBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		//winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
		//	.Show(ToastTemplates::SingleLineHeaderWithBody{ L"Header", L"Body" });
	}


	void ToastPage::TwoLineHeaderWithBodyBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		//winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
		//	.Show(ToastTemplates::TwoLineHeaderWithBody{ L"Very looooooooooooooooooooooooooong two line header", L"Body" });
	}


	void ToastPage::HeaderWithTwoSingleLineBody_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		//winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
		//	.Show(ToastTemplates::HeaderWithTwoSingleLineBody{ L"Header", L"body#1", L"body#2" });
	}


	void ToastPage::ImageWithBodyOnly_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		//winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
		//	.Show(ToastTemplates::ImageWithBodyOnly{ L"ms-appx:///Assets/Windows 11.png", L"Header" });
	}


	void ToastPage::ImageWithHeaderAndBodyBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		//winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
		//	.Show(ToastTemplates::ImageWithHeaderAndBody{ L"ms-appx:///Assets/Windows 11.png", L"Header", L"body" });
	}


	void ToastPage::ImageWithTwoLineHeaderAndBody_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		//winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
		//	.Show(ToastTemplates::ImageWithTwoLineHeaderAndBody{ L"ms-appx:///Assets/Windows 11.png", L"Very looooooooooooooooooooooooooong two line header", L"body" });
	}


	void ToastPage::ImageWithHeaderAndTwoSingleLineBody_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		//winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
		//	.Show(ToastTemplates::ImageWithHeaderAndTwoSingleLineBody{ L"ms-appx:///Assets/Windows 11.png", L"Header", L"body#1", L"body#2" });
	}


	void ToastPage::ToastBuilderBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		using namespace ToastBuilder;

		auto const audio = getAudioSelection();
		winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
			.Show(
				Toast().Duration(Long).Scenario(Reminder).UseButtonStyle(true)
				(
					Visual()
					(
						Binding().Template(L"ToastText04")
						(
							Text().Id(1)(L"headline"),
							Text().Id(2)(L"body text1"),
							Text().Id(3)(L"body text2")
						)
					),
					Actions()
					(
						Action().Content(L"Accept").Arguments(L"accept")
						.Click([this](winrt::Windows::ApplicationModel::Activation::ToastNotificationActivatedEventArgs args)
						{
							ArgumentText().Text(args.Argument());
							ActivationDialog().ShowAsync();
						}),
						Action().Content(L"Cancel").Arguments(L"cancel")
						.Click([this](winrt::Windows::ApplicationModel::Activation::ToastNotificationActivatedEventArgs args)
						{
							ArgumentText().Text(args.Argument());
							ActivationDialog().ShowAsync();
						})
					),
					Audio().Src(audio.data()).Loop(LoopingToggle().IsOn())
				)
			);
	}
	winrt::hstring ToastPage::getAudioSelection()
	{
		if (auto selectedItem = AudioComboBox().SelectedItem())
			return winrt::unbox_value<winrt::hstring>(selectedItem).data();
		return {};
	}
}
