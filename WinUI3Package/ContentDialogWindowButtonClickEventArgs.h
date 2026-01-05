#pragma once

#include "ContentDialogWindowButtonClickEventArgs.g.h"

namespace winrt::WinUI3Package::implementation
{
	struct ContentDialogWindowButtonClickEventArgs : ContentDialogWindowButtonClickEventArgsT<ContentDialogWindowButtonClickEventArgs>,
		deferrable_event_args<ContentDialogWindowButtonClickEventArgs>
	{
		ContentDialogWindowButtonClickEventArgs();


		bool Cancel();
		void Cancel(bool Value);

		bool Handled();
		void Handled(bool Value);

	private:
		bool m_Cancel{};
		bool m_Handled{};
	};
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct ContentDialogWindowButtonClickEventArgs : ContentDialogWindowButtonClickEventArgsT<ContentDialogWindowButtonClickEventArgs, implementation::ContentDialogWindowButtonClickEventArgs>
    {
    };
}
