#include "pch.h"
#include "WinUIAsyncEventArgs.h"
#if __has_include("WinUIAsyncEventArgs.g.cpp")
#include "WinUIAsyncEventArgs.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
 
	bool WinUIAsyncEventArgs::Cancel()
	{
		return m_Cancel;
	}

	void WinUIAsyncEventArgs::Cancel(bool Value)
	{
		m_Cancel = Value;
	}

}
