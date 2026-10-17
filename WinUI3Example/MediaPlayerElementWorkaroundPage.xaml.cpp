#include "pch.h"
#include "MediaPlayerElementWorkaroundPage.xaml.h"
#if __has_include("MediaPlayerElementWorkaroundPage.g.cpp")
#include "MediaPlayerElementWorkaroundPage.g.cpp"
#endif
#include "PageTagRegister.h"

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	static PageTagRegister<MediaPlayerElementWorkaroundPage> s_tags{ L"mediaplayerelement", L"mediaplayer", L"mediatransportcontrols", L"acrylic", L"control", L"workarund" };
}
