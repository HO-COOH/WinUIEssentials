#include "pch.h"
#include "TaskbarIconPage.xaml.h"
#if __has_include("TaskbarIconPage.g.cpp")
#include "TaskbarIconPage.g.cpp"
#endif

#include "TaskbarIconSource.xaml.h"

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	TaskbarIconPage::TaskbarIconPage()
	{
		InitializeComponent();

		winrt::get_self<TaskbarIconSource>(NormalIconSource())->onIconSet = [this](winrt::hstring const& icon)
		{
			TaskbarIcon().IconFile(icon);
		};

		winrt::get_self<TaskbarIconSource>(LightThemeIconSource())->onIconSet = [this](winrt::hstring const& icon)
		{
			TaskbarIcon().LightThemeIconFile(icon);
		};

		winrt::get_self<TaskbarIconSource>(DarkThemeIconSource())->onIconSet = [this](winrt::hstring const& icon)
		{
			TaskbarIcon().DarkThemeIconFile(icon);
		};
	}

	void TaskbarIconPage::NormalIconAdd_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		TaskbarIcon().Show();
	}


	void TaskbarIconPage::NormalIconRemove_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		TaskbarIcon().Remove();
	}


	void TaskbarIconPage::ThemeAdaptiveIconAddButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		TaskbarIcon().Show();
	}


	void TaskbarIconPage::ThemeAdaptiveIconRemoveButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		TaskbarIcon().Remove();
	}

	void TaskbarIconPage::RadioButtons_SelectionChanged(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const&)
	{
		TaskbarIcon().Remove();
	}

	void TaskbarIconPage::MenuFlyoutItem_Click(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{

	}

	void TaskbarIconPage::MenuFlyoutItemCommand_ExecuteRequested(winrt::Microsoft::UI::Xaml::Input::XamlUICommand const& sender, winrt::Microsoft::UI::Xaml::Input::ExecuteRequestedEventArgs const& args)
	{
		//ClickedItemText().Text(arg..as<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItem>().Text());
		ClickedItemText().Text(L"Clicked");
	}
}
