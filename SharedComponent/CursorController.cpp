#include "pch.h"
#include "CursorController.h"
#if __has_include("CursorController.g.cpp")
#include "CursorController.g.cpp"
#endif
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Windows.UI.Core.h>
#if defined(Build_WinUIPackage)
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Microsoft.UI.Input.h>
#endif

namespace winrt::PackageRoot::implementation
{
	winrt::WinUINamespace::UI::Xaml::DependencyProperty CursorController::TypeProperty()
	{
		static auto s_typeProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::RegisterAttached(
			L"Type",
			winrt::xaml_typename<winrt::Windows::UI::Core::CoreCursorType>(),
			winrt::xaml_typename<winrt::PackageRoot::CursorController>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ winrt::box_value(winrt::Windows::UI::Core::CoreCursorType::Arrow), &CursorController::CursorChanged }
		);
		return s_typeProperty;
	}

	void CursorController::SetType(winrt::WinUINamespace::UI::Xaml::UIElement obj, winrt::Windows::UI::Core::CoreCursorType type)
	{
		obj.SetValue(TypeProperty(), winrt::box_value(type));
	}

	winrt::Windows::UI::Core::CoreCursorType CursorController::GetType(winrt::WinUINamespace::UI::Xaml::UIElement obj)
	{
		return winrt::unbox_value< winrt::Windows::UI::Core::CoreCursorType>(obj.GetValue(TypeProperty()));
	}

	void CursorController::CursorChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject obj, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs e)
	{
		auto value = winrt::unbox_value<winrt::Windows::UI::Core::CoreCursorType>(e.NewValue());
#if defined(Build_UWPPackage)
		auto element = obj.try_as<winrt::WinUINamespace::UI::Xaml::FrameworkElement>();
		if (!element)
			return;

		element.PointerEntered([value](auto, auto)
			{
				winrt::WinUINamespace::UI::Xaml::Window::Current().CoreWindow().PointerCursor(
					winrt::Windows::UI::Core::CoreCursor{ value, 1 }
				);
			}
		);
		element.PointerExited([](auto, auto)
			{
				winrt::WinUINamespace::UI::Xaml::Window::Current().CoreWindow().PointerCursor(
					winrt::Windows::UI::Core::CoreCursor{ winrt::Windows::UI::Core::CoreCursorType::Arrow, 1 }
				);
			}
		);
#else
		auto element = obj.try_as<winrt::WinUINamespace::UI::Xaml::UIElement>();
		if (!element)
			return;

		winrt::Windows::UI::Core::CoreCursor cursor{ value, 1 };
		element.ProtectedCursor(winrt::WinUINamespace::UI::Input::InputCursor::CreateFromCoreCursor(cursor));
#endif
	}
}
