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
	winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutShowOptions GetFlyoutShowOptions(
		HWND hwnd,
		LPARAM lparam,
		winrt::Microsoft::UI::Content::ContentCoordinateConverter const& converter
	);
}
