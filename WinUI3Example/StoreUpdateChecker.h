#pragma once
#include <winrt/Windows.Services.Store.h>
#include <optional>

namespace winrt::Microsoft::UI::Xaml
{
	class Window;
}

class StoreUpdateChecker
{
	winrt::Windows::Services::Store::StoreContext m_storeContext = winrt::Windows::Services::Store::StoreContext::GetDefault();
	
	static StoreUpdateChecker& instance();
public:
	static winrt::fire_and_forget checkUpdate(winrt::Microsoft::UI::Xaml::Window const& window);
};