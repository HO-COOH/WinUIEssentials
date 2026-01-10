#pragma once
#include <winrt/Microsoft.UI.Xaml.h>

struct LayoutUpdateAwaiter
{
	winrt::Microsoft::UI::Xaml::FrameworkElement m_target;
	winrt::Microsoft::UI::Xaml::FrameworkElement::LayoutUpdated_revoker m_revoker;
	bool m_completed = false;

	LayoutUpdateAwaiter(winrt::Microsoft::UI::Xaml::FrameworkElement const& target) : m_target(target) 
	{
	}

	bool await_ready()
	{
		return false;
	}

	void await_suspend(std::coroutine_handle<> handle)
	{
		m_revoker = m_target.LayoutUpdated(winrt::auto_revoke, [this, handle](auto&&...)
		{
			if (!m_completed)
			{
				m_completed = true;
				m_revoker.revoke();
				handle.resume();
			}
		});
		m_target.UpdateLayout();
	}

	void await_resume() 
	{
	}
};