#pragma once
#include <Windows.h>
#include "InputSourceBase.hpp"
#include <wil/resource.h>

/*
	Caption button input of a window with the system title bar, where the InputNonClientPointerSource sink stays hidden
	and the window itself gets the caption input
*/
class ClassicTitleBarInputSource : public InputSourceBase
{
	wil::unique_hwineventhook m_systemToolTipHook;

	constexpr static UINT_PTR SubclassId = 104;

	LRESULT onSubclassMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static LRESULT CALLBACK subclassProc(
		HWND hwnd,
		UINT msg,
		WPARAM wparam,
		LPARAM lparam,
		UINT_PTR uIdSubclass,
		DWORD_PTR dwRefData
	);
	static void CALLBACK onSystemToolTipShown(
		HWINEVENTHOOK hook,
		DWORD event,
		HWND hwnd,
		LONG idObject,
		LONG idChild,
		DWORD idEventThread,
		DWORD time
	);
	void installSystemToolTipHook();
public:
	ClassicTitleBarInputSource(winrt::WinUI3Package::implementation::ModernWindowCaptionButtonToolTip& owner, HWND mainWindow);
	~ClassicTitleBarInputSource();

	//Screen y of the caption's top edge, or fallback when it is unknown
	[[nodiscard]] LONG CaptionTop(LONG fallback) const;
};
