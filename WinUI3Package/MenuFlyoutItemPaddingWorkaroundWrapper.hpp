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
	template<typename Menu, typename...ShowArgs>
	void ShowAtImpl(Menu&& menu, ShowArgs&&... args)
	{
		if (m_isFirstShow)
		{
			MenuFlyoutItemPaddingWorkaround::Apply(menu);
			m_isFirstShow = false;
		}
		menu.ShowAt(std::forward<ShowArgs>(args)...);
	}

	constexpr bool IsFirstShow() const
	{
		return m_isFirstShow;
	}
};
