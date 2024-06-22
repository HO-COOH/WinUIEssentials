#pragma once
#include <winrt/Windows.UI.Xaml.Interop.h>
/**
 * @brief Helper class for calling `DefaultStyleKey` for your templated control
 * @tparam Self Should be the implementation type
 * @code{.cpp}
 *		struct MyControl : MyControlT<MyControl>, TemplateControlHelper<MyControl>
 * @endcode
*/
template<typename Self>
struct TemplateControlHelper
{
	TemplateControlHelper()
	{
		using ProjectionType = Self::class_type;
		static_cast<Self*>(this)->DefaultStyleKey(winrt::box_value(winrt::xaml_typename<ProjectionType>()));
	}
};
