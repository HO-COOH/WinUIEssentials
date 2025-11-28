#pragma once
#include <Windows.h>

#pragma region ForwardDeclaration
namespace winrt::Microsoft::UI
{
	namespace Xaml::Controls::Primitives
	{
		struct FlyoutShowOptions;
	}

	namespace Content
	{
		struct ContentCoordinateConverter;
	}
}
#pragma endregion

namespace WindowContextMenuUtils
{
	/**
	 * @brief Get show options for Window's context menu when a mouse event is triggered, eg. WM_NCRBUTTONDOWN, WM_NCRBUTTONUP, WM_CONTEXTMENU
	 * @param hwnd the window handle of the mouse event
	 * @param lparam This should be the lparam of the mouse event, that is a `POINT` struct
	 * @param converter This should ba a `Microsoft.UI.Content.ContentCoordinateConverter` converter that 
	 * convert the global coordinate of `lparam` to the local coordinate of the window that `MenuFlyout.ShowAt ` uses. This should be created by `ContentCoordinateConverter::CreateForWindowId` and store as a member variable
	 */
	winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutShowOptions GetFlyoutShowOptions(
		HWND hwnd,
		LPARAM lparam,
		winrt::Microsoft::UI::Content::ContentCoordinateConverter const& converter
	);
}
