#pragma once
#include <CommCtrl.h>

/**
 * @brief This is a workaround helper for setting backdrop state to inactive when the window becomes inactive
 * @example CustomAcrylicBackdrop.cpp
 * @note `Derived` class needs to have a member: `winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration m_configuration;`
 *  and declared a friend to this class
 * @tparam Derived The derived class, usually an implementation class, and because of that, you usually do not need to specify the `implementation` namespace
 * @code{.cpp}
 * //Example usage:
 * struct MyBackdrop
 * {
 *		void OnTargetConnected(...)
 *		{
 *			//...
 *			BackdropWindowActiveStateWorkaroundHandler<MyBackdrop, subclassId>::Set(hwnd, this);
 *		}
 * 
 *		void OnTargetDisconnected(...)
 *		{
 *			//...
 *			BackdropWindowActiveStateWorkaroundHandler<MyBackdrop, subclassId>::Unset(hwnd, this);
 *		}
 * };
 * @endcode
 */
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

	/**
	 * Set window subclass for this workaround
	 * 
	 * @param hwnd the window handle
	 * @param self the backdrop derived class instance pointer
	 */
	static void Set(HWND hwnd, Derived* self)
	{
		winrt::check_bool(SetWindowSubclass(
			hwnd,
			&BackdropWindowActiveStateWorkaroundHandler<Derived, SubclassId>::windowActiveStateWorkaroundHandler,
			SubclassId,
			reinterpret_cast<DWORD_PTR>(self)
		));
	}

	/**
	 * Unset window subclass for this workaround
	 * 
	 * @param hwnd the window handle
	 */
	static void Unset(HWND hwnd)
	{
		RemoveWindowSubclass(hwnd, &BackdropWindowActiveStateWorkaroundHandler<Derived, SubclassId>::windowActiveStateWorkaroundHandler, SubclassId);
	}
};