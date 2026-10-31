#pragma once
namespace winrt::WinUI3Package::implementation
{
	struct ModernWindowCaptionButtonToolTip;
}


class InputSourceBase
{
protected:
	winrt::WinUI3Package::implementation::ModernWindowCaptionButtonToolTip& m_captionButtonTooltip;
	HWND m_hwnd; //sink hwnd in InputNonClientPointerSource OR host hwnd in ClassicTitleBarInputSource


	InputSourceBase(winrt::WinUI3Package::implementation::ModernWindowCaptionButtonToolTip& owner, HWND window);

	[[nodiscard]] bool isPointerOver() const;

	void onPointerPressed();
};