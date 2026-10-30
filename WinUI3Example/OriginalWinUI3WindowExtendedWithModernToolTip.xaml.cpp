#include "pch.h"
#include "OriginalWinUI3WindowExtendedWithModernToolTip.xaml.h"
#if __has_include("OriginalWinUI3WindowExtendedWithModernToolTip.g.cpp")
#include "OriginalWinUI3WindowExtendedWithModernToolTip.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	OriginalWinUI3WindowExtendedWithModernToolTip::OriginalWinUI3WindowExtendedWithModernToolTip(bool animate)
	{
		ExtendsContentIntoTitleBar(true);
		InitializeComponent();
		ModernToolTip().Animate(animate);
	}
}
