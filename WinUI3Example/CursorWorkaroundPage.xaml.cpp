#include "pch.h"
#include "CursorWorkaroundPage.xaml.h"
#if __has_include("CursorWorkaroundPage.g.cpp")
#include "CursorWorkaroundPage.g.cpp"
#endif

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	static bool s_workaroundApplied = false;

	void CursorWorkaroundPage::ToggleButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		winrt::WinUI3Package::CursorController::ApplyCursorWorkaround();
		s_workaroundApplied = true;
		raisePropertyChange(L"WorkaroundApplied");
	}

	bool CursorWorkaroundPage::WorkaroundApplied()
	{
		return s_workaroundApplied;
	}

	winrt::hstring CursorWorkaroundPage::GetButtonText(bool applied)
	{
		return applied ? L"Workaround Applied" : L"Apply Workaround";
	}
}
