#pragma once

#include "SettingsCard.g.h"
#include "include/EnsureDependencyProperty.hpp"
#include "include/TemplateControlHelper.hpp"

namespace winrt::PackageRoot::implementation
{
    struct SettingsCard : SettingsCardT<SettingsCard>, TemplateControlHelper<SettingsCard>, EnsureDependencyProperty<SettingsCard>
    {
        static void EnsureDependencyProperties();
        SettingsCard() = default;

#pragma region Overrides
        void OnApplyTemplate();

#pragma endregion

#pragma region Properties
        winrt::Windows::Foundation::IInspectable Header();
        void Header(winrt::Windows::Foundation::IInspectable value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty HeaderProperty();

        winrt::Windows::Foundation::IInspectable Description();
        void Description(winrt::Windows::Foundation::IInspectable value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty DescriptionProperty();

        winrt::Windows::Foundation::IInspectable HeaderIcon();
        void HeaderIcon(winrt::Windows::Foundation::IInspectable value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty HeaderIconProperty();

        winrt::Windows::Foundation::IInspectable ActionIcon();
        void ActionIcon(winrt::Windows::Foundation::IInspectable value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ActionIconProperty();

        winrt::hstring ActionIconToolTip();
        void ActionIconToolTip(winrt::hstring value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ActionIconToolTipProperty();

        bool IsClickEnabled();
        void IsClickEnabled(bool value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty IsClickEnabledProperty();

        bool IsActionIconVisible();
        void IsActionIconVisible(bool value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty IsActionIconVisibleProperty();

        PackageRoot::ContentAlignment ContentAlignment();
        void ContentAlignment(PackageRoot::ContentAlignment value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ContentAlignmentProperty();
#pragma endregion

        void OnPointerPressed(winrt::WinUINamespace::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void OnPointerReleased(winrt::WinUINamespace::UI::Xaml::Input::PointerRoutedEventArgs const& e);
		void OnContentChanged(winrt::Windows::Foundation::IInspectable const& oldContent, winrt::Windows::Foundation::IInspectable const& newContent);

#if defined Build_WinUIPackage
        constexpr static auto ResourceUri = L"ms-appx:///WinUI3Package/SettingsCard_Resource.xaml";
#else
        constexpr static auto ResourceUri = L"ms-appx:///UWPPackage/SettingsCard_Resource.xaml";
#endif
    private:
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_headerProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_descriptionProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_headerIconProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_actionIconProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_actionIconToolTipProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_isClickEnabledProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_isActionIconVisibleProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_contentAlignmentProperty = nullptr;

        void onIsClickEnabledChanged();
        void onActionIconChanged();
        void onHeaderChanged();
        void onHeaderIconChanged();
        void onDescriptionChanged();
        void onIsEnabledChanged(
            winrt::Windows::Foundation::IInspectable sender,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);

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
            winrt::WinUINamespace::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void pointerExited(
            winrt::Windows::Foundation::IInspectable sender,
            winrt::WinUINamespace::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void pointerCaptureLost(
            winrt::Windows::Foundation::IInspectable sender,
            winrt::WinUINamespace::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void pointerCanceled(
            winrt::Windows::Foundation::IInspectable sender,
            winrt::WinUINamespace::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void previewKeyUp(
            winrt::Windows::Foundation::IInspectable sender,
            winrt::WinUINamespace::UI::Xaml::Input::KeyRoutedEventArgs const& e);
        void previewKeyDown(
            winrt::Windows::Foundation::IInspectable sender,
            winrt::WinUINamespace::UI::Xaml::Input::KeyRoutedEventArgs const& e);


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

        winrt::WinUINamespace::UI::Xaml::FrameworkElement getFocusedElement();
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct SettingsCard : SettingsCardT<SettingsCard, implementation::SettingsCard>
    {
    };
}
