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
	TenMicaBackdrop::TenMicaBackdrop(winrt::Microsoft::UI::Xaml::FrameworkElement const& bindThemeTo) : 
		m_bindThemeTo{ bindThemeTo }, 
		m_bindThemeRevoker{ bindThemeTo.ActualThemeChanged(winrt::auto_revoke, [this](winrt::Microsoft::UI::Xaml::FrameworkElement const& sender, auto&&)
		{
			if (m_effect)
				m_effect->SetTheme(sender.ActualTheme());
		}) }
	{
		if (m_effect)
			m_effect->SetTheme(bindThemeTo.ActualTheme());
	}

	winrt::Microsoft::UI::Xaml::FrameworkElement TenMicaBackdrop::BindThemeTo()
    {
        return m_bindThemeTo.get();
    }

    void TenMicaBackdrop::BindThemeTo(winrt::Microsoft::UI::Xaml::FrameworkElement const& value)
    {
        m_bindThemeTo = value;
        m_bindThemeRevoker = value.ActualThemeChanged(winrt::auto_revoke, [this](winrt::Microsoft::UI::Xaml::FrameworkElement const& sender, auto&&)
        {
			if (m_effect)
				m_effect->SetTheme(sender.ActualTheme());
        });

		if (m_effect)
			m_effect->SetTheme(value.ActualTheme());
    }

    void TenMicaBackdrop::OnTargetConnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget, winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot)
    {
		m_target = connectedTarget;
		try
		{
			getVirtualScreenXY();
			bool const hadEffect = m_effect.has_value();
			auto& effect = getEffect();
			if (effect.IsFallback())
			{
				fallbackToInactiveBrush();
				return;
			}

			if (hadEffect)
				onWallpaperChanged();

			if (auto bindThemeTo = m_bindThemeTo.get())
				effect.SetTheme(bindThemeTo.ActualTheme());
			connectedTarget.SystemBackdrop(effect.m_finalCrossFadeBrush);
			auto const hwnd = GetHwnd(xamlRoot);
			RECT windowRect;
			winrt::check_bool(GetWindowRect(hwnd, &windowRect));
			updateBrushOffset(windowRect.left, windowRect.top);
			addSubClass(hwnd);
			m_registryWatcher.emplace(
				this,
				GetWindowsVersion().dwMajorVersion >= 22000 ?
				TenMicaRegistryWatcher::WatchValue{ true, true, true } :
				TenMicaRegistryWatcher::WatchValue{ .background = true, .transcodedImageCache = true }
			);
		}
		catch (...)
		{
			fallbackToInactiveBrush();
		}
    }

	void TenMicaBackdrop::OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget)
	{
		removeSubClass();
		m_registryWatcher.reset();
		m_target = nullptr;
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
				if (!strong->m_target.get() || (strong->m_effect && strong->m_effect->IsFallback()))
					return;

				try
				{
					if (!strong->m_factory->GetWallpaperManager().UpdatedNeeded())
						return;

					strong->m_factory->Redraw();
				}
				catch (TenMicaDeviceLostException const&)
				{
					//no need to handle it here
				}
				catch (...)
				{
					strong->fallbackToInactiveBrush();
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
				if (!strong->m_target.get() || (strong->m_effect && strong->m_effect->IsFallback()))
					return;

				try
				{
					try
					{
						strong->onDeviceReset();
					}
					catch (TenMicaDeviceLostException const&)
					{
						std::ignore = strong->m_factory->GetWallpaperManager().UpdatedNeeded();
						strong->onDeviceReset();
					}
				}
				catch (...)
				{
					strong->fallbackToInactiveBrush();
				}
			}
		});
	}

	void TenMicaBackdrop::onWatcherError() noexcept
	{
		m_queue.TryEnqueue([weakThis = get_weak()]
		{
			if (auto strong = weakThis.get())
				strong->fallbackToInactiveBrush();
		});
	}

	TenMicaEffect& TenMicaBackdrop::getEffect()
	{
		if (!m_effect)
			m_effect.emplace(m_factory->Get());
		
		return *m_effect;
	}

	void TenMicaBackdrop::fallbackToInactiveBrush() noexcept
	{
		removeSubClass();
		m_registryWatcher.reset();

		try
		{
			if (!m_effect)
				m_effect.emplace(m_factory->GetFallback());
			else
				m_effect->FallbackToInactiveBrush();

			if (auto bindThemeTo = m_bindThemeTo.get())
				m_effect->SetTheme(bindThemeTo.ActualTheme());

			if (auto target = m_target.get())
				target.SystemBackdrop(m_effect->m_inactiveBrush);
		}
		catch (...)
		{
		}
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
