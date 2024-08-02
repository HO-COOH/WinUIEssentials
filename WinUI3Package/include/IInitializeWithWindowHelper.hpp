#pragma once
#include <winrt/Windows.Devices.Enumeration.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <ShObjIdl.h>

namespace WinUIEssentials::Windows
{
	namespace internal
	{
		template<typename T>
		struct IInitializeWithWindowConstructorHelper : T
		{
			IInitializeWithWindowConstructorHelper(HWND hwnd)
			{
				T::template as<IInitializeWithWindow>()->Initialize(hwnd);
			}
		};
	}

	namespace Devices
	{
		namespace Enumeration
		{
			using DevicePicker = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::Devices::Enumeration::DevicePicker>;
		}
	}

	namespace Storage::Pickers
	{
		using FileOpenPicker = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::Storage::Pickers::FileOpenPicker>;
	}
}