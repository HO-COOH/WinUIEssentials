#pragma once
#include <winrt/Windows.System.h>

class EnsureSystemDispatcherQueueController
{
	winrt::Windows::System::DispatcherQueueController m_controller{ nullptr };
public:
	EnsureSystemDispatcherQueueController();
};
