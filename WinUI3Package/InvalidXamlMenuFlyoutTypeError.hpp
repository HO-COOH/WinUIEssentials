/*****************************************************************//**
 * \file   InvalidXamlMenuFlyoutTypeError.hpp
 * \brief  This class wraps up a typed exception for wrong MenuFlyout type used in xaml
 * 
 * \author Peter
 * \date   August 2024
 *********************************************************************/
#pragma once
#include <stdexcept>

class InvalidXamlMenuFlyoutTypeError : public std::invalid_argument
{
public:
	InvalidXamlMenuFlyoutTypeError() : 
		invalid_argument{ "Invalid Xaml MenuFlyout type! Valid types are: Microsoft.UI.Xaml.Controls.MenuFlyout & WinUI3Package.PopupMenuFlyout" }
	{
	}
};
