#include "pch.h"
#include "OriginalWinUI3WindowWithModernToolTip.xaml.h"
#if __has_include("OriginalWinUI3WindowWithModernToolTip.g.cpp")
#include "OriginalWinUI3WindowWithModernToolTip.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	OriginalWinUI3WindowWithModernToolTip::OriginalWinUI3WindowWithModernToolTip(bool animate)
	{
		InitializeComponent();
		ModernToolTip().Animate(animate);
	}
}
