#include "pch.h"
#include "TaskbarIconPage.xaml.h"
#if __has_include("TaskbarIconPage.g.cpp")
#include "TaskbarIconPage.g.cpp"
#endif

#include "TaskbarIconSource.xaml.h"

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	TaskbarIconPage::TaskbarIconPage()
	{
		InitializeComponent();

		winrt::get_self<TaskbarIconSource>(NormalIconSource())->onIconSet = [this](winrt::Windows::Foundation::Uri icon)
		{
			TaskbarIcon().Icon(icon);
		};
	}
}
