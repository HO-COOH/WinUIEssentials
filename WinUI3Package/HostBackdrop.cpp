#include "pch.h"
#include "HostBackdrop.h"
#if __has_include("HostBackdrop.g.cpp")
#include "HostBackdrop.g.cpp"
#endif
#include <winrt/Windows.UI.Composition.h>
#include "GaussianBlurEffectInterop.h"

namespace winrt::WinUI3Package::implementation
{
	void HostBackdrop::EnsureDependencyProperties()
	{
		if (s_blurAmountProperty)
			return;

		s_blurAmountProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"BlurAmount",
			winrt::xaml_typename<float>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(60.f), &HostBackdrop::onBlurAmountChanged}
		);
	}

	void HostBackdrop::OnTargetConnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget, winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot)
	{
		winrt::Windows::UI::Composition::Compositor compositor;
		auto hostBackdropBrush = compositor.CreateHostBackdropBrush();

		auto blurEffect = winrt::make_self<GaussianBlurEffectInterop>(BlurAmount(), L"Backdrop");
		blurEffect->Name(L"Blur");

		auto effectFactory = compositor.CreateEffectFactory(*blurEffect, { L"Blur.BlurAmount" });
		m_effectBrush = effectFactory.CreateBrush();
		m_effectBrush.SetSourceParameter(L"Backdrop", hostBackdropBrush);

		connectedTarget.SystemBackdrop(m_effectBrush);
	}

	void HostBackdrop::OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget)
	{
	}

	float HostBackdrop::BlurAmount()
	{
		return winrt::unbox_value<float>(GetValue(s_blurAmountProperty));
	}

	void HostBackdrop::BlurAmount(float value)
	{
		SetValue(s_blurAmountProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty HostBackdrop::BlurAmountProperty()
	{
		return s_blurAmountProperty;
	}

	void HostBackdrop::onBlurAmountChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto self = GetSelf(d);
		if (!self->m_effectBrush)
			return;

		self->m_effectBrush.Properties().InsertScalar(L"Blur.BlurAmount", winrt::unbox_value<float>(e.NewValue()));
	}
}
