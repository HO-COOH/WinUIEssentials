#include "pch.h"
#include "EntranceAnimationDemo.xaml.h"
#if __has_include("EntranceAnimationDemo.g.cpp")
#include "EntranceAnimationDemo.g.cpp"
#endif

#include <winrt/Microsoft.UI.Content.h>
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include <DispatcherQueue.h>

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{

	static winrt::Windows::System::DispatcherQueueController createSystemDispatcherQueueController()
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

		AppWindow().MoveAndResize({
			.X = 1000,
			.Y = 1000,
			.Width = Width,
			.Height = Height
		});

		TranslateAnimation().From(-Width);
	}

	void EntranceAnimationDemo::CreateVisual()
	{
		auto compositor = winrt::Microsoft::UI::Xaml::Media::CompositionTarget::GetCompositorForCurrentThread();
		externalOutputLink = winrt::Microsoft::UI::Content::ContentExternalOutputLink::Create(compositor);
		
		externalOutputLink.as<winrt::Windows::UI::Composition::CompositionTarget>().Root(createVisualW());
		auto placementVisual = externalOutputLink.PlacementVisual();
		placementVisual.Size({ static_cast<float>(Width), static_cast<float>(Height) });
		winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(AcrylicGrid(), placementVisual);
	}

	winrt::Windows::UI::Composition::SpriteVisual EntranceAnimationDemo::createVisualW()
	{
		if (!s_queue)
			s_queue = createSystemDispatcherQueueController();

		winrt::Windows::UI::Composition::Compositor compositor;
		auto spriteVisual = compositor.CreateSpriteVisual();
		spriteVisual.Brush(compositor.CreateHostBackdropBrush());
		spriteVisual.Size({ static_cast<float>(Width), static_cast<float>(Height) });
		spriteVisual.BorderMode(winrt::Windows::UI::Composition::CompositionBorderMode::Soft);

		auto clip = compositor.CreateRoundedRectangleGeometry();
		clip.CornerRadius({ Radius, Radius });
		clip.Size(spriteVisual.Size());

		spriteVisual.Clip(compositor.CreateGeometricClip(clip));

		return spriteVisual;
	}
}


void winrt::WinUI3Example::implementation::EntranceAnimationDemo::RootGrid_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	CreateVisual();
}
