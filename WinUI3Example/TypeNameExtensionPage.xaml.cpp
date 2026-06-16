#include "pch.h"
#include "TypeNameExtensionPage.xaml.h"
#if __has_include("TypeNameExtensionPage.g.cpp")
#include "TypeNameExtensionPage.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	void TypeNameExtensionPage::NavigationView_SelectionChanged(
		winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, 
		winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args)
	{
		//before, you usually need to create a mapping between NavigationViewItem.Tag to a winrt::xaml_typename to do Navigation
		//using {essential:TypeName} markup extension, you directly set a type on NavigationViewItem.Tag, allowing you to simplify the Navigate() call
		contentFrame().Navigate(args.SelectedItem().as<winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem>().Tag().as<winrt::Windows::UI::Xaml::Interop::TypeName>());
	}

}

