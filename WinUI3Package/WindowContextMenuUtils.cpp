#include "pch.h"
#include "WindowContextMenuUtils.h"
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Content.h>
#include <windowsx.h>
#include <DpiUtils.hpp>

namespace WindowContextMenuUtils
{
    winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutShowOptions GetFlyoutShowOptions(
        HWND hwnd,
        LPARAM lparam, 
        winrt::Microsoft::UI::Content::ContentCoordinateConverter const& converter)
    {
        winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutShowOptions options;
        options.ShowMode(winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutShowMode::Standard);
        winrt::Windows::Graphics::PointInt32 screenPoint{ static_cast<int>(GET_X_LPARAM(lparam)),  static_cast<int>(GET_Y_LPARAM(lparam)) };
        auto localPoint = converter.ConvertScreenToLocal(screenPoint);
        auto const dpi = GetDpiForWindow(hwnd);
        options.Position(winrt::Windows::Foundation::Point{
            DpiUtils::UnscaleForDpi<float>(localPoint.X, dpi),
            DpiUtils::UnscaleForDpi<float>(localPoint.Y, dpi)
        });
        return options;
    }
}
