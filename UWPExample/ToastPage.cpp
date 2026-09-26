#include "pch.h"
#include "ToastPage.h"
#if __has_include("ToastPage.g.cpp")
#include "ToastPage.g.cpp"
#endif
#include "PageTagRegister.h"
#include <ToastTemplates.hpp>
#include <ToastBuilder.hpp>

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::UWPExample::implementation
{
	static PageTagRegister<ToastPage> s_tags{ L"toast", L"toastnotification", L"toasttemplates", L"notification" };


	void ToastPage::BodyTextOnlyBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier().Show(ToastTemplates::BodyTextOnly{ Body1().Text() });
	}


	void ToastPage::SingleLineHeaderWithBodyBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
			.Show(ToastTemplates::SingleLineHeaderWithBody{ Header2().Text(), Body2().Text() });
	}


	void ToastPage::TwoLineHeaderWithBodyBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
			.Show(ToastTemplates::TwoLineHeaderWithBody{ Header3().Text(), Body3().Text() });
	}


	void ToastPage::HeaderWithTwoSingleLineBody_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
			.Show(ToastTemplates::HeaderWithTwoSingleLineBody{ Header4().Text(), Body4_1().Text(), Body4_2().Text() });
	}


	void ToastPage::ImageWithBodyOnly_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
			.Show(ToastTemplates::ImageWithBodyOnly{ L"ms-appx:///Assets/Owl.jpg", Body5().Text() });
	}


	void ToastPage::ImageWithHeaderAndBodyBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
			.Show(ToastTemplates::ImageWithHeaderAndBody{ L"ms-appx:///Assets/Owl.jpg", Header6().Text(), Body6().Text() });
	}


	void ToastPage::ImageWithTwoLineHeaderAndBody_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
			.Show(ToastTemplates::ImageWithTwoLineHeaderAndBody{ L"ms-appx:///Assets/Owl.jpg", Header7().Text(), Body7().Text() });
	}


	void ToastPage::ImageWithHeaderAndTwoSingleLineBody_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
			.Show(ToastTemplates::ImageWithHeaderAndTwoSingleLineBody{ L"ms-appx:///Assets/Owl.jpg", Header8().Text(), Body8_1().Text(), Body8_2().Text() });
	}


	void ToastPage::ToastBuilderBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		using namespace ToastBuilder;

		auto const audio = getAudioSelection();
		winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
			.Show(
				Toast().Duration(Long).Scenario(Reminder).UseButtonStyle(true).Launch(L"launch arg")
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
						Action().Content(L"Single Argument").Arguments(L"singleArgument")
						.Click([this](winrt::Windows::ApplicationModel::Activation::ToastNotificationActivatedEventArgs const& args)
						{
							showArgumentToDialog(args);
						}),
						Action().Content(L"Cancel").Arguments(L"arg1=value1;arg2=value2")
						.Click([this](winrt::Windows::ApplicationModel::Activation::ToastNotificationActivatedEventArgs const& args)
						{
							showArgumentToDialog(args);
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

	void ToastPage::showArgumentToDialog(winrt::Windows::ApplicationModel::Activation::ToastNotificationActivatedEventArgs const& args)
	{
		auto const argument = args.Argument();
		ArgumentText().Text(argument);

		auto items = ArgumentsList().Items();
		items.Clear();
		//Unlike AppNotification, a UWP toast only carries the raw argument string, so split the "key=value;key=value" pairs ourselves
		for (std::wstring_view remaining{ argument }; !remaining.empty(); )
		{
			auto const pairEnd = remaining.find(L';');
			auto const pair = remaining.substr(0, pairEnd);
			auto const separator = pair.find(L'=');
			items.Append(
				winrt::box_value(
					std::format(
						L"arg: {}, value: {}",
						pair.substr(0, separator),
						separator == pair.npos ? std::wstring_view{} : pair.substr(separator + 1)
					)
				)
			);

			if (pairEnd == remaining.npos)
				break;
			remaining.remove_prefix(pairEnd + 1);
		}

		ActivationDialog().ShowAsync();
	}
}
