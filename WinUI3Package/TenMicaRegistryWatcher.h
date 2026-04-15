#pragma once
#include "TenMicaRegistry.h"
#include <atomic>
#include <thread>
#include <boost/container/small_vector.hpp>

namespace winrt::WinUI3Package::implementation
{
	struct TenMicaBackdrop;
}

//This have to use polling because a packaged winui3 app has registry virtualization
//meaning a registry watcher will NOT work!
class TenMicaRegistryWatcher
{
public:
	struct WatchValue
	{
		bool wallpaper{};
		bool background{};
		bool transcodedImageCache{};
	};

	TenMicaRegistryWatcher(winrt::WinUI3Package::implementation::TenMicaBackdrop* impl, WatchValue watchValue);
	~TenMicaRegistryWatcher();

private:
	using SmallVector = boost::container::small_vector<std::vector<uint8_t>, TenMicaRegistry::MonitorCountEstimate>;

	std::wstring WallPaperValue = TenMicaRegistry::Wallpaper();
	std::wstring BackgroundValue = TenMicaRegistry::BackgroundValue();
	SmallVector transcodedImagesValue = TenMicaRegistry::TranscodedImageCaches();


	winrt::WinUI3Package::implementation::TenMicaBackdrop* m_impl{};
	std::atomic_bool m_requestStop = false;
	WatchValue m_watchValue;
	std::jthread m_thread;

	bool wallpaperChanged();
	bool transcodedImageChanged();
	bool backgroundChanged();

	void threadProc();
};