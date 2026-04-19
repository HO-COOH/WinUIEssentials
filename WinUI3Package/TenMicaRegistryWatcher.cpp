#include "pch.h"
#include "TenMicaRegistryWatcher.h"
#include "TenMicaBackdrop.h"

bool TenMicaRegistryWatcher::wallpaperChanged()
{
	if (!m_watchValue.wallpaper)
		return false;

	auto value = TenMicaRegistry::Wallpaper();
	if (WallPaperValue == value)
		return false;

	WallPaperValue = std::move(value);
	return true;
}

bool TenMicaRegistryWatcher::transcodedImageChanged()
{
	if (!m_watchValue.transcodedImageCache)
		return false;

	auto value = TenMicaRegistry::TranscodedImageCaches();
	if (transcodedImagesValue == value)
		return false;

	transcodedImagesValue = std::move(value);
	return true;
}

bool TenMicaRegistryWatcher::backgroundChanged()
{
	if(!m_watchValue.background)
		return false;

	auto value = TenMicaRegistry::BackgroundValue();
	if (BackgroundValue == value)
		return false;

	BackgroundValue = std::move(value);
	return true;
}

void TenMicaRegistryWatcher::threadProc()
{
	while (!m_requestStop)
	{
		if (wallpaperChanged() || transcodedImageChanged() || backgroundChanged())
			m_impl->onWallpaperChanged();
		std::this_thread::sleep_for(std::chrono::seconds{ 1 });
	}
}

TenMicaRegistryWatcher::TenMicaRegistryWatcher(winrt::WinUI3Package::implementation::TenMicaBackdrop* impl, WatchValue watchValue)
	: m_impl{impl},
	m_watchValue{watchValue},
	m_thread{std::jthread{&TenMicaRegistryWatcher::threadProc, this}}
{
}

TenMicaRegistryWatcher::~TenMicaRegistryWatcher()
{
	m_requestStop = true;
}
