#include "pch.h"
#include "InitializeWithWindowHelperPage.xaml.h"
#if __has_include("InitializeWithWindowHelperPage.g.cpp")
#include "InitializeWithWindowHelperPage.g.cpp"
#endif

#include <IInitializeWithWindowHelper.hpp>
#include <winrt/Windows.ApplicationModel.Contacts.h>
#include <winrt/Windows.ApplicationModel.Payments.h>
#include "MainWindow.xaml.h"

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{

	winrt::Windows::Foundation::IAsyncAction InitializeWithWindowHelperPage::PinnedContactManagerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		winrt::Windows::ApplicationModel::Contacts::ContactPicker picker;
		//picker.as<::IInitializeWithWindow>()->Initialize(MainWindow::Hwnd);
		auto contact = co_await picker.PickContactAsync();
		
		auto manager = winrt::Windows::ApplicationModel::Contacts::PinnedContactManager::GetDefault();
		//manager.as<::IInitializeWithWindow>()->Initialize(MainWindow::Hwnd);
		//winrt::Windows::ApplicationModel::Contacts::Contact contact;
		auto result = co_await manager.RequestPinContactAsync(contact, winrt::Windows::ApplicationModel::Contacts::PinnedContactSurface::StartMenu);
	}


	void InitializeWithWindowHelperPage::PaymentMediatorButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		winrt::Windows::ApplicationModel::Payments::PaymentMediator mediator;
		//mediator.
	}


	void InitializeWithWindowHelperPage::DevicePickerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::Devices::Enumeration::DevicePicker picker{ MainWindow::Hwnd };
		picker.PickSingleDeviceAsync({});
	}


	void InitializeWithWindowHelperPage::GraphicsCapturePicker_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::Graphics::Capture::GraphicsCapturePicker picker{ MainWindow::Hwnd };
		picker.PickSingleItemAsync();
	}


	void InitializeWithWindowHelperPage::CastingDevicePickerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::Media::Casting::CastingDevicePicker picker{ MainWindow::Hwnd };
		picker.Show({});
	}


	void InitializeWithWindowHelperPage::DialDevicePickerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::Media::Casting::CastingDevicePicker picker{ MainWindow::Hwnd };
		picker.Show({});
	}


	void InitializeWithWindowHelperPage::ProvisioningAgentButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{

	}


	void InitializeWithWindowHelperPage::OnlineIdAuthenticatorButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{

	}


	void InitializeWithWindowHelperPage::StoreContextButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{

	}


	void InitializeWithWindowHelperPage::FileOpenPickerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::Storage::Pickers::FileOpenPicker{ MainWindow::Hwnd }.PickSingleFileAsync();
	}


	void InitializeWithWindowHelperPage::FileSavePicker_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::Storage::Pickers::FileSavePicker{ MainWindow::Hwnd }.PickSaveFileAsync();
	}


	void InitializeWithWindowHelperPage::FolderPickerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::Storage::Pickers::FolderPicker{ MainWindow::Hwnd }.PickSingleFolderAsync();
	}


	void InitializeWithWindowHelperPage::FolderLauncherOptionsButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{

	}


	void InitializeWithWindowHelperPage::LauncherOptionsButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{

	}


	void InitializeWithWindowHelperPage::CoreWindowDialogButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
#ifdef HasCoreWindow
		WinUIEssentials::Windows::UI::Core::CoreWindowDialog{ MainWindow::Hwnd, L"CoreMessageDialogTitle" }.ShowAsync();
#endif
	}


	void InitializeWithWindowHelperPage::CoreWindowFlyoutButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
#ifdef HasCoreWindow
		WinUIEssentials::Windows::UI::Core::CoreWindowFlyout{ MainWindow::Hwnd, {} }.ShowAsync();
#endif
	}


	void InitializeWithWindowHelperPage::MessageDialogButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::UI::Popups::MessageDialog{ MainWindow::Hwnd, L"MessageDialogContent", L"MessageDialogTitle" }.ShowAsync();
	}


	void InitializeWithWindowHelperPage::PopupMenuButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::UI::Popups::PopupMenu menu{ MainWindow::Hwnd };
		menu.Commands().ReplaceAll({ winrt::Windows::UI::Popups::UICommand{L"Command1"}, winrt::Windows::UI::Popups::UICommand{L"Command2"} });
		menu.ShowAsync({});
	}


	winrt::Windows::Foundation::IAsyncAction InitializeWithWindowHelperPage::SecondaryTileButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::UI::StartScreen::SecondaryTile tile
		{ 
			MainWindow::Hwnd, 
			L"Tile",
			L"Tile", 
			L"me", 
			winrt::Windows::Foundation::Uri{L"ms-appx:///Assets/LargeTile.scale-100.png"}, 
			winrt::Windows::UI::StartScreen::TileSize::Default
		};
		co_await tile.RequestCreateAsync();
	}

}

