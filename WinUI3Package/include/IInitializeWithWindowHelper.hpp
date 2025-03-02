#pragma once
#include <winrt/Windows.Devices.Enumeration.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Popups.h>
#include <winrt/Windows.UI.StartScreen.h>
#include <winrt/Windows.Graphics.Capture.h>
#include <winrt/Windows.Media.Casting.h>
#include <winrt/Windows.Media.DialProtocol.h>
#include <ShObjIdl.h>
#if __has_include("HwndHelper.hpp")
#include "HwndHelper.hpp"
#endif

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

#if __has_include("HwndHelper.hpp")
			IInitializeWithWindowConstructorHelper(winrt::Microsoft::UI::Xaml::Window window) :
				IInitializeWithWindowConstructorHelper{ GetHwnd(window) }
			{

			}
#endif
		};

		template<typename T>
		struct IInitializeWithWindowConstructorHelperWithArg : T
		{
			template<typename... Args>
			IInitializeWithWindowConstructorHelperWithArg(HWND hwnd, Args&&... args) : T{std::forward<Args>(args)...}
			{
				T::template as<IInitializeWithWindow>()->Initialize(hwnd);
			}

#if __has_include("HwndHelper.hpp")
			template<typename... Args>
			IInitializeWithWindowConstructorHelperWithArg(winrt::Microsoft::UI::Xaml::Window window, Args&&... args) :
				IInitializeWithWindowConstructorHelperWithArg{ GetHwnd(window), std::forward<Args>(args)... }
			{
			}
#endif
		};
	}

	namespace Devices
	{
		namespace Enumeration
		{
			using DevicePicker = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::Devices::Enumeration::DevicePicker>;
		}
	}

	namespace Graphics::Capture
	{
		using GraphicsCapturePicker = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::Graphics::Capture::GraphicsCapturePicker>;
	}

	namespace Storage::Pickers
	{
		using FileOpenPicker = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::Storage::Pickers::FileOpenPicker>;
		using FileSavePicker = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::Storage::Pickers::FileSavePicker>;
		using FolderPicker = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::Storage::Pickers::FolderPicker>;

	}

	namespace System
	{
		using FolderLauncherOptions = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::System::FolderLauncherOptions>;
		using LauncherOptions = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::System::LauncherOptions>;
	}

	namespace Media
	{
		namespace Casting
		{
			using CastingDevicePicker = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::Media::Casting::CastingDevicePicker>;
		}

		namespace DialProtocol
		{
			using DialDevicePicker = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::Media::DialProtocol::DialDevicePicker>;
		}
	}



	namespace UI	
	{
#ifdef HasCoreWindow
		namespace Core
		{
			struct CoreWindowDialog : internal::IInitializeWithWindowConstructorHelperWithArg<winrt::Windows::UI::Core::CoreWindowDialog>
			{
				CoreWindowDialog(HWND hwnd) : IInitializeWithWindowConstructorHelperWithArg{ hwnd }
				{
				}

				CoreWindowDialog(HWND hwnd, winrt::hstring const& title) : IInitializeWithWindowConstructorHelperWithArg{ hwnd, title }
				{
				}
			};

			struct CoreWindowFlyout : internal::IInitializeWithWindowConstructorHelperWithArg<winrt::Windows::UI::Core::CoreWindowFlyout>
			{
				CoreWindowFlyout(HWND hwnd, winrt::Windows::Foundation::Point position) : IInitializeWithWindowConstructorHelperWithArg{ hwnd, position }
				{
				}

				CoreWindowFlyout(HWND hwnd, winrt::Windows::Foundation::Point position, winrt::hstring const& title) :
					IInitializeWithWindowConstructorHelperWithArg{ hwnd, position, title }
				{
				}
			};
		}
#endif

		namespace Popups
		{
			struct MessageDialog : internal::IInitializeWithWindowConstructorHelperWithArg<winrt::Windows::UI::Popups::MessageDialog>
			{
				MessageDialog(HWND hwnd, winrt::hstring const& content) : IInitializeWithWindowConstructorHelperWithArg{ hwnd, content }
				{
				}

				MessageDialog(HWND hwnd, winrt::hstring const& content, winrt::hstring const& title) :
					IInitializeWithWindowConstructorHelperWithArg{ hwnd, content, title }
				{
				}
			};

			using PopupMenu = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::UI::Popups::PopupMenu>;
		}

		namespace StartScreen
		{
			struct SecondaryTile : internal::IInitializeWithWindowConstructorHelperWithArg<winrt::Windows::UI::StartScreen::SecondaryTile>
			{
				SecondaryTile(HWND hwnd) : IInitializeWithWindowConstructorHelperWithArg{ hwnd }
				{
				}

				SecondaryTile(HWND hwnd, winrt::hstring const& tileId) : IInitializeWithWindowConstructorHelperWithArg{ hwnd, tileId }
				{
				}

				SecondaryTile(
					HWND hwnd,
					winrt::hstring const& tileId,
					winrt::hstring const& displayName,
					winrt::hstring const& arguments,
					winrt::Windows::Foundation::Uri const& square150x150Logo,
					winrt::Windows::UI::StartScreen::TileSize desiredSize) :
					IInitializeWithWindowConstructorHelperWithArg{hwnd, tileId, displayName, arguments, square150x150Logo, desiredSize}
				{
				}

				SecondaryTile(
					HWND hwnd,
					winrt::hstring const& tileId,
					winrt::hstring const& shortName,
					winrt::hstring const& displayName,
					winrt::hstring const& arguments,
					winrt::Windows::UI::StartScreen::TileOptions tileOptions,
					winrt::Windows::Foundation::Uri const& logoReference
				) : IInitializeWithWindowConstructorHelperWithArg{ hwnd, tileId, shortName, displayName, arguments, tileOptions, logoReference }
				{
				}

				SecondaryTile(
					HWND hwnd,
					winrt::hstring const& tileId,
					winrt::hstring const& shortName,
					winrt::hstring const& displayName,
					winrt::hstring const& arguments,
					winrt::Windows::UI::StartScreen::TileOptions tileOptions,
					winrt::Windows::Foundation::Uri const& logoReference,
					winrt::Windows::Foundation::Uri const& wideLogoReference
				) : IInitializeWithWindowConstructorHelperWithArg{ hwnd, tileId, shortName, displayName, arguments, tileOptions, logoReference, wideLogoReference }
				{
				}
			};
		}
	}
}