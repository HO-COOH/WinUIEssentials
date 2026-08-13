#pragma once

#include "PageSearchItem.g.h"
#include <span>
#include <string_view>

namespace winrt::PackageRoot::implementation
{
    struct PageSearchItem : PageSearchItemT<PageSearchItem>
    {
        PageSearchItem() = default;
        PageSearchItem(
            std::wstring_view typeName,
            std::span<std::wstring_view const> tags,
            std::wstring_view matchedTag
        );

        winrt::hstring Name();

        //The tag the query matched, which is also the first of Tags, so an accent pill
        //drawn over that first item marks it. Empty when the page was found by its name instead
        winrt::hstring MatchedTag();
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Tags();
        constexpr std::wstring_view TypeName() const 
        { 
            return m_typeName; 
        }

        //Get pageName from TypeName
        static constexpr std::wstring_view PageName(std::wstring_view typeName)
        {
            typeName.remove_prefix(typeName.rfind(L'.') + 1);	//npos + 1 == 0, so an unqualified name survives
            if (typeName.ends_with(L"Page"))
                typeName.remove_suffix(4);
            return typeName;
        }

    private:
        std::wstring_view m_typeName;
        winrt::hstring m_name;
        winrt::hstring m_matchedTag;
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> m_tags{ nullptr };
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct PageSearchItem : PageSearchItemT<PageSearchItem, implementation::PageSearchItem>
    {
    };
}
