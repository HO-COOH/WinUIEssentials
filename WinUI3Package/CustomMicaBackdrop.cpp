#include "pch.h"
#include "CustomMicaBackdrop.h"
#if __has_include("CustomMicaBackdrop.g.cpp")
#include "CustomMicaBackdrop.g.cpp"
#endif
#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>


namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty CustomMicaBackdrop::s_kindProperty = nullptr;

	void CustomMicaBackdrop::OnTargetConnected(
		winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget,
		winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot)
	{
		CustomBackdropImplBase<CustomMicaBackdrop, 101>::OnTargetConnected(connectedTarget, xamlRoot);
	}

	void CustomMicaBackdrop::OnTargetDisconnected(
		winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget)
	{
		CustomBackdropImplBase<CustomMicaBackdrop, 101>::OnTargetDisconnected(connectedTarget);
	}

	void CustomMicaBackdrop::EnsureDependencyProperties()
	{
		if (s_kindProperty) return;
		s_kindProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Kind",
			winrt::xaml_typename<winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind::Base), &CustomMicaBackdrop::onKindPropertyChanged }
		);
	}

	void CustomMicaBackdrop::OnFallbackColorChanged(winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
	{
		if (m_controller)
		{
			m_controller.FallbackColor(winrt::unbox_value<winrt::Windows::UI::Color>(args.NewValue()));
			m_overrideChecker = true;
		}
	}

	winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind CustomMicaBackdrop::Kind()
	{
		return winrt::unbox_value<winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind>(GetValue(s_kindProperty));
	}

	void CustomMicaBackdrop::Kind(winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind value)
	{
		SetValue(s_kindProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty CustomMicaBackdrop::KindProperty()
	{
		return s_kindProperty;
	}

	void CustomMicaBackdrop::OnLuminosityOpacityChanged(winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
	{
		if (m_controller)
		{
			m_controller.LuminosityOpacity(winrt::unbox_value<float>(args.NewValue()));
			m_overrideChecker = true;
		}
	}

	void CustomMicaBackdrop::OnTintColorChanged(winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
	{
		if (m_controller)
		{
			m_controller.TintColor(winrt::unbox_value<winrt::Windows::UI::Color>(args.NewValue()));
			m_overrideChecker = true;
		}
	}

	void CustomMicaBackdrop::OnTintOpacityChanged(winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
	{
		if (m_controller)
		{
			//Same with CustomAcrylicBackdrop.TintOpacity
			m_controller.TintColor({});
			m_controller.TintOpacity(winrt::unbox_value<float>(args.NewValue()));
			m_controller.TintColor(TintColor());
			m_overrideChecker = true;
		}
	}

	void CustomMicaBackdrop::onKindPropertyChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
	{
		auto self = winrt::get_self<CustomMicaBackdrop>(sender.as<class_type>());
		if (self->m_controller)
		{
			self->m_overrideChecker.ThrowIfHasOverride("Kind");
			self->m_controller.Kind(winrt::unbox_value<winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind>(args.NewValue()));
		}
	}


	void CustomMicaBackdrop::makeController(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& target)
	{
		m_controller = {};
		m_controller.AddSystemBackdropTarget(target);
		m_controller.SetSystemBackdropConfiguration(m_configuration);

		//set properties
		auto const unsetValue = winrt::Microsoft::UI::Xaml::DependencyProperty::UnsetValue();

		if (auto fallbackColor = ReadLocalValue(s_fallbackColorProperty); fallbackColor != unsetValue)
			m_controller.FallbackColor(winrt::unbox_value<winrt::Windows::UI::Color>(fallbackColor));

		if (auto kind = ReadLocalValue(s_kindProperty); kind != unsetValue)
			m_controller.Kind(winrt::unbox_value<winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind>(kind));

		if (auto luminosityOpacity = ReadLocalValue(s_luminosityOpacityProperty); luminosityOpacity != unsetValue)
			m_controller.LuminosityOpacity(winrt::unbox_value<float>(luminosityOpacity));

		if (auto tintColor = ReadLocalValue(s_tintColorProperty); tintColor != unsetValue)
			m_controller.TintColor(winrt::unbox_value<winrt::Windows::UI::Color>(tintColor));

		if (auto tintOpacity = ReadLocalValue(s_tintOpacityProperty); tintOpacity != unsetValue)
			m_controller.TintOpacity(winrt::unbox_value<float>(tintOpacity));
	}
	void CustomMicaBackdrop::disposeController()
	{
		m_controller.Close();
		m_controller = nullptr;
		m_configuration = nullptr;
	}
}
