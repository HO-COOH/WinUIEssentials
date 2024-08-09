/*****************************************************************//**
 * \file   ScopedButtonDisabler.hpp
 * \brief  This is a helper class disbling a button inside a scope to prevent double-clicking
 *
 * \author szpeter@yeah.net
 * \date   August 2024
 *********************************************************************/
#pragma once
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
class ScopedButtonDisabler
{
	winrt::Windows::UI::Xaml::Controls::Primitives::ButtonBase m_button;
public:
	/**
	 * This is the primary constructor that accepts any button that are derived from `ButtonBase`
	 * @param button Can be a `Button`, `HyperlinkButton`, `RepeatButton` and `ToggleButton`
	 * @param initialDisabled Whether or not disable the `button` upon construction
	 */
	ScopedButtonDisabler(winrt::Windows::UI::Xaml::Controls::Primitives::ButtonBase button, bool initialDisabled = true) :
		m_button{ button }
	{
		if (initialDisabled)
			button.IsEnabled(false);
	}

	/**
	 * This is a convenient helper typically used inside a `Button.Click` event handler,
	 *  because the generated event handler's argument `sender` has a type `IInspectable`.
	 * @throw When `button` cannot be cast to a `ButtonBase`
	 * \param button
	 * \param initialDisabled Whether or not disable the `button` upon construction
	 */
	ScopedButtonDisabler(winrt::Windows::Foundation::IInspectable button, bool initialDisabled = true) :
		ScopedButtonDisabler{ button.as<winrt::Windows::UI::Xaml::Controls::Primitives::ButtonBase>(), initialDisabled }
	{
	}

	~ScopedButtonDisabler()
	{
		m_button.IsEnabled(true);
	}
};
