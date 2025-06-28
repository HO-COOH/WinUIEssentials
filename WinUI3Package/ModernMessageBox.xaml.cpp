#include "pch.h"
#include "ModernMessageBox.xaml.h"
#if __has_include("ModernMessageBox.g.cpp")
#include "ModernMessageBox.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Package::implementation
{
    winrt::Windows::Foundation::IAsyncOperation<int32_t> ModernMessageBox::ShowAsync(
        winrt::Microsoft::UI::Xaml::Window const& owner, 
        winrt::hstring const& text, 
        winrt::hstring const& caption, 
        uint16_t type)
    {
		winrt::WinUI3Package::ModernMessageBox dialog;
        dialog.Activate();
        co_await winrt::resume_on_signal(winrt::get_self<ModernMessageBox>(dialog)->h.get());
    }
}

void winrt::WinUI3Package::implementation::ModernMessageBox::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	winrt::check_bool(SetEvent(h.get()));
}
