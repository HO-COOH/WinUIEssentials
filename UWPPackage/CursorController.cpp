#include "pch.h"
#include "CursorController.h"
#if __has_include("CursorController.g.cpp")
#include "CursorController.g.cpp"
#endif

namespace winrt::UWPPackage::implementation
{
	winrt::Windows::UI::Xaml::DependencyProperty CursorController::s_typeProperty = winrt::Windows::UI::Xaml::DependencyProperty::RegisterAttached(
		L"Type",
		winrt::xaml_typename<winrt::Windows::UI::Core::CoreCursorType>(),
		winrt::xaml_typename<winrt::UWPPackage::CursorController>(),
		winrt::Windows::UI::Xaml::PropertyMetadata{ winrt::box_value(winrt::Windows::UI::Core::CoreCursorType::Arrow), &CursorController::CursorChanged }
	);
	winrt::Windows::UI::Xaml::DependencyProperty CursorController::TypeProperty()
	{
		return s_typeProperty;
	}
	void CursorController::SetType(winrt::Windows::UI::Xaml::UIElement obj, winrt::Windows::UI::Core::CoreCursorType type)
	{
		obj.SetValue(s_typeProperty, winrt::box_value(type));
	}
	winrt::Windows::UI::Core::CoreCursorType CursorController::GetType(winrt::Windows::UI::Xaml::UIElement obj)
	{
		return winrt::unbox_value< winrt::Windows::UI::Core::CoreCursorType>(obj.GetValue(s_typeProperty));
	}
	void CursorController::CursorChanged(winrt::Windows::UI::Xaml::DependencyObject obj, winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs e)
	{
		auto element = obj.try_as<winrt::Windows::UI::Xaml::FrameworkElement>();
		if (!element)
			return;

		auto value = winrt::unbox_value<winrt::Windows::UI::Core::CoreCursorType>(e.NewValue());
		element.PointerEntered([value](auto, auto)
			{
				winrt::Windows::UI::Xaml::Window::Current().CoreWindow().PointerCursor(
					winrt::Windows::UI::Core::CoreCursor{ value, 1 }
				);
			}
		);
		element.PointerExited([](auto, auto)
			{
				winrt::Windows::UI::Xaml::Window::Current().CoreWindow().PointerCursor(
					winrt::Windows::UI::Core::CoreCursor{ winrt::Windows::UI::Core::CoreCursorType::Arrow, 1 }
				);
			}
		);
	}
}
