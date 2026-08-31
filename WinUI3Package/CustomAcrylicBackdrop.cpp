#include "pch.h"
#include "CustomAcrylicBackdrop.h"
#if __has_include("CustomAcrylicBackdrop.g.cpp")
#include "CustomAcrylicBackdrop.g.cpp"
#endif
#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty CustomAcrylicBackdrop::s_kindProperty = nullptr;
	winrt::Microsoft::UI::Xaml::DependencyProperty CustomAcrylicBackdrop::s_requestedThemeProperty = nullptr;

	void CustomAcrylicBackdrop::OnTargetConnected(
		winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget,
		winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot)
	{
		CustomBackdropImplBase<CustomAcrylicBackdrop, 100>::OnTargetConnected(connectedTarget, xamlRoot);
	}

	void CustomAcrylicBackdrop::OnTargetDisconnected(
		winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget)
	{
		CustomBackdropImplBase<CustomAcrylicBackdrop, 100>::OnTargetDisconnected(connectedTarget);
	}

	void CustomAcrylicBackdrop::EnsureDependencyProperties()
	{
		if (s_kindProperty) return;
		s_kindProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Kind",
			winrt::xaml_typename<winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind::Default), &CustomAcrylicBackdrop::onKindPropertyChanged }
		);
		s_requestedThemeProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"RequestedTheme",
			winrt::xaml_typename<winrt::Microsoft::UI::Xaml::ElementTheme>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(winrt::Microsoft::UI::Xaml::ElementTheme::Default), &CustomAcrylicBackdrop::onThemePropertyChanged }
		);
	}
	winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind CustomAcrylicBackdrop::Kind()
	{
		return winrt::unbox_value<winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind>(GetValue(s_kindProperty));
	}

	void CustomAcrylicBackdrop::Kind(winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind value)
	{
		SetValue(s_kindProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty CustomAcrylicBackdrop::KindProperty()
	{
		return s_kindProperty;
	}

	void CustomAcrylicBackdrop::onKindPropertyChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& backdrop,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
	{
		auto self = winrt::get_self<CustomAcrylicBackdrop>(backdrop.as<class_type>());
		if (self->m_controller)
		{
			self->m_overrideChecker.ThrowIfHasOverride("Kind");
			self->m_controller.Kind(winrt::unbox_value<winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind>(args.NewValue()));
		}
	}


	void CustomAcrylicBackdrop::OnLuminosityOpacityChanged(winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
	{
		if (m_controller)
		{
			m_overrideChecker = true;
			m_controller.LuminosityOpacity(winrt::unbox_value<float>(args.NewValue()));
		}
	}

	void CustomAcrylicBackdrop::OnTintColorChanged(winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
	{
		if (m_controller)
		{
			m_overrideChecker = true;
			m_controller.TintColor(winrt::unbox_value<winrt::Windows::UI::Color>(args.NewValue()));
		}
	}

	void CustomAcrylicBackdrop::OnTintOpacityChanged(winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
	{
		if (m_controller)
		{
			//WinUI issue: You have to change TintColor in order to change TintOpacity, otherwise it is not applied
			m_controller.TintColor({});
			m_controller.TintOpacity(winrt::unbox_value<float>(args.NewValue()));
			m_controller.TintColor(TintColor());
			m_overrideChecker = true;
		}
	}


	winrt::Microsoft::UI::Xaml::ElementTheme CustomAcrylicBackdrop::RequestedTheme()
	{
		return winrt::unbox_value<winrt::Microsoft::UI::Xaml::ElementTheme>(GetValue(s_requestedThemeProperty));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty CustomAcrylicBackdrop::RequestedThemeProperty()
	{
		return s_requestedThemeProperty;
	}

	void CustomAcrylicBackdrop::OnFallbackColorChanged(winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
	{
		if (m_controller)
		{
			m_controller.FallbackColor(winrt::unbox_value<winrt::Windows::UI::Color>(args.NewValue()));
			m_overrideChecker = true;
		}
	}

	void CustomAcrylicBackdrop::RequestedTheme(winrt::Microsoft::UI::Xaml::ElementTheme theme)
	{
		SetValue(s_requestedThemeProperty, winrt::box_value(theme));
	}

	void CustomAcrylicBackdrop::makeController(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& target)
	{
		m_controller = {};

		auto const unsetValue = winrt::Microsoft::UI::Xaml::DependencyProperty::UnsetValue();
		if (auto requestedTheme = ReadLocalValue(s_requestedThemeProperty); requestedTheme != unsetValue)
			m_configuration.Theme(toBackdropTheme(winrt::unbox_value<winrt::Microsoft::UI::Xaml::ElementTheme>(requestedTheme)));

		m_controller.AddSystemBackdropTarget(target);
		m_controller.SetSystemBackdropConfiguration(m_configuration);

		//set properties
		if (auto fallbackColor = ReadLocalValue(s_fallbackColorProperty); fallbackColor != unsetValue)
			m_controller.FallbackColor(winrt::unbox_value<winrt::Windows::UI::Color>(fallbackColor));

		if (auto kind = ReadLocalValue(s_kindProperty); kind != unsetValue)
			m_controller.Kind(winrt::unbox_value<winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind>(kind));

		if (auto luminosityOpacity = ReadLocalValue(s_luminosityOpacityProperty); luminosityOpacity != unsetValue)
			m_controller.LuminosityOpacity(winrt::unbox_value<float>(luminosityOpacity));

		if (auto tintColor = ReadLocalValue(s_tintColorProperty); tintColor != unsetValue)
			m_controller.TintColor(winrt::unbox_value<winrt::Windows::UI::Color>(tintColor));

		if (auto tintOpacity = ReadLocalValue(s_tintOpacityProperty); tintOpacity != unsetValue)
			m_controller.TintOpacity(winrt::unbox_value<float>(tintOpacity));
	}

	void CustomAcrylicBackdrop::disposeController()
	{
		m_controller.Close();
		m_controller = nullptr;
		m_configuration = nullptr;
	}

	void CustomAcrylicBackdrop::onThemePropertyChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& backdrop, 
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& themePropertyChangedArg)
	{
		auto impl = winrt::get_self<CustomAcrylicBackdrop>(backdrop.as<winrt::WinUI3Package::CustomAcrylicBackdrop>());
		if (impl->m_controller)
		{
			impl->m_configuration.Theme(toBackdropTheme(winrt::unbox_value<winrt::Microsoft::UI::Xaml::ElementTheme>(themePropertyChangedArg.NewValue())));
			impl->m_controller.SetSystemBackdropConfiguration(impl->m_configuration);
		}
	}
}
