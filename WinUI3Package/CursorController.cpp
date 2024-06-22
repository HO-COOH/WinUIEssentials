#include "pch.h"
#include "CursorController.h"
#if __has_include("CursorController.g.cpp")
#include "CursorController.g.cpp"
#endif
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Microsoft.UI.Input.h>
#include <winrt/Windows.UI.Core.h>

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty CursorController::s_typeProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
		L"Type",
		winrt::xaml_typename<winrt::Windows::UI::Core::CoreCursorType>(),
		winrt::xaml_typename<winrt::WinUI3Package::CursorController>(),
		winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(winrt::Windows::UI::Core::CoreCursorType::Arrow), &CursorController::CursorChanged }
	);
	winrt::Microsoft::UI::Xaml::DependencyProperty CursorController::TypeProperty()
	{
		return s_typeProperty;
	}
	void CursorController::SetType(winrt::Microsoft::UI::Xaml::UIElement obj, winrt::Windows::UI::Core::CoreCursorType type)
	{
		obj.SetValue(s_typeProperty, winrt::box_value(type));
	}
	winrt::Windows::UI::Core::CoreCursorType CursorController::GetType(winrt::Microsoft::UI::Xaml::UIElement obj)
	{
		return winrt::unbox_value< winrt::Windows::UI::Core::CoreCursorType>(obj.GetValue(s_typeProperty));
	}
	void CursorController::CursorChanged(winrt::Microsoft::UI::Xaml::DependencyObject obj, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e)
	{
		auto element = obj.try_as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
		if (!element)
			return;

		auto value = winrt::unbox_value<winrt::Windows::UI::Core::CoreCursorType>(e.NewValue());
		element.PointerEntered([value](auto sender, auto)
			{
					winrt::Windows::UI::Core::CoreCursor cursor{ value, 1 };
				sender.as<winrt::Microsoft::UI::Xaml::UIElement>().ProtectedCursor(winrt::Microsoft::UI::Input::InputCursor::CreateFromCoreCursor(cursor));
			}
		);
	}
}
