#include "pch.h"
#include "NonMaximizableWindowWorkaround.h"
#if __has_include("NonMaximizableWindowWorkaround.g.cpp")
#include "NonMaximizableWindowWorkaround.g.cpp"
#endif
#include "HwndHelper.hpp"
#include "CommCtrl.h"

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::Window NonMaximizableWindowWorkaround::Window()
	{
		return m_window.get();
	}

	NonMaximizableWindowWorkaround::~NonMaximizableWindowWorkaround()
	{
		if (m_registered && m_hwnd)
		{

		}
	}

	void NonMaximizableWindowWorkaround::Window(winrt::Microsoft::UI::Xaml::Window const& value)
	{
		m_window = value;
		if (m_isMaximizable)
			set();
	}

	bool NonMaximizableWindowWorkaround::IsMaximizable()
	{
		return *m_isMaximizable;
	}

	void NonMaximizableWindowWorkaround::IsMaximizable(bool value)
	{
		m_isMaximizable = value;
		if (m_window.get())
		{
			if (m_isMaximizable)
				set();
		}
	}

	void NonMaximizableWindowWorkaround::setSubClassIfNeeded()
	{
		if (m_registered)
			return;


		if (SetWindowSubclass(m_hwnd, &subclassProc, SubClassId, reinterpret_cast<DWORD_PTR>(this)))
		{
			m_registered = true;
		}
	}

	LRESULT CALLBACK NonMaximizableWindowWorkaround::subclassProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		if (uIdSubclass != SubClassId)
			return DefSubclassProc(hwnd, msg, wparam, lparam);

		if (msg == WM_SYSCOMMAND && wparam == SC_MAXIMIZE)
		{
			auto ptr = reinterpret_cast<NonMaximizableWindowWorkaround*>(dwRefData);
			if (!*ptr->m_isMaximizable)
				return 1;
		}
		if (msg == WM_NCDESTROY)
		{
			// Remove subclass before window is destroyed
			RemoveWindowSubclass(hwnd, subclassProc, uIdSubclass);
			auto ptr = reinterpret_cast<NonMaximizableWindowWorkaround*>(dwRefData);
			ptr->m_registered = false;
			return DefSubclassProc(hwnd, msg, wparam, lparam);
		}

		return DefSubclassProc(hwnd, msg, wparam, lparam);
	}

	void NonMaximizableWindowWorkaround::set()
	{
		auto window = m_window.get();
		if (!window) 
			return;
		m_hwnd = GetHwnd(window);
		SetWindowLongPtr(
			m_hwnd,
			GWL_STYLE,
			*m_isMaximizable ?
			GetWindowLongPtr(m_hwnd, GWL_STYLE) | WS_MAXIMIZEBOX :
			GetWindowLongPtr(m_hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX
		);
		setSubClassIfNeeded();
	}
}
