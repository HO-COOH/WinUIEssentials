#include "pch.h"
#include "PlacementVisualBase.h"
#include <winrt/Microsoft.UI.Xaml.Hosting.h>

PlacementVisualBase::PlacementVisualBase(winrt::Microsoft::UI::Xaml::Controls::Control const& host)
{
	host.RegisterPropertyChangedCallback(
		winrt::Microsoft::UI::Xaml::Controls::Control::CornerRadiusProperty(),
		{ this, &PlacementVisualBase::cornerRadiusChanged }
	);
}

void PlacementVisualBase::BindPlacementVisualSizeToHost(winrt::Microsoft::UI::Xaml::UIElement const& host)
{
	auto const hostVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(host);
	auto sizeAnimation = hostVisual.Compositor().CreateExpressionAnimation(L"host.Size");
	sizeAnimation.SetReferenceParameter(L"host", hostVisual);
	m_placementVisual.StartAnimation(L"Size", sizeAnimation);

	//CornerRadius can change before the derived class attaches the placement visual, in which case the clip is still waiting for it
	if (m_clip)
		m_placementVisual.Clip(m_clip);
}

void PlacementVisualBase::cornerRadiusChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& host, winrt::Microsoft::UI::Xaml::DependencyProperty const& dp)
{
	if (!m_clip)
	{
		auto const hostVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(host.as<winrt::Microsoft::UI::Xaml::UIElement>());
		auto const compositor = hostVisual.Compositor();
		m_clip = compositor.CreateRectangleClip();

		auto rightAnimation = compositor.CreateExpressionAnimation(L"host.Size.X");
		rightAnimation.SetReferenceParameter(L"host", hostVisual);
		m_clip.StartAnimation(L"Right", rightAnimation);

		auto bottomAnimation = compositor.CreateExpressionAnimation(L"host.Size.Y");
		bottomAnimation.SetReferenceParameter(L"host", hostVisual);
		m_clip.StartAnimation(L"Bottom", bottomAnimation);

		if (m_placementVisual)
			m_placementVisual.Clip(m_clip);
	}

	auto const radius = host.GetValue(dp).as<winrt::Microsoft::UI::Xaml::CornerRadius>();
	m_clip.TopLeftRadius({ static_cast<float>(radius.TopLeft), static_cast<float>(radius.TopLeft) });
	m_clip.TopRightRadius({ static_cast<float>(radius.TopRight), static_cast<float>(radius.TopRight) });
	m_clip.BottomLeftRadius({ static_cast<float>(radius.BottomLeft), static_cast<float>(radius.BottomLeft) });
	m_clip.BottomRightRadius({ static_cast<float>(radius.BottomRight), static_cast<float>(radius.BottomRight) });
}
