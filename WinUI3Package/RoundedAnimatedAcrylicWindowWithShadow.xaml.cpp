#include "pch.h"
#include "RoundedAnimatedAcrylicWindowWithShadow.xaml.h"
#if __has_include("RoundedAnimatedAcrylicWindowWithShadow.g.cpp")
#include "RoundedAnimatedAcrylicWindowWithShadow.g.cpp"
#endif

#include <winrt/Microsoft.UI.Xaml.Hosting.h>

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Package::implementation
{
	RoundedAnimatedAcrylicWindowWithShadow::RoundedAnimatedAcrylicWindowWithShadow()
	{
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

	void RoundedAnimatedAcrylicWindowWithShadow::ShadowElement_SizeChanged(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e)
	{

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
	auto compositor = Compositor();
	m_shadowVisual = compositor.CreateSpriteVisual();

	auto dropShadow = compositor.CreateDropShadow();
	dropShadow.BlurRadius(10.f);

	m_shadowVisual.Size(root.ActualSize());
	m_shadowVisual.Shadow(dropShadow);
	m_shadowVisual.BorderMode(winrt::Microsoft::UI::Composition::CompositionBorderMode::Soft);
	m_shadowVisual.Brush(compositor.CreateColorBrush(winrt::Windows::UI::Colors::Transparent()));

	winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(root, m_shadowVisual);
}


void winrt::WinUI3Package::implementation::RoundedAnimatedAcrylicWindowWithShadow::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	OutputDebugString(L"me\n");
}
