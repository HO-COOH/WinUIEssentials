#include "pch.h"
#include "TaskbarIconSource.xaml.h"
#if __has_include("TaskbarIconSource.g.cpp")
#include "TaskbarIconSource.g.cpp"
#endif
#include "MainWindow.xaml.h"
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Microsoft.UI.Xaml.Media.Imaging.h>
#include <IInitializeWithWindowHelper.hpp>
#include <ScopedButtonDisabler.hpp>

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	winrt::Windows::Foundation::IAsyncAction TaskbarIconSource::Button_Click(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		ScopedButtonDisabler buttonDisabler{ sender };
		WinUIEssentials::Windows::Storage::Pickers::FileOpenPicker picker{ winrt::WinUI3Example::implementation::MainWindow::Hwnd };
		
		picker.FileTypeFilter().Append(L"*");
		if (auto file = co_await picker.PickSingleFileAsync())
		{
			auto stream = co_await file.OpenReadAsync();
			winrt::Microsoft::UI::Xaml::Media::Imaging::BitmapImage image;
			image.SetSourceAsync(stream);
			PreviewImage().Source(image);
			IconFile = file.Path();
			raisePropertyChange(L"IsFileSet");
		}
	}

	bool TaskbarIconSource::IsFileSet()
	{
		return !IconFile.empty();
	}

}
