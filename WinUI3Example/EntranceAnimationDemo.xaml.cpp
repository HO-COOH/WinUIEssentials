#include "pch.h"
#include "EntranceAnimationDemo.xaml.h"
#if __has_include("EntranceAnimationDemo.g.cpp")
#include "EntranceAnimationDemo.g.cpp"
#endif



// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{

	winrt::Windows::System::DispatcherQueueController createSystemDispatcherQueueController()
	{
		DispatcherQueueOptions options
		{
			sizeof(DispatcherQueueOptions),
			DQTYPE_THREAD_CURRENT,
			DQTAT_COM_STA
		};

		::ABI::Windows::System::IDispatcherQueueController* ptr{ nullptr };
		winrt::check_hresult(CreateDispatcherQueueController(options, &ptr));
		return { ptr, take_ownership_from_abi };
	}

	winrt::Windows::System::DispatcherQueueController EntranceAnimationDemo::s_queue{ nullptr };

	EntranceAnimationDemo::EntranceAnimationDemo()
	{
		InitializeComponent();

		constexpr static auto Width = 500;
		constexpr static auto Height = 200;
		AppWindow().MoveAndResize({
			.X = 500,
			.Y = 500,
			.Width = Width,
			.Height = Height
		});

		TranslateAnimation().From(-Width);
	}

	void EntranceAnimationDemo::RootGrid_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		if constexpr (std::string_view{ WINDOWSAPPSDK_RELEASE_CHANNEL } == "experimental")
		{
			CreateVisual(sender.as<winrt::Microsoft::UI::Xaml::Controls::Grid>());
		}
		else
		{
			ContentButton().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
			APINotAvailableText().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		}
	}
}

