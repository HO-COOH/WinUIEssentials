#include "pch.h"
#include "ModernStandardWindowContextMenuPage.xaml.h"
#if __has_include("ModernStandardWindowContextMenuPage.g.cpp")
#include "ModernStandardWindowContextMenuPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	void ModernStandardWindowContextMenuPage::StandardWindowButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::StandardWindowWithMenu{}.Activate();
	}

	void ModernStandardWindowContextMenuPage::NonResizableWindowButton_Click(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		winrt::WinUI3Example::NonResizableWindowWithMenu{}.Activate();
	}


	void ModernStandardWindowContextMenuPage::EssentialWindowWithMenuButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::EssentialWindowWithMenu{}.Activate();
	}


	void ModernStandardWindowContextMenuPage::CustomWindowMenuButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::WindowWithCustomMenu{}.Activate();
	}

	std::vector<winrt::Windows::Foundation::IInspectable> ModernStandardWindowContextMenuPage::Components()
	{
		return std::vector
		{
			winrt::box_value(winrt::WinUI3Example::ComponentInfo{.Name = L"ModernStandardWindowContextMenu", .Xaml = true, .Idl = true, .H = true, .Cpp = true}),
			winrt::box_value(winrt::WinUI3Example::ComponentInfo{.Name = L"WindowContextMenu", .Xaml = false, .Idl = true, .H = true, .Cpp = true}),
		};
	}
}
