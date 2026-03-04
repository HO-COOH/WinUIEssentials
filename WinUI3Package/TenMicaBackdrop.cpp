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
		if (GetWindowsVersion().dwMajorVersion >= 22000)
			m_registryWatcher.emplace(this);
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
				auto& wallpaperManager = WallpaperManager::GetInstance();
				if (!wallpaperManager.UpdatedNeeded())
					return;

				try
				{
					TenMicaEffectFactory::GetFactory().Redraw(wallpaperManager);
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
					strong->onDeviceReset(WallpaperManager::GetInstance());
				}
				catch (TenMicaDeviceLostException const&)
				{
					auto& wallpaperManager = WallpaperManager::GetInstance(true);
					std::ignore = wallpaperManager.UpdatedNeeded();
					strong->onDeviceReset(wallpaperManager);
				}
			}
		});
	}

	TenMicaEffect& TenMicaBackdrop::getEffect()
	{
		if (!m_effect)
			m_effect.emplace(TenMicaEffectFactory::GetFactory().Get());
		
		return *m_effect;
	}

	void TenMicaBackdrop::getVirtualScreenXY()
	{
		m_virtualScreenX = GetSystemMetrics(SM_XVIRTUALSCREEN);
		m_virtualScreenY = GetSystemMetrics(SM_YVIRTUALSCREEN);
	}

	void TenMicaBackdrop::onDeviceReset(WallpaperManager& wallpaperManager)
	{
		TenMicaEffectFactory::GetFactory().OnDeviceLost(getEffect(), wallpaperManager);
		RECT windowRect;
		winrt::check_bool(GetWindowRect(m_hwnd, &windowRect));
		updateBrushOffset(windowRect.left, windowRect.top);
	}

}
