#pragma once
#include <wil/registry.h>
#include <atomic>
#include <thread>

namespace winrt::WinUI3Package::implementation
{
	struct TenMicaBackdrop;
}

//This have to use polling because a packaged winui3 app has registry virtualization
//meaning a registry watcher will NOT work!
class TenMicaRegistryWatcher
{
	std::wstring WallPaperValue = getWallpaperValue();
	winrt::WinUI3Package::implementation::TenMicaBackdrop* m_impl{};
	std::atomic_bool m_requestStop = false;
	std::jthread m_thread;

	static std::wstring getWallpaperValue();

	void threadProc();
public:
	TenMicaRegistryWatcher(winrt::WinUI3Package::implementation::TenMicaBackdrop* impl);
	~TenMicaRegistryWatcher();
};