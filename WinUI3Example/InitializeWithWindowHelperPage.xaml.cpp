#include "pch.h"
#include "InitializeWithWindowHelperPage.xaml.h"
#if __has_include("InitializeWithWindowHelperPage.g.cpp")
#include "InitializeWithWindowHelperPage.g.cpp"
#endif

#include <IInitializeWithWindowHelper.hpp>
#include <winrt/Windows.ApplicationModel.Contacts.h>
#include <winrt/Windows.ApplicationModel.Payments.h>
#include "MainWindow.xaml.h"
#include "ExceptionDialog.h"

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{

	winrt::Windows::Foundation::IAsyncAction InitializeWithWindowHelperPage::PinnedContactManagerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		try
		{
			winrt::Windows::ApplicationModel::Contacts::ContactPicker picker;
			WinUIEssentials::InitializeWithWindow(picker, MainWindow::Hwnd).DesiredFieldsWithContactFieldType().Append(winrt::Windows::ApplicationModel::Contacts::ContactFieldType::Email);
			auto contact = co_await picker.PickContactAsync();

			auto manager = winrt::Windows::ApplicationModel::Contacts::PinnedContactManager::GetDefault();
			auto result = co_await manager.RequestPinContactAsync(contact, winrt::Windows::ApplicationModel::Contacts::PinnedContactSurface::StartMenu);
		}
		catch (winrt::hresult_error const& ex)
		{
			winrt::hstring message = L"Exception: " + ex.message() + L"\nError code: " + winrt::to_hstring(ex.code());
			std::make_shared<ExceptionDialog>(L"Exception", message)->Show();
		}
	}


	void InitializeWithWindowHelperPage::PaymentMediatorButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
	}


	void InitializeWithWindowHelperPage::DevicePickerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::Devices::Enumeration::DevicePicker{ MainWindow::Hwnd }.PickSingleDeviceAsync({});
	}


	void InitializeWithWindowHelperPage::GraphicsCapturePicker_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::Graphics::Capture::GraphicsCapturePicker{ MainWindow::Hwnd }.PickSingleItemAsync();
	}


	void InitializeWithWindowHelperPage::CastingDevicePickerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::Media::Casting::CastingDevicePicker{ MainWindow::Hwnd }.Show({});
	}


	void InitializeWithWindowHelperPage::DialDevicePickerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::Media::Casting::CastingDevicePicker{ MainWindow::Hwnd }.Show({});
	}


	void InitializeWithWindowHelperPage::ProvisioningAgentButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::Networking::NetworkOperators::ProvisioningAgent agent{ MainWindow::Hwnd };
		auto profile = agent.GetProvisionedProfile(winrt::Windows::Networking::NetworkOperators::ProfileMediaType::Wlan, L"Default");
	}


	void InitializeWithWindowHelperPage::OnlineIdAuthenticatorButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{

	}


	void InitializeWithWindowHelperPage::StoreContextButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{

	}


	void InitializeWithWindowHelperPage::FileOpenPickerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::Storage::Pickers::FileOpenPicker picker{ MainWindow::Hwnd };
		picker.FileTypeFilter().Append(L"*");
		picker.PickSingleFileAsync();
	}


	void InitializeWithWindowHelperPage::FileSavePicker_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::Storage::Pickers::FileSavePicker picker{ MainWindow::Hwnd };
		picker.FileTypeChoices().Insert(L"Anything", winrt::single_threaded_vector(std::vector<winrt::hstring>{ L".txt" }));
		picker.PickSaveFileAsync();
	}


	void InitializeWithWindowHelperPage::FolderPickerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::Storage::Pickers::FolderPicker{ MainWindow::Hwnd }.PickSingleFolderAsync();
	}


	void InitializeWithWindowHelperPage::FolderLauncherOptionsButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::System::FolderLauncherOptions options{ MainWindow::Hwnd };
		options.DesiredRemainingView(winrt::Windows::UI::ViewManagement::ViewSizePreference::UseMinimum);
		winrt::Windows::System::Launcher::LaunchFolderAsync(winrt::Windows::Storage::KnownFolders::DocumentsLibrary(), options);
	}


	void InitializeWithWindowHelperPage::LauncherOptionsButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{

	}


	void InitializeWithWindowHelperPage::CoreWindowDialogButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		//winrt::Windows::UI::Core::CoreWindowDialog dialog;
		WinUIEssentials::Windows::UI::Core::CoreWindowDialog{ MainWindow::Hwnd, L"CoreMessageDialogTitle" }.ShowAsync();
	}


	void InitializeWithWindowHelperPage::CoreWindowFlyoutButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		WinUIEssentials::Windows::UI::Core::CoreWindowFlyout flyout{ MainWindow::Hwnd, winrt::Windows::Foundation::Point{}, L"CoreWindowFlyout"};
		flyout.Commands().ReplaceAll({ winrt::Windows::UI::Popups::UICommand{L"Command1"}, winrt::Windows::UI::Popups::UICommand{L"Command2"} });
		flyout.ShowAsync();
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

