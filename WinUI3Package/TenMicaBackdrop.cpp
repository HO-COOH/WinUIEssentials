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
			m_effect.SetTheme(sender.ActualTheme() == winrt::Microsoft::UI::Xaml::ElementTheme::Light);
        });
		m_effect.SetTheme(value.ActualTheme() == winrt::Microsoft::UI::Xaml::ElementTheme::Light);
    }

    void TenMicaBackdrop::OnTargetConnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget, winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot)
    {
		getVirtualScreenXY();
		onWallpaperChanged();
        connectedTarget.SystemBackdrop(m_effect.m_finalCrossFadeBrush);
		auto const hwnd = GetHwnd(xamlRoot);
		RECT windowRect;
		winrt::check_bool(GetWindowRect(hwnd, &windowRect));
		updateBrushOffset(windowRect.left, windowRect.top);
		addSubClass(hwnd);
		if (GetWindowsVersion().dwMajorVersion >= 22000)
			m_registryWatcher.emplace(this);
		m_savedTarget = connectedTarget;
    }

	void TenMicaBackdrop::OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget)
	{
		removeSubClass();
		m_registryWatcher.reset();
		connectedTarget.SystemBackdrop(nullptr);
	}

	void TenMicaBackdrop::updateBrushOffset(int windowX, int windowY)
	{
		float const offsetX = m_virtualScreenX - windowX;
		float const offsetY = m_virtualScreenY - windowY;
		m_effect.SetBrushOffset(offsetX, offsetY);
	}

	void TenMicaBackdrop::onWindowActivated(bool isActive)
	{
		if (EnableWhenInactive())
			return;

		m_effect.SetActive(isActive);
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
					strong->onDeviceReset();
				}
			}
		});
	}

	void TenMicaBackdrop::onDisplayChanged()
	{
		getVirtualScreenXY();
		applyNewBrush(false);
	}

	void TenMicaBackdrop::getVirtualScreenXY()
	{
		m_virtualScreenX = GetSystemMetrics(SM_XVIRTUALSCREEN);
		m_virtualScreenY = GetSystemMetrics(SM_YVIRTUALSCREEN);
	}

	void TenMicaBackdrop::onDeviceReset()
	{
		applyNewBrush(true);
		RECT windowRect;
		winrt::check_bool(GetWindowRect(m_hwnd, &windowRect));
		updateBrushOffset(windowRect.left, windowRect.top);
	}

	void TenMicaBackdrop::applyNewBrush(bool recreateFactory)
	{
		m_effect = TenMicaEffectFactory::GetFactory(recreateFactory).Get();
		if (auto bindThemeTo = m_bindThemeTo.get())
			m_effect.SetTheme(bindThemeTo.ActualTheme() == winrt::Microsoft::UI::Xaml::ElementTheme::Light);
		if (m_savedTarget)
			m_savedTarget.SystemBackdrop(m_effect.m_finalCrossFadeBrush);
	}
}
