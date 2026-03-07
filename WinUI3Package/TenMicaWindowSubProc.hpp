#pragma once

template<typename Derived>
class TenMicaWindowSubProc
{
	static auto getThis(DWORD_PTR dwRefData)
	{
		return reinterpret_cast<TenMicaWindowSubProc*>(dwRefData);
	}

	constexpr auto getDerivedThis()
	{
		return static_cast<Derived*>(this);
	}

	int m_borderPadding{};

	WORD m_dpi = 96;

	void updateBorderPadding()
	{
		m_borderPadding = GetSystemMetricsForDpi(SM_CXFRAME, m_dpi) + GetSystemMetricsForDpi(SM_CXPADDEDBORDER, m_dpi);
	}
protected:
	HWND m_hwnd;

	static LRESULT CALLBACK subclassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		switch (msg)
		{
			case WM_WINDOWPOSCHANGING:
			{
				auto* windowPos = reinterpret_cast<WINDOWPOS const*>(lParam);
				
				//Only update if position actually changed (not just size or z-order)
				if (!(windowPos->flags & SWP_NOMOVE))
				{
					auto* pThis = getThis(dwRefData);
				pThis->getDerivedThis()->updateBrushOffset(
					windowPos->x + pThis->m_borderPadding,
					windowPos->y + (IsZoomed(hwnd) ? pThis->m_borderPadding : 0)
				);
				}
				break;
			}
			case WM_DPICHANGED:
			{
				auto* suggestedRect = reinterpret_cast<RECT const*>(lParam);
				auto* pThis = getThis(dwRefData);
				pThis->m_dpi = HIWORD(wParam);
				pThis->updateBorderPadding();
				pThis->getDerivedThis()->updateBrushOffset(
					suggestedRect->left + pThis->m_borderPadding,
					suggestedRect->top + (IsZoomed(hwnd) ? pThis->m_borderPadding : 0)
				);
				break;
			}
			case WM_ACTIVATE:
			{
				auto const isActive = (LOWORD(wParam) != WA_INACTIVE);
				getThis(dwRefData)->getDerivedThis()->onWindowActivated(isActive);
				break;
			}
			//This works fine on Windows 10, but NOT on Windows 11
			//See this link: https://learn.microsoft.com/en-us/answers/questions/5771029/windows-11-changing-wallpaper-in-the-settings-app
			//We need to use registry watcher to monitor wallpaper registry key on Windows 11
			case WM_SETTINGCHANGE:
			{
				if (wParam == SPI_SETDESKWALLPAPER)
					getThis(dwRefData)->getDerivedThis()->onWallpaperChanged();
				break;
			}
			case WM_DISPLAYCHANGE:
			{
				getThis(dwRefData)->getDerivedThis()->onDisplayChanged();
				break;
			}
			case WM_NCDESTROY:
				// Remove subclass before window is destroyed
				RemoveWindowSubclass(hwnd, subclassProc, uIdSubclass);
				break;
		}

		return DefSubclassProc(hwnd, msg, wParam, lParam);
	}

public:
	void removeSubClass()
	{
		RemoveWindowSubclass(m_hwnd, subclassProc, 0);
	}

	void addSubClass(HWND hwnd)
	{
		m_hwnd = hwnd;
		m_dpi = GetDpiForWindow(hwnd);
		updateBorderPadding();
		SetWindowSubclass(m_hwnd, subclassProc, 0, reinterpret_cast<DWORD_PTR>(this));
	}
};