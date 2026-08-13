#include "pch.h"
#include "NavigationHelper.h"
#include <algorithm>
#include <ranges>
#include "PageTag.h"
#include "PageSearchItem.h"
#include <cwctype>

namespace NavigationViewUtils
{
	winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem FindItemByTag(
		winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> const& menuItems, 
		winrt::hstring const& typeName
	)
	{
		for (auto const& menuItem : menuItems)
		{
			//Headers, separators and the footer panel are in the same collection but carry no page
			auto const item = menuItem.try_as<winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem>();
			if (!item)
				continue;

			if (auto const tag = item.Tag();
				tag && winrt::unbox_value<winrt::Windows::UI::Xaml::Interop::TypeName>(tag).Name == typeName)
				return item;

			//A category item can be a page as well as a parent, hence the check above before descending
			if (auto const found = FindItemByTag(item.MenuItems(), typeName))
				return found;
		}

		return nullptr;
	}
}

static wchar_t ToLower(wchar_t c)
{
	return static_cast<wchar_t>(std::towlower(c));
}

void NavigationHelper::normalizeQuery(winrt::hstring const& query)
{
	m_query.clear();
	std::ranges::transform(
		query | std::views::filter([](wchar_t c) { return c != L' '; }),
		std::back_inserter(m_query),
		ToLower
	);
}

bool NavigationHelper::OnAutoSuggestBoxQuerySubmitted(winrt::WinUINamespace::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs const& args, winrt::Microsoft::UI::Xaml::Controls::NavigationView const& navigationView)
{
	auto const item = args.ChosenSuggestion().try_as<winrt::PackageRoot::PageSearchItem>();
	if (!item)
		return false;

	winrt::hstring const typeName{ winrt::get_self<winrt::PackageRoot::implementation::PageSearchItem>(item)->TypeName() };
	//Selecting the pane item moves the indicator onto it and raises SelectionChanged, which does the
	//navigating, so arriving by search leaves the pane exactly as clicking it would have
	if (auto const pageItem = NavigationViewUtils::FindItemByTag(navigationView.MenuItems(), typeName))
	{
		navigationView.SelectedItem(pageItem);
		return true;
	}

	//A registered page with no pane item is not navigated to, because there would be no indicator
	//to move onto it
	return false;
}

void NavigationHelper::OnAutoSuggestBoxTextChanged(winrt::WinUINamespace::UI::Xaml::Controls::AutoSuggestBox const& sender)
{
	normalizeQuery(sender.Text());
	if (m_query.empty())
	{
		sender.ItemsSource(nullptr);
		return;
	}

	m_searchResult.clear();
	for (auto const [Typename, Tags] : PageTag::Registry())
	{
		//try match page name
		if (!std::ranges::search(winrt::PackageRoot::implementation::PageSearchItem::PageName(Typename), m_query, {}, ToLower).empty())
		{
			m_searchResult.emplace_back(winrt::make<winrt::PackageRoot::implementation::PageSearchItem>(Typename, Tags, std::wstring_view{}));
			continue;
		}

		//try match tags
		auto const matched = std::ranges::find_if(
			Tags,
			[this](std::wstring_view tag) { return tag.find(m_query) != std::wstring_view::npos; }
		);

		if (matched != Tags.end())
			m_searchResult.emplace_back(winrt::make<winrt::PackageRoot::implementation::PageSearchItem>(Typename, Tags, *matched));
	}

	sender.ItemsSource(winrt::single_threaded_vector(std::move(m_searchResult)));
}
