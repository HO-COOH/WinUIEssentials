#include "pch.h"
#include "LineGraphControl.xaml.h"
#if __has_include("LineGraphControl.g.cpp")
#include "LineGraphControl.g.cpp"
#endif
#include <winrt/Microsoft.UI.Input.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	void LineGraphControl::AddPoint(double x, double y)
	{
		auto points = Shape().Points();
		//auto const normalized_x = axis_x.AddPoint(x);
		//auto const normalized_y = axis_y.AddPoint(y);
		switch (++m_count)
		{
		case 1:

			points.Append(winrt::Windows::Foundation::Point(getX(0.0), 0));
			points.Append(winrt::Windows::Foundation::Point(getX(0.0), y));
			points.Append(winrt::Windows::Foundation::Point(getX(1.0), y));
			points.Append(winrt::Windows::Foundation::Point(getX(1.0), 0));

			m_points[0] = x;
			break;
		case 2:
		{
			auto point1 = points.GetAt(1);
			points.Clear();

			points.Append(winrt::Windows::Foundation::Point(getX(0.0), 0));
			points.Append(winrt::Windows::Foundation::Point(getX(0.0), point1.Y));
			points.Append(winrt::Windows::Foundation::Point(getX(x), y));
			points.Append(winrt::Windows::Foundation::Point(getX(x), 0));

			m_points[1] = x;
			break;
		}
 
		default:
			points.SetAt(points.Size() - 1, winrt::Windows::Foundation::Point(getX(x), y));
			points.Append(winrt::Windows::Foundation::Point(getX(x), 0));
			break;
		}
	}

	double LineGraphControl::getX(double x)
	{
		return ActualWidth() * x;
	}

}


void winrt::WinUI3Example::implementation::LineGraphControl::Shape_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
	auto point = e.GetCurrentPoint(*this);
	auto pos = point.Position();
	LineX().Translation({ 0, pos.Y, 0 });
	LineY().Translation({ pos.X, 0, 0 });
}


void winrt::WinUI3Example::implementation::LineGraphControl::Shape_PointerExited(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
	LineX().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
	LineY().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
	OutputDebugString(L"Exited\n");
}


void winrt::WinUI3Example::implementation::LineGraphControl::Shape_PointerEntered(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
	LineX().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
	LineY().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
	OutputDebugString(L"Entered\n");
}
