#include "pch.h"
#include "AnimatedWindowSize.xaml.h"
#if __has_include("AnimatedWindowSize.g.cpp")
#include "AnimatedWindowSize.g.cpp"
#endif


namespace winrt::WinUI3Example::implementation
{
	void winrt::WinUI3Example::implementation::AnimatedWindowSize::Button_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		WindowAnimation().Begin();
	}

}
