#pragma once
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Controls.h>

template<typename Self, bool useXamlResource = true, bool defaultStyleOnly = true>
struct XamlResourceHelper
{
	XamlResourceHelper()
	{
		if constexpr (!useXamlResource)
			return;
		
		else if constexpr (requires { Self::ResourceUri; }) //this must be inside an else if branch, otherwise it will be evaluated even when useXamlResource is false
		{
			if constexpr (defaultStyleOnly && requires (Self& self) { self.DefaultStyleResourceUri(winrt::Windows::Foundation::Uri{ Self::ResourceUri }); })
				static_cast<Self*>(this)->DefaultStyleResourceUri(winrt::Windows::Foundation::Uri{ Self::ResourceUri });
			else
			{
				[[maybe_unused]] static bool s_resourceLoaded = []
				{
					winrt::Windows::UI::Xaml::ResourceDictionary resourceDictionary;
					resourceDictionary.Source(winrt::Windows::Foundation::Uri{ Self::ResourceUri });
					winrt::Windows::UI::Xaml::Application::Current().Resources().MergedDictionaries().Append(resourceDictionary);
					return true;
				}();
			}
			return;
		}
		else
			static_assert(!sizeof(Self), "Did you forget to add a ResourceUri?");
	}
};

/**
 * @brief Helper class for calling `DefaultStyleKey` for your templated control
 * @tparam Self Should be the implementation type
 * @code{.cpp}
 *		struct MyControl : MyControlT<MyControl>, TemplateControlHelper<MyControl>
 * @endcode
 * If Self contains a @c constexpr @c static @c wchar_t @c const* @c ResourceUri member, that dictionary is
 * either set as the control's @c DefaultStyleResourceUri (when @p defaultStyleOnly and the control supports it),
 * or merged into Application.Current.Resources.MergedDictionaries once per process. Use @p defaultStyleOnly = false
 * when consumer XAML needs the dictionary's named styles or loose values (e.g. @c DefaultSettingsExpanderItemStyle).
*/
template<typename Self, bool useXamlResource = true, bool defaultStyleOnly = true>
struct TemplateControlHelper : public XamlResourceHelper<Self, useXamlResource, defaultStyleOnly>
{
	TemplateControlHelper()
	{
		static_cast<Self*>(this)
			->template try_as<winrt::Windows::UI::Xaml::Controls::IControlProtected>()
			.DefaultStyleKey(winrt::box_value(winrt::xaml_typename<Self::class_type>()));
	}
};
