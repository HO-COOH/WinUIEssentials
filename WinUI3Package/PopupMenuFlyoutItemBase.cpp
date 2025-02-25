#include "pch.h"
#include "PopupMenuFlyoutItemBase.h"
#if __has_include("PopupMenuFlyoutItemBase.g.cpp")
#include "PopupMenuFlyoutItemBase.g.cpp"
#endif
#include "PopupMenu.h"
namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty PopupMenuFlyoutItemBase::s_visibilityProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Visibility",
			winrt::xaml_typename<winrt::Microsoft::UI::Xaml::Visibility>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);
	winrt::Microsoft::UI::Xaml::DependencyProperty PopupMenuFlyoutItemBase::s_isEnabledProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"IsEnabled",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			{ winrt::box_value(true), nullptr }
		);

	winrt::Microsoft::UI::Xaml::Visibility PopupMenuFlyoutItemBase::Visibility()
	{
		return winrt::unbox_value<winrt::Microsoft::UI::Xaml::Visibility>(GetValue(VisibilityProperty()));
	}

	void PopupMenuFlyoutItemBase::Visibility(winrt::Microsoft::UI::Xaml::Visibility value)
	{
		SetValue(VisibilityProperty(), winrt::box_value(value));
		if (m_parentMenu)
		{

			if (value == winrt::Microsoft::UI::Xaml::Visibility::Visible)
			{
				auto& p = *m_parentMenuPtr->m_menuItemCache.begin();
				auto insertBefore = std::find_if(
					m_parentMenuPtr->m_menuItemCache.begin(),
					m_parentMenuPtr->m_menuItemCache.end(),
					[this](auto const& item)
					{
						return item.Visibility() == winrt::Microsoft::UI::Xaml::Visibility::Visible && 
							winrt::get_self<PopupMenuFlyoutItemBase>(item)->m_parentMenu == m_parentMenu;
					}
				);

				winrt::check_bool(PopupMenu::insertMenu(
					m_parentMenu,
					insertBefore == m_parentMenuPtr->m_menuItemCache.end()? 0 : winrt::get_self<PopupMenuFlyoutItemBase>(*insertBefore)->index,
					MF_STRING,
					index,
					L"hidden item"
				));
			}
			else
			{
				winrt::check_bool(PopupMenu::deleteMenu(
					m_parentMenu,
					index
				));
			}
		}
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty PopupMenuFlyoutItemBase::VisibilityProperty()
	{
		return s_visibilityProperty;
	}
	bool PopupMenuFlyoutItemBase::IsEnabled()
	{
		return winrt::unbox_value<bool>(GetValue(IsEnabledProperty()));
	}
	void PopupMenuFlyoutItemBase::IsEnabled(bool value)
	{
		SetValue(IsEnabledProperty(), winrt::box_value(value));
	}
	winrt::Microsoft::UI::Xaml::DependencyProperty PopupMenuFlyoutItemBase::IsEnabledProperty()
	{
		return s_isEnabledProperty;
	}
}
