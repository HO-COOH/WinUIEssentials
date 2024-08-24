/*****************************************************************//**
 * \file   InvalidMenuItemIconTypeError.hpp
 * \brief  
 * 
 * \author Peter
 * \date   August 2024
 *********************************************************************/
#pragma once
#include <stdexcept>

//This colass wraps up a typed exception for unsupported IconElement type used in PopupMenuFlyoutItem.IconElement
class InvalidMenuItemIconTypeError : public std::invalid_argument
{
public:
	InvalidMenuItemIconTypeError() :
		invalid_argument{ "Invalid PopupMenuFlyoutItem.IconElement type! Valid types are: Microsoft.UI.Xaml.Controls.SymbolIcon & Microsoft.UI.Xaml.Controls.FontIcon" }
	{
	}
};
