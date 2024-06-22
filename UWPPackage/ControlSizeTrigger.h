#pragma once

#include "ControlSizeTrigger.g.h"

namespace winrt::UWPPackage::implementation
{
    struct ControlSizeTrigger : ControlSizeTriggerT<ControlSizeTrigger>
    {
        ControlSizeTrigger() = default;

#pragma region Properties
        bool CanTrigger();
        void CanTrigger(bool value);
        static winrt::Windows::UI::Xaml::DependencyProperty CanTriggerProperty();

        double MaxWidth();
        void MaxWidth(double value);
        static winrt::Windows::UI::Xaml::DependencyProperty MaxWidthProperty();

        double MinWidth();
        void MinWidth(double value);
        static winrt::Windows::UI::Xaml::DependencyProperty MinWidthProperty();

        double MaxHeight();
        void MaxHeight(double value);
        static winrt::Windows::UI::Xaml::DependencyProperty MaxHeightProperty();

        double MinHeight();
        void MinHeight(double value);
        static winrt::Windows::UI::Xaml::DependencyProperty MinHeightProperty();

        winrt::Windows::UI::Xaml::FrameworkElement TargetElement();
        void TargetElement(winrt::Windows::UI::Xaml::FrameworkElement value);
        static winrt::Windows::UI::Xaml::DependencyProperty TargetElementProperty();
#pragma endregion

        bool IsActive();
    private:
        static winrt::Windows::UI::Xaml::DependencyProperty m_canTriggerProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_maxWidthProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_minWidthProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_maxHeightProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_minHeightProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_targetElementProperty;
        bool m_isActive{};
        void updateTrigger();
        winrt::event_token m_onTargetElementSizeChanged;
        static void valueChangeCallback(winrt::Windows::UI::Xaml::DependencyObject d,
            winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
        static void onTargetElementPropertyChanged(
            winrt::Windows::UI::Xaml::DependencyObject d,
            winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs e
        );
        void updateTargetElement(
            winrt::Windows::UI::Xaml::FrameworkElement oldValue,
            winrt::Windows::UI::Xaml::FrameworkElement newValue
        );
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct ControlSizeTrigger : ControlSizeTriggerT<ControlSizeTrigger, implementation::ControlSizeTrigger>
    {
    };
}
