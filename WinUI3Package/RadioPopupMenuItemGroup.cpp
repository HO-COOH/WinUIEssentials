#include "pch.h"
#include "RadioPopupMenuItemGroup.h"

void RadioPopupMenuItemGroup::SetCheckedItem(winrt::WinUI3Package::RadioPopupMenuFlyoutItem const& checkedItem)
{
	auto const& group = checkedItem.GroupName();
	if (auto it = m_radioItemGroupMap.find(group); it != m_radioItemGroupMap.end())
	{
		if (auto previousCheckedItem = it->second.get())
			previousCheckedItem.IsChecked(false);
	}
	m_radioItemGroupMap[group] = winrt::make_weak(checkedItem);
}
