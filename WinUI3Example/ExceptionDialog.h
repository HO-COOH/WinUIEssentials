#pragma once
#include <winrt/base.h>
#include <winrt/Windows.UI.Popups.h>

class ExceptionDialog : public std::enable_shared_from_this<ExceptionDialog>
{
	winrt::Windows::UI::Popups::MessageDialog m_dialog;
public:
	ExceptionDialog(
		winrt::hstring const& title,
		winrt::hstring const& content
	);

	winrt::fire_and_forget Show();
};

