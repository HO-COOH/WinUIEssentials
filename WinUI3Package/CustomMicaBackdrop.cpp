#include "pch.h"
#include "CustomMicaBackdrop.h"
#if __has_include("CustomMicaBackdrop.g.cpp")
#include "CustomMicaBackdrop.g.cpp"
#endif
#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include <winrt/Microsoft.UI.Interop.h>
#include <winrt/Microsoft.UI.Content.h>
#include <CommCtrl.h>

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty CustomMicaBackdrop::s_fallbackColorProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"FallbackColor",
			winrt::xaml_typename<winrt::Windows::UI::Color>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr }
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty CustomMicaBackdrop::s_kindProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Kind",
			winrt::xaml_typename<winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr }
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty CustomMicaBackdrop::s_luminosityOpacityProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"LuminosityOpacity",
			winrt::xaml_typename<float>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr }
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty CustomMicaBackdrop::s_tintColorProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"TintColor",
			winrt::xaml_typename<winrt::Windows::UI::Color>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr }
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty CustomMicaBackdrop::s_tintOpacityProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"TintOpacity",
			winrt::xaml_typename<float>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr }
		);
	winrt::Microsoft::UI::Xaml::DependencyProperty CustomMicaBackdrop::s_enableWhenInactiveProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"EnableWhenInactive",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(false) }
		);

	void CustomMicaBackdrop::OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget)
	{
		disposeMicaController();
		RemoveWindowSubclass(m_hwnd, &CustomMicaBackdrop::windowActiveStateWorkaroundHanlder, subclassId);
	}

	void CustomMicaBackdrop::OnTargetConnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget, winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot)
	{
		m_configuration = {};

		//Note: This method will be called before any Property setter get called.
		//So we do not need to apply the properties in this method
		makeMicaController(connectedTarget);
		m_hwnd = winrt::Microsoft::UI::GetWindowFromWindowId(
			connectedTarget.as<winrt::Microsoft::UI::Xaml::Hosting::DesktopWindowXamlSource>().SiteBridge().WindowId()
		);

		m_oldUserData = GetWindowLongPtr(m_hwnd, GWLP_USERDATA);
		winrt::check_bool(SetWindowSubclass(
			m_hwnd,
			&CustomMicaBackdrop::windowActiveStateWorkaroundHanlder,
			subclassId,
			reinterpret_cast<DWORD_PTR>(this)
		));

		xamlRoot.Changed([this, target = winrt::make_weak(connectedTarget)](winrt::Microsoft::UI::Xaml::XamlRoot const& root, winrt::Microsoft::UI::Xaml::XamlRootChangedEventArgs const& arg)
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

	void CustomMicaBackdrop::OnDefaultSystemBackdropConfigurationChanged(
		winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const&, 
		winrt::Microsoft::UI::Xaml::XamlRoot const&)
	{
	}

	winrt::Windows::UI::Color CustomMicaBackdrop::FallbackColor()
	{
		return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(FallbackColorProperty()));
	}

	void CustomMicaBackdrop::FallbackColor(winrt::Windows::UI::Color value)
	{
		SetValue(FallbackColorProperty(), winrt::box_value(value));
		if (m_controller)
		{
			m_controller.FallbackColor(value);
			m_overrideChecker = true;
		}
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty CustomMicaBackdrop::FallbackColorProperty()
	{
		return s_fallbackColorProperty;
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

	float CustomMicaBackdrop::LuminosityOpacity()
	{
		return winrt::unbox_value<float>(GetValue(LuminosityOpacityProperty()));
	}

	void CustomMicaBackdrop::LuminosityOpacity(float value)
	{
		SetValue(LuminosityOpacityProperty(), winrt::box_value(value));
		if (m_controller)
		{
			m_controller.LuminosityOpacity(value);
			m_overrideChecker = true;
		}
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty CustomMicaBackdrop::LuminosityOpacityProperty()
	{
		return s_luminosityOpacityProperty;
	}

	winrt::Windows::UI::Color CustomMicaBackdrop::TintColor()
	{
		return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(TintColorProperty()));
	}

	void CustomMicaBackdrop::TintColor(winrt::Windows::UI::Color value)
	{
		SetValue(TintColorProperty(), winrt::box_value(value));
		if (m_controller)
		{
			m_controller.TintColor(value);
			m_overrideChecker = true;
		}
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty CustomMicaBackdrop::TintColorProperty()
	{
		return s_tintColorProperty;
	}

	float CustomMicaBackdrop::TintOpacity()
	{
		return winrt::unbox_value<float>(GetValue(TintOpacityProperty()));
	}

	void CustomMicaBackdrop::TintOpacity(float value)
	{
		SetValue(TintOpacityProperty(), winrt::box_value(value));
		if (m_controller)
		{
			//Same with CustomAcrylicBackdrop.TintOpacity
			m_controller.TintColor({});
			m_controller.TintOpacity(value);
			m_controller.TintColor(TintColor());
			m_overrideChecker = true;
		}
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty CustomMicaBackdrop::TintOpacityProperty()
	{
		return s_tintOpacityProperty;
	}
	bool CustomMicaBackdrop::EnableWhenInactive()
	{
		return winrt::unbox_value<bool>(GetValue(EnableWhenInactiveProperty()));
	}
	void CustomMicaBackdrop::EnableWhenInactive(bool value)
	{
		SetValue(EnableWhenInactiveProperty(), winrt::box_value(value));
	}
	winrt::Microsoft::UI::Xaml::DependencyProperty CustomMicaBackdrop::EnableWhenInactiveProperty()
	{
		return s_enableWhenInactiveProperty;
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

	LRESULT CALLBACK CustomMicaBackdrop::windowActiveStateWorkaroundHanlder(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		if (uMsg == WM_SETFOCUS)
		{
			auto self = reinterpret_cast<CustomMicaBackdrop*>(dwRefData);
			self->m_configuration.IsInputActive(true);
		}
		else if (uMsg == WM_KILLFOCUS)
		{
			auto self = reinterpret_cast<CustomMicaBackdrop*>(dwRefData);
			self->m_configuration.IsInputActive(self->EnableWhenInactive());
		}
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
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
	}
	void CustomMicaBackdrop::disposeMicaController()
	{
		m_controller.Close();
		m_controller = nullptr;
		m_configuration = nullptr;
	}
}
