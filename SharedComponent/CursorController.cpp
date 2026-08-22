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
#if defined(Build_UWPPackage)
	//UWP has no UIElement.ProtectedCursor, so the cursor has to be driven from pointer
	//events. Those are subscribed once per element and read the current Type when they
	//fire, so re-setting Type must not subscribe again - this flag records that it has
	//already happened. Deliberately not in the .idl, markup has no business touching it
	static winrt::WinUINamespace::UI::Xaml::DependencyProperty handlersRegisteredProperty()
	{
		static auto s_handlersRegisteredProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::RegisterAttached(
			L"HandlersRegistered",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<winrt::PackageRoot::CursorController>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ winrt::box_value(false) }
		);
		return s_handlersRegisteredProperty;
	}
#endif

	winrt::WinUINamespace::UI::Xaml::DependencyProperty CursorController::s_typeProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::RegisterAttached(
		L"Type",
		winrt::xaml_typename<winrt::Windows::UI::Core::CoreCursorType>(),
		winrt::xaml_typename<winrt::PackageRoot::CursorController>(),
		winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ winrt::box_value(winrt::Windows::UI::Core::CoreCursorType::Arrow), &CursorController::cursorChanged }
	);

	winrt::WinUINamespace::UI::Xaml::DependencyProperty CursorController::TypeProperty()
	{
		return s_typeProperty;
	}

	void CursorController::SetType(winrt::WinUINamespace::UI::Xaml::UIElement const& obj, winrt::Windows::UI::Core::CoreCursorType type)
	{
		obj.SetValue(TypeProperty(), winrt::box_value(type));
	}

	winrt::Windows::UI::Core::CoreCursorType CursorController::GetType(winrt::WinUINamespace::UI::Xaml::UIElement const& obj)
	{
		return winrt::unbox_value< winrt::Windows::UI::Core::CoreCursorType>(obj.GetValue(TypeProperty()));
	}

	void CursorController::cursorChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& obj, [[maybe_unused]] winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto element = obj.try_as<winrt::WinUINamespace::UI::Xaml::UIElement>();
		if (!element)
			return;

#if defined(Build_UWPPackage)
		if (winrt::unbox_value_or<bool>(element.GetValue(handlersRegisteredProperty()), false))
			return;
		element.SetValue(handlersRegisteredProperty(), winrt::box_value(true));

		element.PointerEntered([](winrt::Windows::Foundation::IInspectable const& sender, auto&&)
		{
			if (auto target = sender.try_as<winrt::WinUINamespace::UI::Xaml::UIElement>())
			{
				winrt::WinUINamespace::UI::Xaml::Window::Current().CoreWindow().PointerCursor(
					winrt::Windows::UI::Core::CoreCursor{ GetType(target), 1 }
				);
			}
		});
		element.PointerExited([](auto&&...)
		{
			winrt::WinUINamespace::UI::Xaml::Window::Current().CoreWindow().PointerCursor(
				winrt::Windows::UI::Core::CoreCursor{ winrt::Windows::UI::Core::CoreCursorType::Arrow, 1 }
			);
		});
#else
		auto value = winrt::unbox_value<winrt::Windows::UI::Core::CoreCursorType>(e.NewValue());
		winrt::Windows::UI::Core::CoreCursor cursor{ value, 1 };
		element.ProtectedCursor(winrt::WinUINamespace::UI::Input::InputCursor::CreateFromCoreCursor(cursor));
#endif
	}
}
