#include "pch.h"
#include "CustomMicaBackdrop.h"
#if __has_include("CustomMicaBackdrop.g.cpp")
#include "CustomMicaBackdrop.g.cpp"
#endif
#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include <winrt/Microsoft.UI.Interop.h>
#include "HwndHelper.hpp"

namespace winrt::WinUI3Package::implementation
{

	winrt::Microsoft::UI::Xaml::DependencyProperty CustomMicaBackdrop::s_kindProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Kind",
			winrt::xaml_typename<winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr }
		);

	void CustomMicaBackdrop::OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget)
	{
		disposeMicaController();
		BackdropWindowActiveStateWorkaroundHandler<CustomMicaBackdrop, subclassId>::Unset(m_hwnd);
	}

	void CustomMicaBackdrop::OnTargetConnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget, winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot)
	{
		m_configuration = {};

		//Note: This method will be called before any Property setter get called.
		//So we do not need to apply the properties in this method
		makeMicaController(connectedTarget);
		m_hwnd = GetHwnd(xamlRoot);
		BackdropWindowActiveStateWorkaroundHandler<CustomMicaBackdrop, subclassId>::Set(m_hwnd, this);

		m_oldUserData = GetWindowLongPtr(m_hwnd, GWLP_USERDATA);
		

		m_xamlRootChangedRevoker = xamlRoot.Changed(winrt::auto_revoke, [this](winrt::Microsoft::UI::Xaml::XamlRoot const& root, auto&&)
		{
			if (auto content = root.Content(); content != nullptr)
			{
				auto element = content.as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
				changeTheme(content.as<winrt::Microsoft::UI::Xaml::FrameworkElement>().ActualTheme());
				element.ActualThemeChanged([this](winrt::Microsoft::UI::Xaml::FrameworkElement const& element, auto&&...)
					{
						changeTheme(element.ActualTheme());
					});
			}
		});
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
		return winrt::unbox_value<winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind>(GetValue(KindProperty()));
	}

	void CustomMicaBackdrop::Kind(winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind value)
	{
		SetValue(KindProperty(), winrt::box_value(value));
		if (m_controller)
		{
			m_overrideChecker.ThrowIfHasOverride("Kind");
			m_controller.Kind(value);
		}
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

	winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropTheme CustomMicaBackdrop::toBackdropTheme(winrt::Microsoft::UI::Xaml::ElementTheme theme)
	{
		switch (theme)
		{
		case winrt::Microsoft::UI::Xaml::ElementTheme::Default:
			return winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropTheme::Default;
		case winrt::Microsoft::UI::Xaml::ElementTheme::Light:
			return winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropTheme::Light;
		case winrt::Microsoft::UI::Xaml::ElementTheme::Dark:
			return winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropTheme::Dark;
		}
	}

	void CustomMicaBackdrop::changeTheme(winrt::Microsoft::UI::Xaml::ElementTheme theme)
	{
		m_configuration.Theme(toBackdropTheme(theme));
	}
	void CustomMicaBackdrop::makeMicaController(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& target)
	{
		m_controller = {};
		m_controller.AddSystemBackdropTarget(target);
		m_controller.SetSystemBackdropConfiguration(m_configuration);

		//set properties
		auto const unsetValue = winrt::Microsoft::UI::Xaml::DependencyProperty::UnsetValue();

		if (auto fallbackColor = ReadLocalValue(FallbackColorProperty()); fallbackColor != unsetValue)
			m_controller.FallbackColor(winrt::unbox_value<winrt::Windows::UI::Color>(fallbackColor));

		if (auto kind = ReadLocalValue(KindProperty()); kind != unsetValue)
			m_controller.Kind(winrt::unbox_value<winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind>(kind));

		if (auto luminosityOpacity = ReadLocalValue(LuminosityOpacityProperty()); luminosityOpacity != unsetValue)
			m_controller.LuminosityOpacity(winrt::unbox_value<float>(luminosityOpacity));

		if (auto tintColor = ReadLocalValue(TintColorProperty()); tintColor != unsetValue)
			m_controller.TintColor(winrt::unbox_value<winrt::Windows::UI::Color>(tintColor));

		if (auto tintOpacity = ReadLocalValue(TintOpacityProperty()); tintOpacity != unsetValue)
			m_controller.TintOpacity(winrt::unbox_value<float>(tintOpacity));
	}
	void CustomMicaBackdrop::disposeMicaController()
	{
		m_controller.Close();
		m_controller = nullptr;
		m_configuration = nullptr;
	}
}
