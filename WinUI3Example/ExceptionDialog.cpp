#include "pch.h"
#include "ExceptionDialog.h"
#include <IInitializeWithWindowHelper.hpp>
#include "MainWindow.xaml.h"
#include <winrt/Windows.ApplicationModel.DataTransfer.h>

ExceptionDialog::ExceptionDialog(winrt::hstring const& title, winrt::hstring const& content) : m_dialog{title, content}
{
	WinUIEssentials::InitializeWithWindow(m_dialog, winrt::WinUI3Example::implementation::MainWindow::Hwnd);

	
}

winrt::fire_and_forget ExceptionDialog::Show()
{
	winrt::Windows::UI::Popups::UICommand commands[]
	{
		winrt::Windows::UI::Popups::UICommand
		{
			L"Copy exceptions",
			[this](auto&&)
			{
				winrt::Windows::ApplicationModel::DataTransfer::DataPackage dataPackage;
				dataPackage.SetText(m_dialog.Content());
				winrt::Windows::ApplicationModel::DataTransfer::Clipboard::SetContent(dataPackage);
			}
		},
		winrt::Windows::UI::Popups::UICommand
		{
			L"Cancel"
		}
	};
	m_dialog.Commands().ReplaceAll(commands);
	auto sharedThis = shared_from_this();
	co_await m_dialog.ShowAsync();
}
