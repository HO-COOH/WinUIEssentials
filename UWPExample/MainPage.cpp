#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"


namespace winrt::UWPExample::implementation
{
	MainPage::MainPage()
	{
		winrt::Windows::ApplicationModel::Core::CoreApplication::GetCurrentView().TitleBar().ExtendViewIntoTitleBar(true);
		auto titlebar = winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().TitleBar();
		titlebar.ButtonBackgroundColor(winrt::Windows::UI::Colors::Transparent());
		titlebar.ButtonInactiveBackgroundColor(winrt::Windows::UI::Colors::Transparent());
		//InitializeComponent();
		//winrt::Windows::UI::Xaml::Window::Current().SetTitleBar(AppTitleBar());
	}

	void MainPage::NavigationView_SelectionChanged(
		winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, 
		winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args)
	{
		if (args.IsSettingsSelected())
		{
			ContentFrame().Navigate(winrt::xaml_typename<UWPExample::AboutPage>());
			return;
		}

		if (auto tag = args.SelectedItemContainer().Tag())
			ContentFrame().Navigate(winrt::unbox_value<winrt::Windows::UI::Xaml::Interop::TypeName>(tag));
	}

	winrt::hstring MainPage::WindowTitle()
	{
#if (defined DEBUG) || (defined _DEBUG)
		return L"WinUIEssentials.UWPExample(Dev)";
#else
		return L"WinUIEssentials.UWPExample";
#endif
	}


	void MainPage::FooterMenuItemsHost_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		auto itemsRepeater = sender.as<winrt::Microsoft::UI::Xaml::Controls::ItemsRepeater>();
		auto items = itemsRepeater.ItemsSource().as<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable>>();
		auto settingsButton = items.GetAt(0).as<winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem>();
		settingsButton.Content(winrt::box_value(L"About"));
	}

}
