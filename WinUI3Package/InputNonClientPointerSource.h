#pragma once
#include <Windows.h>

//pch.h already pulled in <windows.h> without NOMINMAX, so hide its min/max macros from tiny/optional.h
#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max
#include <tiny/optional.h>
#pragma pop_macro("max")
#pragma pop_macro("min")

namespace winrt::WinUI3Package::implementation
{
	struct ModernWindowCaptionButtonToolTip;
}

class InputNonClientPointerSource
{
	HWND m_hwnd{};
	DWORD m_strippedStyle{};
	tiny::optional<UINT32, (std::numeric_limits<UINT32>::max)()> m_pressedPointerId;
	LRESULT m_lastHitTest{ HTNOWHERE };
	winrt::WinUI3Package::implementation::ModernWindowCaptionButtonToolTip* m_captionButtonTooltip{};
	bool m_isSettingStyle{};


	[[nodiscard]] static bool isNonClientInputSink(HWND hwnd);
	[[nodiscard]] static HWND find(HWND parent);
	constexpr static UINT_PTR SubclassId = 103;

	LRESULT onSubclassMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static LRESULT CALLBACK nonClientInputSinkSubclassProc(
		HWND hwnd,
		UINT msg,
		WPARAM wparam,
		LPARAM lparam,
		UINT_PTR uIdSubclass,
		DWORD_PTR dwRefData
	);
	LRESULT restoreHitTest(LRESULT hitTest) const;
	void onPointerPressed(UINT32 pointerId);
	void onPointerPressed();
	bool isPressed();

	void detach();

	void disableMinimizeAndMaximizeTooltipByStyle();
public:
	InputNonClientPointerSource(winrt::WinUI3Package::implementation::ModernWindowCaptionButtonToolTip* owner);

	//Return whether it is successful
	bool Initialize(HWND parent);

	[[nodiscard]] bool IsPointerOver() const;
	
	constexpr operator HWND() const noexcept
	{
		return m_hwnd;
	}

	constexpr operator bool() const noexcept
	{ 
		return m_hwnd;
	}

	constexpr auto LastHitTest() const noexcept
	{
		return m_lastHitTest;
	}
};