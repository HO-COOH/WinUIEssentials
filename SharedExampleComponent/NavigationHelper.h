#pragma once
#include <winrt/base.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>

namespace NavigationViewUtils
{
	//Recursively find a navigationViewItem for a typename
	winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem FindItemByTag(
		winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> const& menuItems,
		winrt::hstring const& typeName
	);
}

class NavigationHelper
{
	std::wstring m_query;
	std::vector<winrt::Windows::Foundation::IInspectable> m_searchResult;

	void normalizeQuery(winrt::hstring const& query);
public:

	//return navigation succeeded
	bool OnAutoSuggestBoxQuerySubmitted(
		winrt::WinUINamespace::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs const& args,
		winrt::Microsoft::UI::Xaml::Controls::NavigationView const& navigationView
	);

	void OnAutoSuggestBoxTextChanged(winrt::WinUINamespace::UI::Xaml::Controls::AutoSuggestBox const& sender);
};