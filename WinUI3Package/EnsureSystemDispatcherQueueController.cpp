#include "pch.h"
#include <DispatcherQueue.h>
#include "EnsureSystemDispatcherQueueController.h"

EnsureSystemDispatcherQueueController::EnsureSystemDispatcherQueueController()
{
	if (winrt::Windows::System::DispatcherQueue::GetForCurrentThread())
		return;

	m_controller = []
	{
		DispatcherQueueOptions options
		{
			sizeof(DispatcherQueueOptions),
			DQTYPE_THREAD_CURRENT,
			DQTAT_COM_STA
		};

		::ABI::Windows::System::IDispatcherQueueController* ptr{ nullptr };
		winrt::check_hresult(CreateDispatcherQueueController(options, &ptr));
		return winrt::Windows::System::DispatcherQueueController{ ptr, winrt::take_ownership_from_abi };
	}();
}