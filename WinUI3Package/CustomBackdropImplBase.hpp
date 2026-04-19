#pragma once
#include "HwndHelper.hpp"

//sunclassId: workaround for m_configuration not able to send inactive state when switching to other window created in the same app package
template<typename DerivedImpl, UINT_PTR subclassId>
struct CustomBackdropImplBase
{
	friend class BackdropWindowActiveStateWorkaroundHandler<DerivedImpl, subclassId>;

	winrt::Microsoft::UI::Xaml::XamlRoot::Changed_revoker m_xamlRootChangedRevoker;
	winrt::Microsoft::UI::Xaml::FrameworkElement::ActualThemeChanged_revoker m_actualThemeChangedRevoker;
	HWND m_hwnd{};
	WNDPROC m_oldProc{};
	LONG_PTR m_oldUserData{};

	winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration m_configuration{ nullptr };

	DerivedImpl& derived()
	{
		return *static_cast<DerivedImpl*>(this);
	}

	constexpr static winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropTheme toBackdropTheme(winrt::Microsoft::UI::Xaml::ElementTheme theme)
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

	void OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget)
	{
		m_actualThemeChangedRevoker.revoke();
		m_xamlRootChangedRevoker.revoke();
		derived().disposeController();
		BackdropWindowActiveStateWorkaroundHandler<DerivedImpl, subclassId>::Unset(m_hwnd);
	}

	void OnTargetConnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget, winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot)
	{
		m_configuration = {};

		//Note: This method will be called before any Property setter get called.
		//So we do not need to apply the properties in this method
		derived().makeController(connectedTarget);
		m_hwnd = GetHwnd(xamlRoot);
		BackdropWindowActiveStateWorkaroundHandler<DerivedImpl, subclassId>::Set(m_hwnd, static_cast<DerivedImpl*>(this));

		m_oldUserData = GetWindowLongPtr(m_hwnd, GWLP_USERDATA);


		m_xamlRootChangedRevoker = xamlRoot.Changed(winrt::auto_revoke, [this](winrt::Microsoft::UI::Xaml::XamlRoot const& root, auto&&)
		{
			if (auto content = root.Content(); content != nullptr)
			{
				auto element = content.as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
				changeTheme(content.as<winrt::Microsoft::UI::Xaml::FrameworkElement>().ActualTheme());
				m_actualThemeChangedRevoker = element.ActualThemeChanged(winrt::auto_revoke, [this](winrt::Microsoft::UI::Xaml::FrameworkElement const& element, auto&&...)
				{
					changeTheme(element.ActualTheme());
				});
			}
		});
	}

	void changeTheme(winrt::Microsoft::UI::Xaml::ElementTheme theme)
	{
		m_configuration.Theme(toBackdropTheme(theme));
	}
};