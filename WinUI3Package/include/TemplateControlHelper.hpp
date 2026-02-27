#pragma once
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Microsoft.UI.Xaml.h>

template<typename Self>
struct XamlResourceHelper
{
	XamlResourceHelper()
	{
		if constexpr (requires { Self::ResourceUri; })
		{
			if constexpr (requires {Self::DefaultStyleResourceUri(); })
				static_cast<Self*>(this)->DefaultStyleResourceUri(winrt::Windows::Foundation::Uri{ Self::ResourceUri });
			else
			{
				[[maybe_unused]] static bool s_resourceLoaded = []
				{
					winrt::Microsoft::UI::Xaml::ResourceDictionary resourceDictionary;
					resourceDictionary.Source(winrt::Windows::Foundation::Uri{ Self::ResourceUri });
					winrt::Microsoft::UI::Xaml::Application::Current().Resources().MergedDictionaries().Append(resourceDictionary);
					return true;
				}();
			}
		}
	}
};


/**
 * @brief Helper class for calling `DefaultStyleKey` for your templated control
 * @tparam Self Should be the implementation type
 * @code{.cpp}
 *		struct MyControl : MyControlT<MyControl>, TemplateControlHelper<MyControl>
 * @endcode
 * If Self contains a @c constexpr @c static @c wchar_t @c const* @c ResourceUri member,
 * the corresponding ResourceDictionary is automatically loaded into Application.Current.Resources.MergedDictionaries.
*/
template<typename Self>
struct TemplateControlHelper : public XamlResourceHelper<Self>
{
	TemplateControlHelper()
	{
		using ProjectionType = Self::class_type;
		static_cast<Self*>(this)->DefaultStyleKey(winrt::box_value(winrt::xaml_typename<ProjectionType>()));
	}
};
