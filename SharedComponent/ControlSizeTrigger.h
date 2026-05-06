#pragma once

#include "ControlSizeTrigger.g.h"
#include "include/EnsureDependencyProperty.hpp"

namespace winrt::PackageRoot::implementation
{
    struct ControlSizeTrigger : ControlSizeTriggerT<ControlSizeTrigger>, EnsureDependencyProperty<ControlSizeTrigger>
    {
        static void EnsureDependencyProperties();
        ControlSizeTrigger() = default;

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
        void TargetElement(winrt::WinUINamespace::UI::Xaml::FrameworkElement value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty TargetElementProperty();
#pragma endregion

        bool IsActive();
    private:
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_canTriggerProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_maxWidthProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_minWidthProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_maxHeightProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_minHeightProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_targetElementProperty = nullptr;
        bool m_isActive{};
        void updateTrigger();
        winrt::event_token m_onTargetElementSizeChanged;
        static void valueChangeCallback(winrt::WinUINamespace::UI::Xaml::DependencyObject d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
        static void onTargetElementPropertyChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs e
        );
        void updateTargetElement(
            winrt::WinUINamespace::UI::Xaml::FrameworkElement oldValue,
            winrt::WinUINamespace::UI::Xaml::FrameworkElement newValue
        );
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct ControlSizeTrigger : ControlSizeTriggerT<ControlSizeTrigger, implementation::ControlSizeTrigger>
    {
    };
}
