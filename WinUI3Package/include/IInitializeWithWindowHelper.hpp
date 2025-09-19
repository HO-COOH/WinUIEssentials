#pragma once

#include <ShObjIdl.h>
#if __has_include("HwndHelper.hpp")
#include "HwndHelper.hpp"
#else
#include <include/HwndHelper.hpp>
#endif

namespace WinUIEssentials
{
	[[maybe_unused]] auto& InitializeWithWindow(auto&& obj, HWND hwnd)
	{
		obj.as<IInitializeWithWindow>()->Initialize(hwnd);
		return obj;
	}

	[[maybe_unused]] auto& InitializeWithWindow(auto&& obj, winrt::Microsoft::UI::Xaml::Window window)
	{
		return InitializeWithWindow(obj, GetHwnd(window));
	}

	namespace internal
	{
		template<typename T>
		struct IInitializeWithWindowConstructorHelper : T
		{
			IInitializeWithWindowConstructorHelper(HWND hwnd)
			{
				T::template as<IInitializeWithWindow>()->Initialize(hwnd);
			}

			IInitializeWithWindowConstructorHelper(winrt::Microsoft::UI::Xaml::Window window) :
				IInitializeWithWindowConstructorHelper{ GetHwnd(window) }
			{

			}
		};

		template<typename T>
		struct IInitializeWithWindowConstructorHelperWithArg : T
		{
			template<typename... Args>
			IInitializeWithWindowConstructorHelperWithArg(HWND hwnd, Args&&... args) : T{ std::forward<Args>(args)... }
			{
				T::template as<IInitializeWithWindow>()->Initialize(hwnd);
			}

			template<typename... Args>
			IInitializeWithWindowConstructorHelperWithArg(winrt::Microsoft::UI::Xaml::Window window, Args&&... args) :
				IInitializeWithWindowConstructorHelperWithArg{ GetHwnd(window), std::forward<Args>(args)... }
			{
			}
		};

		template<typename T>
		concept HasCoreWindowDialog = requires
		{
			{ T{} };
			{ T{}.BackButtonCommand() };
			{ T{}.CancelCommandIndex() };
			{ T{}.Commands() };
			{ T{}.IsInteractionDelayed() };
			{ T{}.DefaultCommandIndex() };
			{ T{}.MaxSize() };
			{ T{}.MinSize() };
			{ T{}.Title() };
			{ T{}.ShowAsync() };
		};

		template<typename T>
		concept HasCoreWindowFlyout = requires(T t)
		{
			{ t.BackButtonCommand() };
			{ t.Commands() };
			{ t.DefaultCommandIndex() };
			{ t.IsInteractionDelayed() };
			{ t.MaxSize() };
			{ t.MinSize() };
			{ t.Title() };
			{ t.ShowAsync() };
		};

		template<bool v, typename T>
		struct Conditional
		{
			template<typename... Args>
			Conditional(Args&&...)
			{
			}
		};

		template<typename T>
		struct Conditional<true, T> : internal::IInitializeWithWindowConstructorHelperWithArg<T>
		{
			template<typename... Args>
			Conditional(Args&&... args)
				: internal::IInitializeWithWindowConstructorHelperWithArg<T>{ std::forward<Args>(args)... }
			{
			}
		};
	}
}

#if __has_include("winrt/Windows.Devices.Enumeration.h")
#include <winrt/Windows.Devices.Enumeration.h>
namespace WinUIEssentials::Windows::Devices::Enumeration
{
	using DevicePicker = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::Devices::Enumeration::DevicePicker>;
}
#endif

#if __has_include("winrt/Windows.Graphics.Capture.h")
#include <winrt/Windows.Graphics.Capture.h>
namespace WinUIEssentials::Windows::Graphics::Capture
{
	using GraphicsCapturePicker = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::Graphics::Capture::GraphicsCapturePicker>;
}
#endif

#if __has_include("winrt/Windows.Media.Casting.h")
#include <winrt/Windows.Media.Casting.h>
namespace WinUIEssentials::Windows::Media::Casting
{
	using CastingDevicePicker = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::Media::Casting::CastingDevicePicker>;
}
#endif

#if __has_include("winrt/Windows.Media.DialProtocol.h")
#include <winrt/Windows.Media.DialProtocol.h>
namespace WinUIEssentials::Windows::Media::DialProtocol
{
	using DialDevicePicker = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::Media::DialProtocol::DialDevicePicker>;
}
#endif

#if __has_include("winrt/Windows.Networking.NetworkOperators.h")
#include <winrt/Windows.Networking.NetworkOperators.h>
namespace WinUIEssentials::Windows::Networking::NetworkOperators
{
	using ProvisioningAgent = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::Networking::NetworkOperators::ProvisioningAgent>;
}
#endif

#if __has_include("winrt/Windows.Security.Authentication.OnlineId.h")
#include <winrt/Windows.Security.Authentication.OnlineId.h>
namespace WinUIEssentials::Windows::Security::Authentication::OnlineId
{
	using OnlineIdAuthenticator = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::Security::Authentication::OnlineId::OnlineIdAuthenticator>;
}
#endif

#if __has_include("winrt/Windows.Storage.Pickers.h")
#include <winrt/Windows.Storage.Pickers.h>
namespace WinUIEssentials::Windows::Storage::Pickers
{
	using FileOpenPicker = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::Storage::Pickers::FileOpenPicker>;
	using FileSavePicker = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::Storage::Pickers::FileSavePicker>;
	using FolderPicker = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::Storage::Pickers::FolderPicker>;
}
#endif

#if __has_include("winrt/Windows.System.h")
#include <winrt/Windows.System.h>
namespace WinUIEssentials::Windows::System
{
	using FolderLauncherOptions = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::System::FolderLauncherOptions>;
	using LauncherOptions = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::System::LauncherOptions>;
}
#endif

#if __has_include("winrt/Windows.UI.Core.h")
namespace winrt::Windows::UI::Core
{
	struct CoreWindowDialog;
	struct CoreWindowFlyout;
}
#include <winrt/Windows.UI.Core.h>
namespace WinUIEssentials::Windows::UI::Core
{
	struct CoreWindowDialog : internal::Conditional<internal::HasCoreWindowDialog<winrt::Windows::UI::Core::CoreWindowDialog>, winrt::Windows::UI::Core::CoreWindowDialog>
	{
		CoreWindowDialog(HWND hwnd) : Conditional{ hwnd }
		{
		}

		CoreWindowDialog(winrt::Microsoft::UI::Xaml::Window window) : Conditional{ window }
		{
		}

		CoreWindowDialog(HWND hwnd, winrt::hstring const& title) : Conditional{ hwnd, title }
		{
		}

		CoreWindowDialog(winrt::Microsoft::UI::Xaml::Window window, winrt::hstring const& title) : Conditional{ window, title }
		{
		}
	};

	struct CoreWindowFlyout : internal::Conditional<internal::HasCoreWindowFlyout<winrt::Windows::UI::Core::CoreWindowFlyout>, winrt::Windows::UI::Core::CoreWindowFlyout>
	{
		CoreWindowFlyout(HWND hwnd, winrt::Windows::Foundation::Point position) : Conditional{ hwnd, position }
		{
		}

		CoreWindowFlyout(winrt::Microsoft::UI::Xaml::Window window, winrt::Windows::Foundation::Point position) : Conditional{ window, position }
		{
		}

		CoreWindowFlyout(HWND hwnd, winrt::Windows::Foundation::Point position, winrt::hstring const& title) : Conditional{ hwnd, position, title }
		{
		}

		CoreWindowFlyout(winrt::Microsoft::UI::Xaml::Window window, winrt::Windows::Foundation::Point position, winrt::hstring const& title) : Conditional{ window, position, title }
		{
		}
	};
}
#endif

#if __has_include("winrt/Windows.UI.Popups.h")
#include <winrt/Windows.UI.Popups.h>
namespace WinUIEssentials::Windows::UI::Popups
{
	struct MessageDialog : internal::IInitializeWithWindowConstructorHelperWithArg<winrt::Windows::UI::Popups::MessageDialog>
	{
		MessageDialog(HWND hwnd, winrt::hstring const& content) : IInitializeWithWindowConstructorHelperWithArg{ hwnd, content }
		{
		}

		MessageDialog(winrt::Microsoft::UI::Xaml::Window window, winrt::hstring const& content) : IInitializeWithWindowConstructorHelperWithArg{ window, content }
		{
		}

		MessageDialog(HWND hwnd, winrt::hstring const& content, winrt::hstring const& title) :
			IInitializeWithWindowConstructorHelperWithArg{ hwnd, content, title }
		{
		}

		MessageDialog(winrt::Microsoft::UI::Xaml::Window window, winrt::hstring const& content, winrt::hstring const& title) :
			IInitializeWithWindowConstructorHelperWithArg{ window, content, title }
		{
		}
	};

	using PopupMenu = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::UI::Popups::PopupMenu>;
}
#endif

#if __has_include("winrt/Windows.UI.StartScreen.h")
#include <winrt/Windows.UI.StartScreen.h>
namespace WinUIEssentials::Windows::UI::StartScreen
{
	struct SecondaryTile : internal::IInitializeWithWindowConstructorHelperWithArg<winrt::Windows::UI::StartScreen::SecondaryTile>
	{
		SecondaryTile(HWND hwnd) : IInitializeWithWindowConstructorHelperWithArg{ hwnd }
		{
		}

		SecondaryTile(winrt::Microsoft::UI::Xaml::Window window) : IInitializeWithWindowConstructorHelperWithArg{ window }
		{
		}

		SecondaryTile(HWND hwnd, winrt::hstring const& tileId) : IInitializeWithWindowConstructorHelperWithArg{ hwnd, tileId }
		{
		}

		SecondaryTile(winrt::Microsoft::UI::Xaml::Window window, winrt::hstring const& tileId) : IInitializeWithWindowConstructorHelperWithArg{ window, tileId }
		{
		}

		SecondaryTile(
			HWND hwnd,
			winrt::hstring const& tileId,
			winrt::hstring const& displayName,
			winrt::hstring const& arguments,
			winrt::Windows::Foundation::Uri const& square150x150Logo,
			winrt::Windows::UI::StartScreen::TileSize desiredSize) :
			IInitializeWithWindowConstructorHelperWithArg{ hwnd, tileId, displayName, arguments, square150x150Logo, desiredSize }
		{
		}

		SecondaryTile(
			winrt::Microsoft::UI::Xaml::Window window,
			winrt::hstring const& tileId,
			winrt::hstring const& displayName,
			winrt::hstring const& arguments,
			winrt::Windows::Foundation::Uri const& square150x150Logo,
			winrt::Windows::UI::StartScreen::TileSize desiredSize) :
			IInitializeWithWindowConstructorHelperWithArg{ window, tileId, displayName, arguments, square150x150Logo, desiredSize }
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
			winrt::Microsoft::UI::Xaml::Window window,
			winrt::hstring const& tileId,
			winrt::hstring const& shortName,
			winrt::hstring const& displayName,
			winrt::hstring const& arguments,
			winrt::Windows::UI::StartScreen::TileOptions tileOptions,
			winrt::Windows::Foundation::Uri const& logoReference
		) : IInitializeWithWindowConstructorHelperWithArg{ window, tileId, shortName, displayName, arguments, tileOptions, logoReference }
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

		SecondaryTile(
			winrt::Microsoft::UI::Xaml::Window window,
			winrt::hstring const& tileId,
			winrt::hstring const& shortName,
			winrt::hstring const& displayName,
			winrt::hstring const& arguments,
			winrt::Windows::UI::StartScreen::TileOptions tileOptions,
			winrt::Windows::Foundation::Uri const& logoReference,
			winrt::Windows::Foundation::Uri const& wideLogoReference
		) : IInitializeWithWindowConstructorHelperWithArg{ window, tileId, shortName, displayName, arguments, tileOptions, logoReference, wideLogoReference }
		{
		}
	};
}
#endif

#if __has_include("winrt/Windows.Web.Http.Filters.h")
#include <winrt/Windows.Web.Http.Filters.h>
namespace WinUIEssentials::Windows::Web::Http::Filters
{
	using HttpBaseProtocolFilter = internal::IInitializeWithWindowConstructorHelper<winrt::Windows::Web::Http::Filters::HttpBaseProtocolFilter>;
}
#endif
