﻿#pragma once

#include "SettingsCard.g.h"
#include "include/TemplateControlHelper.hpp"

namespace winrt::UWPPackage::implementation
{
    struct SettingsCard : SettingsCardT<SettingsCard>
    {
        SettingsCard() = default;

#pragma region Overrides
        void OnApplyTemplate();

#pragma endregion

#pragma region Properties
        winrt::Windows::Foundation::IInspectable Header();
        void Header(winrt::Windows::Foundation::IInspectable value);
        static winrt::Windows::UI::Xaml::DependencyProperty HeaderProperty();

        winrt::Windows::Foundation::IInspectable Description();
        void Description(winrt::Windows::Foundation::IInspectable value);
        static winrt::Windows::UI::Xaml::DependencyProperty DescriptionProperty();

        winrt::Windows::Foundation::IInspectable HeaderIcon();
        void HeaderIcon(winrt::Windows::Foundation::IInspectable value);
        static winrt::Windows::UI::Xaml::DependencyProperty HeaderIconProperty();

        winrt::Windows::Foundation::IInspectable ActionIcon();
        void ActionIcon(winrt::Windows::Foundation::IInspectable value);
        static winrt::Windows::UI::Xaml::DependencyProperty ActionIconProperty();

        winrt::hstring ActionIconToolTip();
        void ActionIconToolTip(winrt::hstring value);
        static winrt::Windows::UI::Xaml::DependencyProperty ActionIconToolTipProperty();

        bool IsClickEnabled();
        void IsClickEnabled(bool value);
        static winrt::Windows::UI::Xaml::DependencyProperty IsClickEnabledProperty();

        bool IsActionIconVisible();
        void IsActionIconVisible(bool value);
        static winrt::Windows::UI::Xaml::DependencyProperty IsActionIconVisibleProperty();

        UWPPackage::ContentAlignment ContentAlignment();
        void ContentAlignment(UWPPackage::ContentAlignment value);
        static winrt::Windows::UI::Xaml::DependencyProperty ContentAlignmentProperty();
#pragma endregion

        void OnPointerPressed(winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void OnPointerReleased(winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
    private:
        static winrt::Windows::UI::Xaml::DependencyProperty m_headerProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_descriptionProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_headerIconProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_actionIconProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_actionIconToolTipProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_isClickEnabledProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_isActionIconVisibleProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_contentAlignmentProperty;

        void onIsClickEnabledChanged();
        void onActionIconChanged();
        void onHeaderChanged();
        void onHeaderIconChanged();
        void onDescriptionChanged();
        void onIsEnabledChanged(
            winrt::Windows::Foundation::IInspectable sender,
            winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e);

        void enableButtonInteraction();
        void disableButtonInteraction();

        winrt::event_token m_pointerEntered;
        winrt::event_token m_pointerExited;
        winrt::event_token m_pointerCaptureLost;
        winrt::event_token m_pointerCanceled;
        winrt::event_token m_previewKeyDown;
        winrt::event_token m_previewKeyUp;

        bool m_isPointerOver{};

        void pointerEntered(
            winrt::Windows::Foundation::IInspectable sender,
            winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void pointerExited(
            winrt::Windows::Foundation::IInspectable sender,
            winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void pointerCaptureLost(
            winrt::Windows::Foundation::IInspectable sender,
            winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void pointerCanceled(
            winrt::Windows::Foundation::IInspectable sender,
            winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void previewKeyUp(
            winrt::Windows::Foundation::IInspectable sender,
            winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);
        void previewKeyDown(
            winrt::Windows::Foundation::IInspectable sender,
            winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);


        constexpr static auto NormalState = L"Normal";
        constexpr static auto PointerOverState = L"PointerOver";
        constexpr static auto PressedState = L"Pressed";
        constexpr static auto DisabledState = L"Disabled";

        constexpr static auto ActionIconPresenterHolder = L"PART_ActionIconPresenterHolder";
        constexpr static auto HeaderPresenter = L"PART_HeaderPresenter";
        constexpr static auto DescriptionPresenter = L"PART_DescriptionPresenter";
        constexpr static auto HeaderIconPresenterHolder = L"PART_HeaderIconPresenterHolder";

        constexpr static std::array PreviewKeys
        {
            winrt::Windows::System::VirtualKey::Enter,
            winrt::Windows::System::VirtualKey::Space,
            winrt::Windows::System::VirtualKey::GamepadA
        };

        static bool contains(auto&& range, auto&& value)
        {
            return std::ranges::find(range, value) != std::end(range);
        }

        winrt::Windows::UI::Xaml::FrameworkElement getFocusedElement();
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct SettingsCard : SettingsCardT<SettingsCard, implementation::SettingsCard>
    {
    };
}
