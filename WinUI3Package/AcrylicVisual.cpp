#include "pch.h"
#include "AcrylicVisual.h"
#if __has_include("AcrylicVisual.g.cpp")
#include "AcrylicVisual.g.cpp"
#endif
#include <format>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include "ThemeListener.h"

namespace winrt::WinUI3Package::implementation
{
	static inline winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropTheme elementThemeToBackdropTheme(
		winrt::Microsoft::UI::Xaml::ElementTheme const& theme)
	{
		switch (theme)
		{
			case winrt::Microsoft::UI::Xaml::ElementTheme::Light:
				return winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropTheme::Light;
			case winrt::Microsoft::UI::Xaml::ElementTheme::Dark:
				return winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropTheme::Dark;
			default:
				return ThemeSettings::Instance().AppsUseLightTheme() ? 
					winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropTheme::Light : 
					winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropTheme::Dark;
		}
	};

	AcrylicVisual::AcrylicVisual()
	{
		RegisterPropertyChangedCallback(
			winrt::Microsoft::UI::Xaml::Controls::Control::CornerRadiusProperty(),
			{ this, &AcrylicVisual::cornerRadiusChanged }
		);

		RegisterPropertyChangedCallback(
			winrt::Microsoft::UI::Xaml::FrameworkElement::RequestedThemeProperty(),
			[this](auto&&...)
			{ 
				m_configuration.Theme(elementThemeToBackdropTheme(RequestedTheme()));
				m_controller.SetSystemBackdropConfiguration(m_configuration);
			});
		auto compositor = winrt::Microsoft::UI::Xaml::Media::CompositionTarget::GetCompositorForCurrentThread();
		m_backdropLink = winrt::Microsoft::UI::Content::ContentExternalBackdropLink::Create(compositor);
		m_backdropLink.ExternalBackdropBorderMode(winrt::Microsoft::UI::Composition::CompositionBorderMode::Soft);
		m_controller = {};

		Loaded([this](auto&&...) {updateVisual(); });
	}

	winrt::Windows::Foundation::Size AcrylicVisual::ArrangeOverride(winrt::Windows::Foundation::Size finalSize)
	{
		updateVisual();
		m_placementVisual.Size(finalSize);
		if (m_clip)
		{
			m_clip.Right(finalSize.Width + ClipOffset.z);
			m_clip.Bottom(finalSize.Height + ClipOffset.w);
		}
		return finalSize;
	}

	winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration AcrylicVisual::m_configuration =
		[]()
		{
			winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration configuration;
			configuration.IsInputActive(true);
			return configuration;
		}();

	void AcrylicVisual::cornerRadiusChanged(winrt::Microsoft::UI::Xaml::DependencyObject const&, winrt::Microsoft::UI::Xaml::DependencyProperty const&)
	{
		updateVisual();
		auto const radius = CornerRadius();
		if (!m_clip)
		{
			auto const actualSize = ActualSize();
			m_clip = winrt::Microsoft::UI::Xaml::Media::CompositionTarget::GetCompositorForCurrentThread().CreateRectangleClip(
				0.f + ClipOffset.x,
				0.f + ClipOffset.y,
				actualSize.x + ClipOffset.z,
				actualSize.y + ClipOffset.w,
				{ static_cast<float>(radius.TopLeft), static_cast<float>(radius.TopLeft) },
				{ static_cast<float>(radius.TopRight), static_cast<float>(radius.TopRight) },
				{ static_cast<float>(radius.BottomRight), static_cast<float>(radius.BottomRight) },
				{ static_cast<float>(radius.BottomLeft), static_cast<float>(radius.BottomLeft) }
			);
			m_placementVisual.Clip(m_clip);
		}
		else
		{
			m_clip.TopLeftRadius({ static_cast<float>(radius.TopLeft), static_cast<float>(radius.TopLeft) });
			m_clip.TopRightRadius({ static_cast<float>(radius.TopRight), static_cast<float>(radius.TopRight) });
			m_clip.BottomLeftRadius({ static_cast<float>(radius.BottomLeft), static_cast<float>(radius.BottomLeft) });
			m_clip.BottomRightRadius({ static_cast<float>(radius.BottomRight), static_cast<float>(radius.BottomRight) });
		}
	}

	void AcrylicVisual::updateVisual()
	{
		if (auto parent = Parent())
		{
			if (auto parentElement = parent.try_as<winrt::Microsoft::UI::Xaml::FrameworkElement>())
			{
				auto theme = parentElement.ActualTheme();
				m_configuration.Theme(elementThemeToBackdropTheme(theme));
			}
		}

		if (!m_placementVisual)
		{
			m_controller.AddSystemBackdropTarget(m_backdropLink.as<winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop>());
			m_controller.SetSystemBackdropConfiguration(m_configuration);
			m_placementVisual = m_backdropLink.PlacementVisual();
			m_placementVisual.BorderMode(winrt::Microsoft::UI::Composition::CompositionBorderMode::Soft);
			winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(*this, m_placementVisual);
		}
	}
}
