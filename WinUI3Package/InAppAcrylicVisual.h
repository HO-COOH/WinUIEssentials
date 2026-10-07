#pragma once

#include "InAppAcrylicVisual.g.h"
#include "PlacementVisualBase.h"
#include <winrt/Microsoft.UI.Content.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Composition.h>

namespace winrt::WinUI3Package::implementation
{
    struct InAppAcrylicVisual : InAppAcrylicVisualT<InAppAcrylicVisual>, PlacementVisualBase<InAppAcrylicVisual>
    {
        InAppAcrylicVisual();
    private:
        winrt::Microsoft::UI::Content::ContentExternalBackdropLink m_backdropLink
        {
            winrt::Microsoft::UI::Content::ContentExternalBackdropLink::Create(winrt::Microsoft::UI::Xaml::Media::CompositionTarget::GetCompositorForCurrentThread())
        };
        void updateBrushColor();
        
        constexpr static winrt::Windows::UI::Color luminosityBrushColor(winrt::Microsoft::UI::Xaml::ElementTheme theme)
        {
            return theme == winrt::Microsoft::UI::Xaml::ElementTheme::Light ? 
             winrt::Windows::UI::Color{ 217, 0xfc, 0xfc, 0xfc } : 
             winrt::Windows::UI::Color{ 245, 0x2c, 0x2c, 0x2c };
        }

		constexpr static winrt::Windows::UI::Color tintBrushColor(winrt::Microsoft::UI::Xaml::ElementTheme theme)
		{
			return theme == winrt::Microsoft::UI::Xaml::ElementTheme::Light ?
				winrt::Windows::UI::Color{ 0, 0xfc, 0xfc, 0xfc } :
				winrt::Windows::UI::Color{ 38, 0x2c, 0x2c, 0x2c };
		}

        //adjust when theme changes
        winrt::Windows::UI::Composition::CompositionBrush createFinalBrush();
		winrt::Windows::UI::Composition::CompositionColorBrush m_tintBrush{ nullptr };
		winrt::Windows::UI::Composition::CompositionColorBrush m_luminosityBrush{ nullptr };
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct InAppAcrylicVisual : InAppAcrylicVisualT<InAppAcrylicVisual, implementation::InAppAcrylicVisual>
    {
    };
}
