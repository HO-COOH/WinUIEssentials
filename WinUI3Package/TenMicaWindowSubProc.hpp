#pragma once
#include <CommCtrl.h>
#include <DpiUtils.hpp>

class TenMicaWindowSubProc
{
	template<typename Derived>
	static auto getThis(DWORD_PTR dwRefData)
	{
		return reinterpret_cast<Derived*>(dwRefData);
	}

	int m_borderPadding{};

	UINT m_dpi = DpiUtils::DefaultDpi;

	void updateBorderPadding();
	static UINT taskbarCreatedMessage();

	template<typename Derived>
	static LRESULT CALLBACK subclassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR, DWORD_PTR dwRefData)
	{
		switch (msg)
		{
			case WM_WINDOWPOSCHANGING:
			{
				auto* windowPos = reinterpret_cast<WINDOWPOS const*>(lParam);

				//Only update if position actually changed (not just size or z-order)
				if (!(windowPos->flags & SWP_NOMOVE))
				{
					auto* pThis = getThis<Derived>(dwRefData);
					pThis->updateBrushOffset(
						windowPos->x + pThis->m_borderPadding,
						windowPos->y + (IsZoomed(hwnd) ? pThis->m_borderPadding : 0)
					);
				}
				break;
			}
			case WM_DPICHANGED:
			{
				auto* suggestedRect = reinterpret_cast<RECT const*>(lParam);
				auto* pThis = getThis<Derived>(dwRefData);
				pThis->m_dpi = HIWORD(wParam);
				pThis->updateBorderPadding();
				pThis->updateBrushOffset(
					suggestedRect->left + pThis->m_borderPadding,
					suggestedRect->top + (IsZoomed(hwnd) ? pThis->m_borderPadding : 0)
				);
				break;
			}
			case WM_ACTIVATE:
			{
				auto const isActive = (LOWORD(wParam) != WA_INACTIVE);
				getThis<Derived>(dwRefData)->onWindowActivated(isActive);
				break;
			}
			//This works fine on Windows 10, but NOT on Windows 11
			//See this link: https://learn.microsoft.com/en-us/answers/questions/5771029/windows-11-changing-wallpaper-in-the-settings-app
			//We need to use registry watcher to monitor wallpaper registry key on Windows 11
			case WM_SETTINGCHANGE:
				if (wParam == SPI_SETDESKWALLPAPER)
					getThis<Derived>(dwRefData)->onWallpaperChanged();
				break;
			case WM_DISPLAYCHANGE:
				getThis<Derived>(dwRefData)->onDisplayChanged();
				break;
			case WM_NCDESTROY:
				// Remove subclass before window is destroyed
				getThis<Derived>(dwRefData)->removeSubClass();
				break;
			default:
				if (msg >= 0xC000 && msg == taskbarCreatedMessage())
					getThis<Derived>(dwRefData)->onWallpaperChanged();
				break;
		}

		return DefSubclassProc(hwnd, msg, wParam, lParam);
	}
protected:
	HWND m_hwnd{};

	template<typename Derived>
	void removeSubClass(this Derived& self)
	{
		if (self.m_hwnd)
		{
			RemoveWindowSubclass(self.m_hwnd, &subclassProc<Derived>, 0);
			self.m_hwnd = nullptr;
		}
	}

	template<typename Derived>
	void addSubClass(this Derived& self, HWND hwnd)
	{
		self.m_hwnd = hwnd;
		self.m_dpi = GetDpiForWindow(hwnd);
		self.updateBorderPadding();
		ChangeWindowMessageFilterEx(self.m_hwnd, taskbarCreatedMessage(), MSGFLT_ALLOW, nullptr);
		SetWindowSubclass(self.m_hwnd, &subclassProc<Derived>, 0, reinterpret_cast<DWORD_PTR>(&self));
	}
};
