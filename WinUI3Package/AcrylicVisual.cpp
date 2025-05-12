#include "pch.h"
#include "AcrylicVisual.h"
#if __has_include("AcrylicVisual.g.cpp")
#include "AcrylicVisual.g.cpp"
#endif
#include <format>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>

namespace winrt::WinUI3Package::implementation
{
	AcrylicVisual::AcrylicVisual()
	{
		RegisterPropertyChangedCallback(
			winrt::Microsoft::UI::Xaml::Controls::Control::CornerRadiusProperty(),
			{ this, &AcrylicVisual::cornerRadiusChanged }
		);
		RegisterPropertyChangedCallback(
			winrt::Microsoft::UI::Xaml::FrameworkElement::MarginProperty(),
			{ this, &AcrylicVisual::paddingChanged }
		);

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

	void AcrylicVisual::cornerRadiusChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& self, winrt::Microsoft::UI::Xaml::DependencyProperty const& cornerRadiusProperty)
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

	void AcrylicVisual::paddingChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& self, winrt::Microsoft::UI::Xaml::DependencyProperty const& paddingProperty)
	{
	}
	void AcrylicVisual::updateVisual()
	{
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
