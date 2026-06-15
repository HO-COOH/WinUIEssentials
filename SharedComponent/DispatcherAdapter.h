#pragma once
#if defined Build_WinUIPackage
#include <winrt/Microsoft.UI.Dispatching.h>
#else
#include <winrt/Windows.UI.Core.h>
#endif

class DispatcherAdapter
{
#if defined Build_WinUIPackage
	winrt::Microsoft::UI::Dispatching::DispatcherQueue m_dispatcher{ nullptr };
#else
	winrt::Windows::UI::Core::CoreDispatcher m_dispatcher{ nullptr };
#endif
public:
	DispatcherAdapter() = default;

	DispatcherAdapter(auto&& element) : m_dispatcher
	{
#if defined Build_WinUIPackage
		element.DispatcherQueue()
#else
		element.Dispatcher()
#endif
	}
	{
	}

	void TryEnqueue(auto&& func)
	{
#if defined Build_WinUIPackage
		m_dispatcher.TryEnqueue(func);
#else
		m_dispatcher.RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, func);
#endif
	}

#if defined Build_WinUIPackage
	auto CreateTimer()
	{
		return m_dispatcher.CreateTimer();
	}
#endif
};