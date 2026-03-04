#include "pch.h"
#include "TenMicaRegistryWatcher.h"
#include "TenMicaBackdrop.h"

std::wstring TenMicaRegistryWatcher::getWallpaperValue()
{
	return wil::reg::get_value_string(HKEY_CURRENT_USER, LR"(Control Panel\Desktop)", L"Wallpaper");
}

void TenMicaRegistryWatcher::threadProc()
{
	while (!m_requestStop)
	{
		auto value = getWallpaperValue();;
		if (WallPaperValue != value)
		{
			WallPaperValue = std::move(value);
			m_impl->onWallpaperChanged();
		}
		std::this_thread::sleep_for(std::chrono::seconds{ 1 });
	}
}

TenMicaRegistryWatcher::TenMicaRegistryWatcher(winrt::WinUI3Package::implementation::TenMicaBackdrop* impl)
	: m_impl{impl},
	m_thread{std::jthread{&TenMicaRegistryWatcher::threadProc, this}}
{
}

TenMicaRegistryWatcher::~TenMicaRegistryWatcher()
{
	m_requestStop = true;
}
