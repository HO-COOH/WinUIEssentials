#include "pch.h"
#include "TaskbarIconPage.xaml.h"
#if __has_include("TaskbarIconPage.g.cpp")
#include "TaskbarIconPage.g.cpp"
#endif

#include "TaskbarIconSource.xaml.h"
#include "MainWindow.xaml.h"

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	TaskbarIconPage::TaskbarIconPage()
	{
		InitializeComponent();
	}

	void TaskbarIconPage::NormalIconAdd_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		if (!m_isNormalIconWithXamlMenuAdded)
		{
			TaskbarIcon().IconFile(winrt::get_self<implementation::TaskbarIconSource>(NormalIconSource())->IconFile);
			TaskbarIcon().Show();
			isNormalIconWithXamlMenuAdded(true);
		}
		else
		{
			TaskbarIcon().Remove();
			isNormalIconWithXamlMenuAdded(false);
		}
	}


	void TaskbarIconPage::ThemeAdaptiveIconAddButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		if (!m_isThemeAdaptiveIconWithXamlMenuAdded)
		{
			TaskbarIcon().LightThemeIconFile(winrt::get_self<implementation::TaskbarIconSource>(LightThemeIconSource())->IconFile);
			TaskbarIcon().DarkThemeIconFile(winrt::get_self<implementation::TaskbarIconSource>(DarkThemeIconSource())->IconFile);
			TaskbarIcon().Show();
			isThemeAdaptiveIconWithXamlMenuAdded(true);
		}
		else
		{
			TaskbarIcon().Remove();
			isThemeAdaptiveIconWithXamlMenuAdded(false);
		}
	}


	void TaskbarIconPage::MenuFlyoutItem_Click(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		if (auto xamlFlyoutItem = sender.as<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItem>())
			ClickedItemText().Text(std::format(L"Type: {}, item: {}", winrt::get_class_name(xamlFlyoutItem), xamlFlyoutItem.Text()));
	}

	void TaskbarIconPage::TaskbarIcon_LeftPressed()
	{
		++m_leftPressedCount;
		raisePropertyChange(L"LeftPressedCount");
	}

	void TaskbarIconPage::TaskbarIcon_LeftDoublePressed()
	{
		++m_leftDoublePressedCount;
		raisePropertyChange(L"LeftDoublePressedCount");
	}

	void TaskbarIconPage::TaskbarIcon_RightPressed()
	{
		++m_rightPressedCount;
		raisePropertyChange(L"RightPressedCount");
	}

	void TaskbarIconPage::TaskbarIcon_PointerHover()
	{
		++m_hoverCount;
		raisePropertyChange(L"HoverCount");
	}


	void TaskbarIconPage::PopupMenuFlyoutItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		if (auto popupFlyoutItem = sender.as<winrt::WinUI3Package::PopupMenuFlyoutItem>())
		{
			ClickedItemText().Text(std::format(L"Type: {}, item: {}", winrt::get_class_name(sender), popupFlyoutItem.Text()));
			popupFlyoutItem.Text(L"Clicked");
		}
	}

	void TaskbarIconPage::NormalIconWithPopupMenuAdd_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		if (!m_isNormalIconWithPopupMenuAdded)
		{
			TaskbarIconWithPopupMenu().IconFile(winrt::get_self<implementation::TaskbarIconSource>(NormalIconSource())->IconFile);
			TaskbarIconWithPopupMenu().Show();
			isNormalIconWithPopupMenuAdded(true);
		}
		else
		{
			TaskbarIconWithPopupMenu().Remove();
			isNormalIconWithPopupMenuAdded(false);
		}
	}

	bool TaskbarIconPage::IsNormalIconWithXamlMenuAdded()
	{
		return m_isNormalIconWithXamlMenuAdded;
	}

	bool TaskbarIconPage::IsNormalIconWithPopupMenuAdded()
	{
		return m_isNormalIconWithPopupMenuAdded;
	}

	bool TaskbarIconPage::IsThemeAdaptiveIconWithXamlMenuAdded()
	{
		return m_isThemeAdaptiveIconWithXamlMenuAdded;
	}

	bool TaskbarIconPage::IsThemeAdaptiveIconWithPopupMenuAdded()
	{
		return m_isThemeAdaptiveIconWithPopupMenuAdded;
	}

	bool TaskbarIconPage::BoolAnd(bool v1, bool v2)
	{
		return v1 && v2;
	}

	bool TaskbarIconPage::NegateBool(bool v)
	{
		return !v;
	}

	int TaskbarIconPage::LeftPressedCount()
	{
		return m_leftPressedCount;
	}

	int TaskbarIconPage::LeftDoublePressedCount()
	{
		return m_leftDoublePressedCount;
	}

	int TaskbarIconPage::HoverCount()
	{
		return m_hoverCount;;
	}

	int TaskbarIconPage::RightPressedCount()
	{
		return m_rightPressedCount;
	}

	void TaskbarIconPage::isNormalIconWithXamlMenuAdded(bool value)
	{
		if (value == m_isNormalIconWithXamlMenuAdded)
			return;

		m_isNormalIconWithXamlMenuAdded = value;
		raisePropertyChange(L"IsNormalIconAdded");
	}

	void TaskbarIconPage::isNormalIconWithPopupMenuAdded(bool value)
	{
		if (value == m_isNormalIconWithPopupMenuAdded)
			return;

		m_isNormalIconWithPopupMenuAdded = value;
		raisePropertyChange(L"IsNormalIconWithPopupMenuAdded");
	}

	void TaskbarIconPage::isThemeAdaptiveIconWithXamlMenuAdded(bool value)
	{
		if (value == m_isThemeAdaptiveIconWithXamlMenuAdded)
			return;

		m_isThemeAdaptiveIconWithXamlMenuAdded = value;
		raisePropertyChange(L"IsThemeAdaptiveIconAdded");
	}

	void TaskbarIconPage::isThemeAdaptiveIconWithPopupMenuAdded(bool value)
	{
		if (value == m_isThemeAdaptiveIconWithPopupMenuAdded)
			return;

		m_isThemeAdaptiveIconWithPopupMenuAdded = value;
		raisePropertyChange(L"IsThemeAdaptiveIconWithPopupMenuAdded");
	}

	void TaskbarIconPage::ThemeAdaptiveIconWithPopupMenuAdd_Click(
		winrt::Windows::Foundation::IInspectable const& , 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		if (!m_isThemeAdaptiveIconWithPopupMenuAdded)
		{
			TaskbarIconWithPopupMenu().LightThemeIconFile(winrt::get_self<implementation::TaskbarIconSource>(LightThemeIconSource())->IconFile);
			TaskbarIconWithPopupMenu().DarkThemeIconFile(winrt::get_self<implementation::TaskbarIconSource>(DarkThemeIconSource())->IconFile);
			TaskbarIconWithPopupMenu().Show();
			isThemeAdaptiveIconWithPopupMenuAdded(true);
		}
		else
		{
			TaskbarIconWithPopupMenu().Remove();
			isThemeAdaptiveIconWithPopupMenuAdded(false);
		}
	}

	void TaskbarIconPage::ToggleSwitch_Toggled(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		auto toggleSwitch = sender.as<winrt::Microsoft::UI::Xaml::Controls::ToggleSwitch>();
		if (toggleSwitch.IsOn())
			winrt::get_self<MainWindow>(MainWindow::MainWindowInstance)->MainIcon().Show();
		else
			winrt::get_self<MainWindow>(MainWindow::MainWindowInstance)->MainIcon().Remove();
	}

}

