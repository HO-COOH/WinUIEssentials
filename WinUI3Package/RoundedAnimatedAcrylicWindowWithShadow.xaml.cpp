#include "pch.h"
#include "RoundedAnimatedAcrylicWindowWithShadow.xaml.h"
#if __has_include("RoundedAnimatedAcrylicWindowWithShadow.g.cpp")
#include "RoundedAnimatedAcrylicWindowWithShadow.g.cpp"
#endif

#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include "TransparentWindow.h"
#include <winrt/Microsoft.UI.Windowing.h>

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Package::implementation
{
	RoundedAnimatedAcrylicWindowWithShadow::RoundedAnimatedAcrylicWindowWithShadow()
	{
		WinUI3Package::implementation::TransparentWindow::configureAppWindow(AppWindow());
		SystemBackdrop(WinUI3Package::TransparentBackdrop{});
	}

	winrt::Microsoft::UI::Xaml::CornerRadius RoundedAnimatedAcrylicWindowWithShadow::CornerRadius()
	{
		return m_cornerRadius;
	}
	void RoundedAnimatedAcrylicWindowWithShadow::CornerRadius(winrt::Microsoft::UI::Xaml::CornerRadius const& value)
	{
		m_cornerRadius = value;
	}
	winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard RoundedAnimatedAcrylicWindowWithShadow::EntranceStoryboard()
	{
		return m_entranceStoryboard;
	}
	void RoundedAnimatedAcrylicWindowWithShadow::EntranceStoryboard(winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard const& value)
	{
		m_entranceStoryboard = value;
	}
	winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard RoundedAnimatedAcrylicWindowWithShadow::ExitStoryboard()
	{
		return m_exitStoryboard;
	}
	void RoundedAnimatedAcrylicWindowWithShadow::ExitStoryboard(winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard const& value)
	{
		m_exitStoryboard = value;
	}

	winrt::Microsoft::UI::Xaml::UIElement RoundedAnimatedAcrylicWindowWithShadow::WindowContent()
	{
		return nullptr;
	}

	void RoundedAnimatedAcrylicWindowWithShadow::WindowContent(winrt::Microsoft::UI::Xaml::UIElement const& value)
	{
	}

	winrt::Windows::Foundation::TimeSpan RoundedAnimatedAcrylicWindowWithShadow::DurationToTimeSpan(winrt::Microsoft::UI::Xaml::Duration const& duration)
	{
		return duration.TimeSpan;
	}

}


void winrt::WinUI3Package::implementation::RoundedAnimatedAcrylicWindowWithShadow::ShadowElement_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	if (m_shadowVisual)
	{
		return;
	}


	//create shadow visual
	auto root = sender.as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
	auto compositor = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(root).Compositor();
	m_shadowVisual = compositor.CreateSpriteVisual();

	constexpr static auto Radius = 30.f;
	constexpr static auto OffsetMultiplier = 0.65;

	auto dropShadow = compositor.CreateDropShadow();
	dropShadow.BlurRadius(Radius);

	auto size = root.ActualSize();
	size.x -= 2*OffsetMultiplier*Radius;
	size.y -= 2*OffsetMultiplier*Radius;
	m_shadowVisual.Offset({ OffsetMultiplier *Radius, OffsetMultiplier *Radius, 0 });
	m_shadowVisual.Size(size);	m_shadowVisual.Shadow(dropShadow);
	m_shadowVisual.BorderMode(winrt::Microsoft::UI::Composition::CompositionBorderMode::Soft);
	m_shadowVisual.Brush(compositor.CreateColorBrush(winrt::Windows::UI::Colors::Transparent()));

	winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(root, m_shadowVisual);
}


void winrt::WinUI3Package::implementation::RoundedAnimatedAcrylicWindowWithShadow::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	OutputDebugString(L"me\n");
}


void winrt::WinUI3Package::implementation::RoundedAnimatedAcrylicWindowWithShadow::RootGrid_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e)
{
	TranslateAnimation().From(e.NewSize().Width);
}
