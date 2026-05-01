#include "pch.h"
#include "Shimmer.h"
#include "Shimmer.DefaultGradientColor.h"
#if __has_include("Shimmer.g.cpp")
#include "Shimmer.g.cpp"
#endif

namespace winrt::PackageRoot::implementation
{
	void Shimmer::EnsureDependencyProperties()
	{
		if (s_isLoadingProperty) return;
		s_isLoadingProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"IsLoading",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{
				winrt::box_value(false),
				[](winrt::WinUINamespace::UI::Xaml::DependencyObject const& shimmer, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
				{
					auto self = winrt::get_self<Shimmer>(shimmer.as<PackageRoot::Shimmer>());
					winrt::unbox_value<bool>(args.NewValue()) ? self->loadShimmer() : self->loadContent();
				}
			}
		);

		s_gradientStopsProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"GradientStops",
			winrt::xaml_typename<winrt::WinUINamespace::UI::Xaml::Media::GradientStopCollection>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{
				nullptr,
				[](winrt::WinUINamespace::UI::Xaml::DependencyObject const& shimmer, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const&)
				{
					winrt::get_self<Shimmer>(shimmer.as<PackageRoot::Shimmer>())->applyGradientStops();
				}
			}
		);
	}

	bool Shimmer::IsLoading()
	{
		return winrt::unbox_value<bool>(GetValue(IsLoadingProperty()));
	}

	void Shimmer::IsLoading(bool value)
	{
		SetValue(IsLoadingProperty(), winrt::box_value(value));
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty Shimmer::IsLoadingProperty()
	{
		return s_isLoadingProperty;
	}

	winrt::WinUINamespace::UI::Xaml::Media::GradientStopCollection Shimmer::GradientStops()
	{
		return GetValue(GradientStopsProperty()).try_as<winrt::WinUINamespace::UI::Xaml::Media::GradientStopCollection>();
	}

	void Shimmer::GradientStops(winrt::WinUINamespace::UI::Xaml::Media::GradientStopCollection const& value)
	{
		SetValue(GradientStopsProperty(), value);
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty Shimmer::GradientStopsProperty()
	{
		return s_gradientStopsProperty;
	}

	void Shimmer::OnApplyTemplate()
	{
		base_type::OnApplyTemplate();
		m_loaded = true;

		m_presenter = GetTemplateChild(L"ContentPresenter").as<winrt::WinUINamespace::UI::Xaml::Controls::ContentPresenter>();
		IsLoading() ? loadShimmer() : loadContent();
	}

	void Shimmer::startAnimation()
	{
		if (!m_loaded)
			return;

		m_animation.emplace(
			winrt::WinUINamespace::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(m_animationContainer).Compositor(),
			std::chrono::milliseconds{ 1600 }
		);

		if (auto stops = GradientStops())
			m_animation->SetGradientStops(stops);
		else if (ActualTheme() == winrt::WinUINamespace::UI::Xaml::ElementTheme::Dark)
			m_animation->SetGradientStops(DefaultShimmerGraidentColor::DarkColors, DefaultShimmerGraidentColor::GradientStopOffset);
		else
			m_animation->SetGradientStops(DefaultShimmerGraidentColor::LightColors, DefaultShimmerGraidentColor::GradientStopOffset);
		winrt::Windows::Foundation::Numerics::float2 size{
			static_cast<float>(m_animationContainer.ActualWidth()),
			static_cast<float>(m_animationContainer.ActualHeight())
		};
		winrt::WinUINamespace::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(m_animationContainer, m_animation->GetVisual(size, CornerRadius().TopLeft));
	}

	void Shimmer::applyGradientStops()
	{
		if (!m_animation)
			return;
		if (auto stops = GradientStops())
			m_animation->SetGradientStops(stops);
		else if (ActualTheme() == winrt::WinUINamespace::UI::Xaml::ElementTheme::Dark)
			m_animation->SetGradientStops(DefaultShimmerGraidentColor::DarkColors, DefaultShimmerGraidentColor::GradientStopOffset);
		else
			m_animation->SetGradientStops(DefaultShimmerGraidentColor::LightColors, DefaultShimmerGraidentColor::GradientStopOffset);
	}

	void Shimmer::loadShimmer()
	{
		if (!m_loaded)
			return;
		if (!m_animationContainer)
		{
			m_animationContainer = GetTemplateChild(L"Container").as<winrt::WinUINamespace::UI::Xaml::FrameworkElement>();
			m_animationSizeChangedRevoker = m_animationContainer.SizeChanged(winrt::auto_revoke, [this](auto&& sender, winrt::WinUINamespace::UI::Xaml::SizeChangedEventArgs const& args)
			{
				if (m_animation)
					m_animation->SetSize(args.NewSize());
			});
		}
		if (m_presenter)
			m_presenter.Opacity(0);
		startAnimation();
	}

	void Shimmer::loadContent()
	{
		m_animation.reset();
		if (m_animationContainer)
		{
			m_animationSizeChangedRevoker.revoke();
			winrt::WinUINamespace::UI::Xaml::Markup::XamlMarkupHelper::UnloadObject(m_animationContainer);
			m_animationContainer = nullptr;
		}
		if (m_presenter)
			m_presenter.Opacity(1.0);
	}

	bool Shimmer::removeChildFromPanel(winrt::WinUINamespace::UI::Xaml::Controls::Panel const& panel, winrt::WinUINamespace::UI::Xaml::FrameworkElement const& child)
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
