#pragma once
#include "MenuFlyoutItemPaddingWorkaround.h"

/**
 * @brief This is wrapper class for `MenuFlyoutItemPaddingWorkaround`
 *  that tracts the menu whether it's first opens to auto apply the fix
 *  call `Show()` method and pass in the `MenuFlyout` that needs to be fixed
 * @details Private inherit from this class, call the `Show()` method
 */
class MenuFlyoutItemPaddingWorkaroundWrapper
{
	bool m_isFirstShow = true;
public:
	void ShowAtImpl(auto&& menu, auto&&... args)
	{
		if (m_isFirstShow)
		{
			MenuFlyoutItemPaddingWorkaround::Apply(menu);
			m_isFirstShow = false;
		}
		menu.ShowAt(args...);
	}

	constexpr bool IsFirstShow() const
	{
		return m_isFirstShow;
	}
};
