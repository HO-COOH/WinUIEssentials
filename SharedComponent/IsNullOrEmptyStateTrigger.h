#pragma once

#include "IsNullOrEmptyStateTrigger.g.h"
#include "include/EnsureDependencyProperty.hpp"
#include <variant>

namespace winrt::PackageRoot::implementation
{
    struct IsNullOrEmptyStateTrigger : IsNullOrEmptyStateTriggerT<IsNullOrEmptyStateTrigger>, EnsureDependencyProperty<IsNullOrEmptyStateTrigger>
    {
        static void EnsureDependencyProperties();

        winrt::Windows::Foundation::IInspectable Value();
        void Value(winrt::Windows::Foundation::IInspectable value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ValueProperty();

    private:
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty m_valueProperty;
        static void onValuePropertyChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);

        void updateTrigger();
        static bool isNullOrEmpty(winrt::Windows::Foundation::IInspectable const& val);

        std::variant<
            winrt::WinUINamespace::UI::Xaml::Interop::INotifyCollectionChanged::CollectionChanged_revoker,
            winrt::WinUINamespace::UI::Xaml::Interop::IBindableObservableVector::VectorChanged_revoker,
            winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable>::VectorChanged_revoker,
            winrt::Windows::Foundation::Collections::IObservableMap<winrt::Windows::Foundation::IInspectable, winrt::Windows::Foundation::IInspectable>::MapChanged_revoker
        > m_revoker;
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct IsNullOrEmptyStateTrigger : IsNullOrEmptyStateTriggerT<IsNullOrEmptyStateTrigger, implementation::IsNullOrEmptyStateTrigger>
    {
    };
}
