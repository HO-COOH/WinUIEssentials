#include "pch.h"
#include "HostBackdropVisual.h"
#if __has_include("HostBackdropVisual.g.cpp")
#include "HostBackdropVisual.g.cpp"
#endif
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include <DispatcherQueue.h>

namespace winrt::WinUI3Package::implementation
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

	winrt::Windows::System::DispatcherQueueController HostBackdropVisual::s_queue{ nullptr };

	HostBackdropVisual::HostBackdropVisual()
	{
		RegisterPropertyChangedCallback(
			winrt::Microsoft::UI::Xaml::Controls::Control::CornerRadiusProperty(),
			{ this, &HostBackdropVisual::cornerRadiusChanged }
		);
	}

	void HostBackdropVisual::OnApplyTemplate()
	{
		m_acrylicContainer = GetTemplateChild(AcrylicContainer).as<decltype(m_acrylicContainer)>();
		m_acrylicContainer.SizeChanged({ this, &HostBackdropVisual::sizeChanged });

	}

	void HostBackdropVisual::sizeChanged(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& args)
	{
		auto size = args.NewSize();
		if (m_clipGeometry)
		{
			//already created visual
			m_clipGeometry.Size(size);
			m_externalLink.PlacementVisual().Size(size);
			return;
		}

		//create visual
		if (!s_queue)
			s_queue = createSystemDispatcherQueueController();

		winrt::Windows::UI::Composition::Compositor compositor;
		auto spriteVisual = compositor.CreateSpriteVisual();
		spriteVisual.Brush(compositor.CreateHostBackdropBrush());
		spriteVisual.Size(size);
		spriteVisual.BorderMode(winrt::Windows::UI::Composition::CompositionBorderMode::Soft);

		m_clipGeometry = compositor.CreateRoundedRectangleGeometry();
		m_clipGeometry.Size(size);
		cornerRadiusChanged(nullptr, winrt::Microsoft::UI::Xaml::Controls::Control::CornerRadiusProperty());
		spriteVisual.Clip(compositor.CreateGeometricClip(m_clipGeometry));

		//create placement visual
		createPlacementVisual(spriteVisual);

		//auto placementVisual = m_externalLink.PlacementVisual();
		//placementVisual.Clip(compositor.CreateGeometricClip(m_clipGeometry));
		winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(
			m_acrylicContainer,
			m_externalLink.PlacementVisual()
		);
	}

	void HostBackdropVisual::cornerRadiusChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& self,
		winrt::Microsoft::UI::Xaml::DependencyProperty const& cornerRadiusProperty
	)
	{
		if (!m_clipGeometry)
			return;

		auto const radius = winrt::unbox_value<winrt::Microsoft::UI::Xaml::CornerRadius>(GetValue(cornerRadiusProperty));
		m_clipGeometry.CornerRadius({
			static_cast<float>(radius.TopLeft),
			static_cast<float>(radius.TopLeft)
		});
	}

	void HostBackdropVisual::createPlacementVisual(winrt::Windows::UI::Composition::Visual const& rootVisual)
	{
		auto compositor = winrt::Microsoft::UI::Xaml::Media::CompositionTarget::GetCompositorForCurrentThread();
		m_externalLink = winrt::Microsoft::UI::Content::ContentExternalOutputLink::Create(compositor);
		
		auto clipGeometryW = compositor.CreateRoundedRectangleGeometry();

		auto const radius = winrt::unbox_value<winrt::Microsoft::UI::Xaml::CornerRadius>(GetValue(winrt::Microsoft::UI::Xaml::Controls::Control::CornerRadiusProperty()));
		clipGeometryW.CornerRadius({
8.0f, 8.0f
			});
		clipGeometryW.Size(m_clipGeometry.Size());

		m_externalLink.as<winrt::Windows::UI::Composition::CompositionTarget>().Root(rootVisual);

		//m_externalLink.ExternalOutputBorderMode(winrt::Microsoft::UI::Composition::CompositionBorderMode::Soft);
		//m_externalLink.PlacementVisual().BorderMode(winrt::Microsoft::UI::Composition::CompositionBorderMode::Soft);
		//m_externalLink.PlacementVisual().Clip(compositor.CreateGeometricClip(clipGeometryW));
		m_externalLink.PlacementVisual().Size(rootVisual.Size());
	}


}
