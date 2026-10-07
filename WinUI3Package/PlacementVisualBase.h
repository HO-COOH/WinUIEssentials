#pragma once

#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>

//Handles automatic sizing and CornerRadius handling of a placement visual
template<typename Derived>
class PlacementVisualBase
{
	auto& getSelf()
	{
		return static_cast<Derived&>(*this);
	}
protected:

	PlacementVisualBase()
	{
		getSelf().RegisterPropertyChangedCallback(
			winrt::Microsoft::UI::Xaml::Controls::Control::CornerRadiusProperty(),
			{this, &PlacementVisualBase::cornerRadiusChanged}
		);
	}

	winrt::Microsoft::UI::Composition::Visual m_placementVisual{ nullptr };
	
	//Call after the placement visual is attached to the host
	void BindPlacementVisual()
	{
		auto const hostVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(getSelf());
		auto sizeAnimation = hostVisual.Compositor().CreateExpressionAnimation(L"host.Size");
		sizeAnimation.SetReferenceParameter(L"host", hostVisual);
		m_placementVisual.StartAnimation(L"Size", sizeAnimation);

		//CornerRadius can change before the derived class attaches the placement visual, in which case the clip is still waiting for it
		if (m_clip)
			m_placementVisual.Clip(m_clip);
	}
private:
	PlacementVisualBase(PlacementVisualBase const&) = delete;

	winrt::Microsoft::UI::Composition::RectangleClip m_clip{ nullptr };
	
	void cornerRadiusChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& host,
		winrt::Microsoft::UI::Xaml::DependencyProperty const& cornerRadiusProperty
	)
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

		auto const radius = host.GetValue(cornerRadiusProperty).as<winrt::Microsoft::UI::Xaml::CornerRadius>();
		m_clip.TopLeftRadius({ static_cast<float>(radius.TopLeft), static_cast<float>(radius.TopLeft) });
		m_clip.TopRightRadius({ static_cast<float>(radius.TopRight), static_cast<float>(radius.TopRight) });
		m_clip.BottomLeftRadius({ static_cast<float>(radius.BottomLeft), static_cast<float>(radius.BottomLeft) });
		m_clip.BottomRightRadius({ static_cast<float>(radius.BottomRight), static_cast<float>(radius.BottomRight) });
	}
};
