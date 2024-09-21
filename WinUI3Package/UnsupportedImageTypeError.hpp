#pragma once
#include <stdexcept>

class UnsupportedImageTypeError : public std::invalid_argument
{
public:
	UnsupportedImageTypeError() :
		invalid_argument{ "Cannot attach ImageExtension.FallbackSource to this object. Supported object are Microsoft.UI.Xaml.Controls.Image" }
	{
	}
};