#pragma once
#include <CommCtrl.h>
template<typename Derived, UINT_PTR SubclassId>
class BackdropWindowActiveStateWorkaroundHandler
{
    static LRESULT CALLBACK windowActiveStateWorkaroundHandler(HWND hWnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam,
        UINT_PTR,
        DWORD_PTR dwRefData)
    {
		if (uMsg == WM_SETFOCUS || (uMsg == WM_NCACTIVATE && wParam))
		{
			auto self = reinterpret_cast<Derived*>(dwRefData);
			self->m_configuration.IsInputActive(true);
		}
		else if (uMsg == WM_KILLFOCUS || (uMsg == WM_NCACTIVATE && !wParam))
		{
			auto self = reinterpret_cast<Derived*>(dwRefData);
			self->m_configuration.IsInputActive(self->EnableWhenInactive());
		}
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
    }
public:
	static void Set(HWND hwnd, Derived* self)
	{
		winrt::check_bool(SetWindowSubclass(
			hwnd,
			&BackdropWindowActiveStateWorkaroundHandler<Derived, SubclassId>::windowActiveStateWorkaroundHandler,
			SubclassId,
			reinterpret_cast<DWORD_PTR>(self)
		));
	}

	static void Unset(HWND hwnd)
	{
		RemoveWindowSubclass(hwnd, &BackdropWindowActiveStateWorkaroundHandler<Derived, SubclassId>::windowActiveStateWorkaroundHandler, SubclassId);
	}
};