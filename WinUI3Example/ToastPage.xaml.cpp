// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "ToastPage.xaml.h"
#if __has_include("ToastPage.g.cpp")
#include "ToastPage.g.cpp"
#endif
#include <ToastTemplates.hpp>
#include <winrt/Microsoft.Windows.AppNotifications.Builder.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    ToastPage::ToastPage()
    {
        InitializeComponent();
    }

	void ToastPage::BodyTextOnlyBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier().Show(ToastTemplates::BodyTextOnly{ Body1().Text() });
	}


	void ToastPage::SingleLineHeaderWithBodyBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
			.Show(ToastTemplates::SingleLineHeaderWithBody{ Header2().Text(), Body2().Text() });
	}


	void ToastPage::TwoLineHeaderWithBodyBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
			.Show(ToastTemplates::TwoLineHeaderWithBody{ Header3().Text(), Body3().Text() });
	}


	void ToastPage::HeaderWithTwoSingleLineBody_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
			.Show(ToastTemplates::HeaderWithTwoSingleLineBody{ Header4().Text(), Body4_1().Text(), Body4_2().Text() });
	}


	void ToastPage::ImageWithBodyOnly_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
			.Show(ToastTemplates::ImageWithBodyOnly{ L"ms-appx:///Assets/Windows 11.png", Body5().Text() });
	}


	void ToastPage::ImageWithHeaderAndBodyBtn_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
			.Show(ToastTemplates::ImageWithHeaderAndBody{ L"ms-appx:///Assets/Windows 11.png", Header6().Text(), Body6().Text() });
	}


	void ToastPage::ImageWithTwoLineHeaderAndBody_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
			.Show(ToastTemplates::ImageWithTwoLineHeaderAndBody{ L"ms-appx:///Assets/Windows 11.png", Header7().Text(), Body7().Text() });
	}


	void ToastPage::ImageWithHeaderAndTwoSingleLineBody_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
			.Show(ToastTemplates::ImageWithHeaderAndTwoSingleLineBody{ L"ms-appx:///Assets/Windows 11.png", Header8().Text(), Body8_1().Text(), Body8_2().Text() });
	}


	void ToastPage::ToastBuilderBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		//winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder builder;
		//winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton button{ L"Content" };
		//button.AddArgument(L"arg1", L"value1");
		//button.AddArgument(L"arg2", L"value2");
		//builder.AddButton(button);
		//auto xml = builder.BuildNotification().Payload();
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
						.Click([this](winrt::Microsoft::Windows::AppNotifications::AppNotificationActivatedEventArgs const& args)
						{
							DispatcherQueue().TryEnqueue([this, args] {
								showArgumentToDialog(args);
							});
						}),
						Action().Content(L"Cancel").Arguments(L"arg1=value1;arg2=value2")
						.Click([this](winrt::Microsoft::Windows::AppNotifications::AppNotificationActivatedEventArgs const& args)
						{
							DispatcherQueue().TryEnqueue([this, args] {
								showArgumentToDialog(args);
							});
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

	void ToastPage::showArgumentToDialog(winrt::Microsoft::Windows::AppNotifications::AppNotificationActivatedEventArgs const& args)
	{
		ArgumentText().Text(args.Argument());

		auto items = ArgumentsList().Items();
		items.Clear();
		for (auto pair : args.Arguments())
		{
			items.Append(winrt::box_value(std::format(L"arg: {}, value: {}", pair.Key(), pair.Value())));
		}

		ActivationDialog().ShowAsync();
	}
}
