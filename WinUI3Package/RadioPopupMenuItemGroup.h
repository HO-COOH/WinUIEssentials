#pragma once
#include <unordered_map>
#include <winrt/base.h>

namespace winrt::WinUI3Package 
{
	struct RadioPopupMenuFlyoutItem;
}

/**
 * This class is a utility class for update checked/unchecked states for 
 * all other `RadioPopupMenuFlyoutItem` in the same group when one changes its state
 * 
 * This should be instantiated in `PopupMenuFlyout` as an `std::optional<>` member, then set 
 * a pointer to all child items
 */
class RadioPopupMenuItemGroup
{
	std::unordered_map<
		winrt::hstring, 
		winrt::weak_ref<winrt::WinUI3Package::RadioPopupMenuFlyoutItem>> m_radioItemGroupMap;
public:
	void SetCheckedItem(winrt::WinUI3Package::RadioPopupMenuFlyoutItem const& checkedItem);
};

