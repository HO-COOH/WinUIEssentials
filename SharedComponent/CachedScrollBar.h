#pragma once
#include <limits>
#if defined Build_WinUIPackage
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#define WinUINamespace Microsoft
#else
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#define WinUINamespace Windows
#endif

class CachedScrollBar
{
    winrt::WinUINamespace::UI::Xaml::Controls::Primitives::ScrollBar m_scrollBar{ nullptr };

    winrt::WinUINamespace::UI::Xaml::Visibility m_visibility{ winrt::WinUINamespace::UI::Xaml::Visibility::Visible };
    double m_maximum = std::numeric_limits<double>::quiet_NaN();
    double m_viewportSize = std::numeric_limits<double>::quiet_NaN();
    double m_largeChange = std::numeric_limits<double>::quiet_NaN();
    double m_smallChange = std::numeric_limits<double>::quiet_NaN();
    double m_value = std::numeric_limits<double>::quiet_NaN();
public:
    void Set(winrt::WinUINamespace::UI::Xaml::Controls::Primitives::ScrollBar const& scrollBar);

    void Visibility(winrt::WinUINamespace::UI::Xaml::Visibility visibility);
	void Maximum(double maximum);
	void ViewportSize(double viewportSize);
	void LargeChange(double largeChange);
	void SmallChange(double smallChange);
	bool Value(double value); //return whether changed
};