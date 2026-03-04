#include "pch.h"
#include "ContentDialogWindowButtonClickEventArgs.h"
#if __has_include("ContentDialogWindowButtonClickEventArgs.g.cpp")
#include "ContentDialogWindowButtonClickEventArgs.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	ContentDialogWindowButtonClickEventArgs::ContentDialogWindowButtonClickEventArgs() {

		Cancel(false);
		Handled(false);
	}

	bool ContentDialogWindowButtonClickEventArgs::Cancel()
	{
		return m_Cancel;
	}

	void ContentDialogWindowButtonClickEventArgs::Cancel(bool Value)
	{
		m_Cancel = Value;
	}

	bool ContentDialogWindowButtonClickEventArgs::Handled()
	{
		return m_Handled;
	}

	void ContentDialogWindowButtonClickEventArgs::Handled(bool Value)
	{
		m_Handled = Value;
	}
}
