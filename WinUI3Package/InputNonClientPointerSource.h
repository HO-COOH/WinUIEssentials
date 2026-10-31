#pragma once
#include <Windows.h>
#include "InputSourceBase.hpp"
//pch.h already pulled in <windows.h> without NOMINMAX, so hide its min/max macros from tiny/optional.h
#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max
#include <tiny/optional.h>
#pragma pop_macro("max")
#pragma pop_macro("min")

class InputNonClientPointerSource : public InputSourceBase
{
	DWORD m_strippedStyle{};
	tiny::optional<UINT32, (std::numeric_limits<UINT32>::max)()> m_pressedPointerId;
	LRESULT m_lastHitTest{ HTNOWHERE };
	bool m_isSettingStyle{};


	[[nodiscard]] static bool isNonClientInputSink(HWND hwnd);
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
	
	using InputSourceBase::onPointerPressed;
	void onPointerPressed(UINT32 pointerId);
	bool isPressed();

	void detach();

	void disableMinimizeAndMaximizeTooltipByStyle();
public:
	InputNonClientPointerSource(winrt::WinUI3Package::implementation::ModernWindowCaptionButtonToolTip& owner, HWND sink);
	~InputNonClientPointerSource();
	InputNonClientPointerSource(InputNonClientPointerSource const&) = delete;

	//This is only found when `ExtendsContentIntoTitleBar` is enabled
	[[nodiscard]] static HWND Find(HWND window);

	//Screen y of the caption's top edge, or fallback when it is unknown
	[[nodiscard]] LONG CaptionTop(LONG fallback) const;
};