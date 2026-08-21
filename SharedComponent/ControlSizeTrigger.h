#pragma once

#include "ControlSizeTrigger.g.h"
#include "include/EnsureDependencyProperty.hpp"

namespace winrt::PackageRoot::implementation
{
    struct ControlSizeTrigger : ControlSizeTriggerT<ControlSizeTrigger>, EnsureDependencyProperty<ControlSizeTrigger>
    {
        static void EnsureDependencyProperties();

#pragma region Properties
        bool CanTrigger();
        void CanTrigger(bool value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty CanTriggerProperty();

        double MaxWidth();
        void MaxWidth(double value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty MaxWidthProperty();

        double MinWidth();
        void MinWidth(double value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty MinWidthProperty();

        double MaxHeight();
        void MaxHeight(double value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty MaxHeightProperty();

        double MinHeight();
        void MinHeight(double value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty MinHeightProperty();

        winrt::WinUINamespace::UI::Xaml::FrameworkElement TargetElement();
        void TargetElement(winrt::WinUINamespace::UI::Xaml::FrameworkElement const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty TargetElementProperty();
#pragma endregion

    private:
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty m_canTriggerProperty;
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty m_maxWidthProperty;
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty m_minWidthProperty;
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty m_maxHeightProperty;
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty m_minHeightProperty;
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty m_targetElementProperty;
        void updateTrigger();
        void updateTrigger(winrt::WinUINamespace::UI::Xaml::FrameworkElement const& target);
        winrt::WinUINamespace::UI::Xaml::FrameworkElement::SizeChanged_revoker m_onTargetElementSizeChanged;
        static void valueChangeCallback(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onTargetElementPropertyChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct ControlSizeTrigger : ControlSizeTriggerT<ControlSizeTrigger, implementation::ControlSizeTrigger>
    {
    };
}
