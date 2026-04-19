#include "pch.h"
#include "TenMicaBackdrop.h"
#if __has_include("TenMicaBackdrop.g.cpp")
#include "TenMicaBackdrop.g.cpp"
#endif

#pragma comment(lib, "dxguid.lib")
#include <windows.ui.composition.interop.h>
#include "CrossFadeEffectInterop.h"
#include "HwndHelper.hpp"
#include "WindowsVersion.hpp"
#include "TenMicaDeviceLostException.h"

namespace winrt::WinUI3Package::implementation
{
    winrt::Microsoft::UI::Xaml::FrameworkElement TenMicaBackdrop::BindThemeTo()
    {
        return m_bindThemeTo.get();
    }

    void TenMicaBackdrop::BindThemeTo(winrt::Microsoft::UI::Xaml::FrameworkElement const value)
    {
        m_bindThemeTo = value;
        m_bindThemeRevoker = value.ActualThemeChanged(winrt::auto_revoke, [this](winrt::Microsoft::UI::Xaml::FrameworkElement const& sender, auto&&)
        {
			if (m_effect)
				m_effect->SetTheme(sender.ActualTheme() == winrt::Microsoft::UI::Xaml::ElementTheme::Light);
        });

		if (m_effect)
			m_effect->SetTheme(value.ActualTheme() == winrt::Microsoft::UI::Xaml::ElementTheme::Light);
    }

    void TenMicaBackdrop::OnTargetConnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget, winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot)
    {
		getVirtualScreenXY();
		onWallpaperChanged();
		auto& effect = getEffect();
		if (auto bindThemeTo = m_bindThemeTo.get())
			effect.SetTheme(bindThemeTo.ActualTheme() == winrt::Microsoft::UI::Xaml::ElementTheme::Light);
        connectedTarget.SystemBackdrop(effect.m_finalCrossFadeBrush);
		auto const hwnd = GetHwnd(xamlRoot);
		RECT windowRect;
		winrt::check_bool(GetWindowRect(hwnd, &windowRect));
		updateBrushOffset(windowRect.left, windowRect.top);
		addSubClass(hwnd);
		m_registryWatcher.emplace(
			this, 
			GetWindowsVersion().dwMajorVersion >= 22000 ? 
			TenMicaRegistryWatcher::WatchValue{true, true, true} :
			TenMicaRegistryWatcher::WatchValue{.background = true, .transcodedImageCache = true}
		);
    }

	void TenMicaBackdrop::OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget)
	{
		removeSubClass();
		m_registryWatcher.reset();
		connectedTarget.SystemBackdrop(nullptr);
	}

	void TenMicaBackdrop::updateBrushOffset(int windowX, int windowY)
	{
		auto const offsetX = static_cast<float>(m_virtualScreenX - windowX);
		auto const offsetY = static_cast<float>(m_virtualScreenY - windowY);
		getEffect().SetBrushOffset(offsetX, offsetY);
	}

	void TenMicaBackdrop::onWindowActivated(bool isActive)
	{
		if (EnableWhenInactive())
			return;

		getEffect().SetActive(isActive);
	}

	void TenMicaBackdrop::onWallpaperChanged()
	{
		//This must be put inside a queue, otherwise the GetMonitorDevicePathCount() causes a COM exception
		//0x8001010d : An outgoing call cannot be made since the application is dispatching an input-synchronous call

		m_queue.TryEnqueue([weakThis = get_weak()]
		{
			if (auto strong = weakThis.get())
			{
				if (!strong->m_factory->m_wallpaperManager.UpdatedNeeded())
					return;

				try
				{
					strong->m_factory->Redraw();
				}
				catch (TenMicaDeviceLostException const&)
				{
					//no need to handle it here
				}
			}
		});
	}

	void TenMicaBackdrop::onDisplayChanged()
	{
		getVirtualScreenXY();
		m_queue.TryEnqueue([weakThis = get_weak()]
		{
			if (auto strong = weakThis.get())
			{
				try
				{
					strong->onDeviceReset();
				}
				catch (TenMicaDeviceLostException const&)
				{
					std::ignore = strong->m_factory->m_wallpaperManager.UpdatedNeeded();
					strong->onDeviceReset();
				}
			}
		});
	}

	TenMicaEffect& TenMicaBackdrop::getEffect()
	{
		if (!m_effect)
			m_effect.emplace(m_factory->Get());
		
		return *m_effect;
	}

	void TenMicaBackdrop::getVirtualScreenXY()
	{
		m_virtualScreenX = GetSystemMetrics(SM_XVIRTUALSCREEN);
		m_virtualScreenY = GetSystemMetrics(SM_YVIRTUALSCREEN);
	}

	void TenMicaBackdrop::onDeviceReset()
	{
		m_factory->OnDeviceLost(getEffect());
		RECT windowRect;
		winrt::check_bool(GetWindowRect(m_hwnd, &windowRect));
		updateBrushOffset(windowRect.left, windowRect.top);
	}

}
