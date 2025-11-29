#include "pch.h"
#include "StoreUpdateChecker.h"
#include <IInitializeWithWindowHelper.hpp>

StoreUpdateChecker& StoreUpdateChecker::instance()
{
    static StoreUpdateChecker s_instance;
    return s_instance;
}

winrt::fire_and_forget StoreUpdateChecker::checkUpdate(winrt::Microsoft::UI::Xaml::Window const& window)
{
    auto dispatcherQueue = winrt::Microsoft::UI::Dispatching::DispatcherQueue::GetForCurrentThread();
    auto storeContext = WinUIEssentials::InitializeWithWindow(instance().m_storeContext, window);
    auto updates = co_await storeContext.GetAppAndOptionalStorePackageUpdatesAsync();
    if (updates.Size() > 0)
    {
        co_await wil::resume_foreground(dispatcherQueue);
        auto result = co_await storeContext.RequestDownloadAndInstallStorePackageUpdatesAsync(updates);
    }
}
