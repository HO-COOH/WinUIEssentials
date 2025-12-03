#include "pch.h"
#include "Shimmer.h"
#if __has_include("Shimmer.g.cpp")
#include "Shimmer.g.cpp"
#endif
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include "Shimmer.DefaultGradientColor.h"

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty Shimmer::s_isLoadingProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"IsLoading",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				winrt::box_value(false)
			}
		);

	bool Shimmer::IsLoading()
	{
		return winrt::unbox_value<bool>(GetValue(IsLoadingProperty()));
	}

	void Shimmer::IsLoading(bool value)
	{
		SetValue(IsLoadingProperty(), winrt::box_value(value));
		value ? loadShimmer() : loadContent();
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty Shimmer::IsLoadingProperty()
	{
		return s_isLoadingProperty;
	}

	void Shimmer::OnApplyTemplate()
	{
		base_type::OnApplyTemplate();
		m_loaded = true;

		m_animationContainer = GetTemplateChild(L"Container").as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
		m_presenter = GetTemplateChild(L"ContentPresenter").as<winrt::Microsoft::UI::Xaml::Controls::ContentPresenter>();
		startAnimation();
		m_animationContainer.SizeChanged([this](auto&& sender, winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& args) 
		{
			if (m_animation)
				m_animation->SetSize(args.NewSize());
		});
		
		ActualThemeChanged([this](auto&&...) 
		{
			if (m_animation)
				setGradientStops();
		});
	}

	void Shimmer::startAnimation()
	{
		if (!m_loaded)
			return;

		m_animation.emplace(
			winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(m_animationContainer).Compositor(),
			std::chrono::milliseconds{ 1600 }
		);

		setGradientStops();
		auto size = m_animationContainer.ActualSize();
		winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(m_animationContainer, m_animation->GetVisual(size, CornerRadius().TopLeft));
	}

	void Shimmer::setGradientStops()
	{
		auto const theme = ActualTheme();
		if (winrt::Microsoft::UI::Xaml::Media::GradientStopCollection stops = tryGetGraidentStopsFromThemeResource(theme))
			m_animation->SetGradientStops(stops);
		else
		{
			stops = tryGetGradientStopsFromAppResource(theme);
			if (stops)
				m_animation->SetGradientStops(stops);
			else
				setDefaultGradientStops(theme);
		}
	}

	void Shimmer::setDefaultGradientStops(winrt::Microsoft::UI::Xaml::ElementTheme theme)
	{
		m_animation->SetGradientStops(
			theme == winrt::Microsoft::UI::Xaml::ElementTheme::Light ? DefaultShimmerGraidentColor::LightColors : DefaultShimmerGraidentColor::DarkColors,
			DefaultShimmerGraidentColor::GradientStopOffset
		);
	}

	void Shimmer::loadShimmer()
	{
		if (!m_loaded)
			return;
		//winrt::Microsoft::UI::Xaml::Markup::XamlMarkupHelper::UnloadObject(m_presenter);
		//if (!m_animationContainer)
		//{
		//	m_animationContainer = GetTemplateChild(L"Container").as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
		//	//auto parent = winrt::get_class_name(m_animationContainer.Parent());
		//	m_animationContainer.Parent().as<winrt::Microsoft::UI::Xaml::Controls::Panel>().Children().Append(m_animationContainer);
		//}
		startAnimation();
	}

	void Shimmer::loadContent()
	{
		m_animation.reset();
		//if (m_animationContainer)
		//{
		//	m_rootPanel = m_animationContainer.Parent().as<winrt::Microsoft::UI::Xaml::Controls::Panel>();
		//	removeChildFromPanel(m_rootPanel, m_animationContainer);
		//	winrt::Microsoft::UI::Xaml::Markup::XamlMarkupHelper::UnloadObject(m_animationContainer);
		//	m_animationContainer = nullptr;
		//}
		m_presenter.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
	}

	winrt::Microsoft::UI::Xaml::ResourceDictionary Shimmer::tryGetThemeResourceDictionaryFromResource(winrt::Microsoft::UI::Xaml::ResourceDictionary const& resource, winrt::Microsoft::UI::Xaml::ElementTheme theme)
	{
		auto themeDictionaries = resource.ThemeDictionaries();
		if (!themeDictionaries)
			return nullptr;

		winrt::Windows::Foundation::IInspectable themeDictionary{ nullptr };
		switch (theme)
		{
			case winrt::Microsoft::UI::Xaml::ElementTheme::Light:
				themeDictionary = themeDictionaries.TryLookup(winrt::box_value(L"Light"));
				break;
			case winrt::Microsoft::UI::Xaml::ElementTheme::Dark:
				themeDictionary = themeDictionaries.TryLookup(winrt::box_value(L"Dark"));
				break;
			default:
				themeDictionary = themeDictionaries.TryLookup(winrt::box_value(L"Default"));
				break;
		}
		return themeDictionary.try_as<winrt::Microsoft::UI::Xaml::ResourceDictionary>();
	}

	winrt::Microsoft::UI::Xaml::ResourceDictionary Shimmer::tryGetThemeResourceDictionary(winrt::Microsoft::UI::Xaml::ElementTheme theme)
	{
		return tryGetThemeResourceDictionaryFromResource(Resources(), theme);
	}

	winrt::Microsoft::UI::Xaml::Media::GradientStopCollection Shimmer::tryGetGraidentStopsFromThemeResource(winrt::Microsoft::UI::Xaml::ElementTheme theme)
	{
		auto themeDictionary = tryGetThemeResourceDictionary(theme);
		if (!themeDictionary)
			return nullptr;

		if (auto stopsRef = themeDictionary.TryLookup(winrt::box_value(ShimmerGradientStopsResourceName)))
			return stopsRef.try_as<winrt::Microsoft::UI::Xaml::Media::GradientStopCollection>();

		return nullptr;
	}

	winrt::Microsoft::UI::Xaml::Media::GradientStopCollection Shimmer::tryGetGradientStopsFromAppResource(winrt::Microsoft::UI::Xaml::ElementTheme theme)
	{
		auto application = winrt::Microsoft::UI::Xaml::Application::Current();
		if (!application)
			return nullptr;

		auto appResource = application.Resources();
		if (!appResource)
			return nullptr;

		auto themeResource = tryGetThemeResourceDictionaryFromResource(appResource, theme);
		if (!themeResource)
			return nullptr;

		auto stops = themeResource.TryLookup(winrt::box_value(ShimmerGradientStopsResourceName));
		if (!stops)
			return nullptr;

		return stops.try_as<winrt::Microsoft::UI::Xaml::Media::GradientStopCollection>();
	}

	bool Shimmer::removeChildFromPanel(winrt::Microsoft::UI::Xaml::Controls::Panel const& panel, winrt::Microsoft::UI::Xaml::FrameworkElement const& child)
	{
		auto children = panel.Children();
		if (uint32_t childIndex{}; children.IndexOf(child, childIndex))
		{
			children.RemoveAt(childIndex);
			return true;
		}
		return false;
	}

}
