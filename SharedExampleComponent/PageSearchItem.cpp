#include "pch.h"
#include "PageSearchItem.h"
#if __has_include("PageSearchItem.g.cpp")
#include "PageSearchItem.g.cpp"
#endif

namespace winrt::PackageRoot::implementation
{
	PageSearchItem::PageSearchItem(
		std::wstring_view typeName,
		std::span<std::wstring_view const> tags,
		std::wstring_view matchedTag)
		: m_typeName{ typeName }, m_name{ PageName(typeName) }, m_matchedTag{ matchedTag }
	{
		std::vector<winrt::Windows::Foundation::IInspectable> boxedTags;
		boxedTags.reserve(tags.size());

		//The matched tag leads, and stays in the same collection as the rest, because one panel
		//is what makes one flow: a row that wraps then starts at the left edge instead of under
		//a column of its own. An empty matchedTag never equals a registered tag, which is what
		//leaves every tag in place, in registration order, on a page name match
		if (!matchedTag.empty())
			boxedTags.emplace_back(winrt::box_value(winrt::hstring{ matchedTag }));

		for (auto const tag : tags)
			if (tag != matchedTag)
				boxedTags.emplace_back(winrt::box_value(winrt::hstring{ tag }));

		m_tags = winrt::single_threaded_vector(std::move(boxedTags));
	}

	winrt::hstring PageSearchItem::Name()
	{
		return m_name;
	}

	winrt::hstring PageSearchItem::MatchedTag()
	{
		return m_matchedTag;
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> PageSearchItem::Tags()
	{
		return m_tags;
	}
}
