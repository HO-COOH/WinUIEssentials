#include "pch.h"
#include "IsNullOrEmptyStateTrigger.h"
#if __has_include("IsNullOrEmptyStateTrigger.g.cpp")
#include "IsNullOrEmptyStateTrigger.g.cpp"
#endif
#if defined Build_WinUIPackage
#include <winrt/Microsoft.UI.Xaml.Interop.h>
#else
#include <winrt/Windows.UI.Xaml.Interop.h>
#endif

namespace winrt::PackageRoot::implementation
{
	static bool isEmpty(winrt::hstring const& str)
	{
		return str.empty();
	}

	static bool isEmpty(winrt::WinUINamespace::UI::Xaml::Interop::IBindableVector const& container)
	{
		return container.Size() == 0;
	}

	static bool isEmpty(winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> const& container)
	{
		return container.Size() == 0;
	}

	static bool isEmpty(winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Foundation::IInspectable> const& container)
	{
		return container.Size() == 0;
	}

	static bool isEmpty(winrt::Windows::Foundation::Collections::IMap<winrt::Windows::Foundation::IInspectable, winrt::Windows::Foundation::IInspectable> const& container)
	{
		return container.Size() == 0;
	}

	static bool isEmpty(winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::Foundation::IInspectable> const& container)
	{
		return !container.First().HasCurrent();
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty IsNullOrEmptyStateTrigger::m_valueProperty = nullptr;

	void IsNullOrEmptyStateTrigger::EnsureDependencyProperties()
	{
		if (m_valueProperty) return;
		m_valueProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"Value",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<PackageRoot::IsNullOrEmptyStateTrigger>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{
				nullptr,
				&IsNullOrEmptyStateTrigger::onValuePropertyChanged
			}
		);
	}

	winrt::Windows::Foundation::IInspectable IsNullOrEmptyStateTrigger::Value()
	{
		return GetValue(m_valueProperty);
	}

	void IsNullOrEmptyStateTrigger::Value(winrt::Windows::Foundation::IInspectable value)
	{
		SetValue(m_valueProperty, value);
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty IsNullOrEmptyStateTrigger::ValueProperty()
	{
		return m_valueProperty;
	}

	void IsNullOrEmptyStateTrigger::onValuePropertyChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, 
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		GetSelf(d)->updateTrigger();
	}

	void IsNullOrEmptyStateTrigger::updateTrigger()
	{
		auto val = Value();
		SetActive(isNullOrEmpty(val));

		m_revoker = {};

		if (!val)
			return;

		auto onContainerChanged = [weakThis = get_weak()](auto&&, auto&&)
		{
			if (auto strongThis = weakThis.get())
				strongThis->SetActive(isNullOrEmpty(strongThis->Value()));
		};

		if (auto notifyCollection = val.try_as<winrt::WinUINamespace::UI::Xaml::Interop::INotifyCollectionChanged>())
			m_revoker = notifyCollection.CollectionChanged(winrt::auto_revoke, onContainerChanged);
		else if (auto bindableObservableVector = val.try_as<winrt::WinUINamespace::UI::Xaml::Interop::IBindableObservableVector>())
			m_revoker = bindableObservableVector.VectorChanged(winrt::auto_revoke, onContainerChanged);
		else if (auto observableVector = val.try_as<winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable>>())
			m_revoker = observableVector.VectorChanged(winrt::auto_revoke, onContainerChanged);
		else if (auto observableMap = val.try_as<winrt::Windows::Foundation::Collections::IObservableMap<winrt::Windows::Foundation::IInspectable, winrt::Windows::Foundation::IInspectable>>())
			m_revoker = observableMap.MapChanged(winrt::auto_revoke, onContainerChanged);
	}

	bool IsNullOrEmptyStateTrigger::isNullOrEmpty(winrt::Windows::Foundation::IInspectable const& val)
	{
		if (!val)
			return true;

		if (auto valString = val.try_as<winrt::hstring>())
			return isEmpty(*valString);

		if (auto bindableVector = val.try_as<winrt::WinUINamespace::UI::Xaml::Interop::IBindableVector>())
			return isEmpty(bindableVector);

		if (auto vector = val.try_as<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable>>())
			return isEmpty(vector);

		if (auto vectorView = val.try_as<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Foundation::IInspectable>>())
			return isEmpty(vectorView);

		if (auto map = val.try_as<winrt::Windows::Foundation::Collections::IMap<winrt::Windows::Foundation::IInspectable, winrt::Windows::Foundation::IInspectable>>())
			return isEmpty(map);

		if (auto iterable = val.try_as<winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::Foundation::IInspectable>>())
			return isEmpty(iterable);

		return false;
	}
}
