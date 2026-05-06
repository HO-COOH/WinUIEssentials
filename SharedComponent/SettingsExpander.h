#pragma once

#include "SettingsExpander.g.h"
#include "include/EnsureDependencyProperty.hpp"
#include "include/TemplateControlHelper.hpp"

namespace winrt::PackageRoot::implementation
{
    struct SettingsExpander : SettingsExpanderT<SettingsExpander>, TemplateControlHelper<SettingsExpander>, EnsureDependencyProperty<SettingsExpander>
    {
        static void EnsureDependencyProperties();
        SettingsExpander();

        void OnApplyTemplate();

#if defined Build_WinUIPackage
        constexpr static auto ResourceUri = L"ms-appx:///WinUI3Package/SettingsExpander_Resource.xaml";
#else
        constexpr static auto ResourceUri = L"ms-appx:///UWPPackage/SettingsExpander_Resource.xaml";
#endif
#pragma region Properties
        winrt::Windows::Foundation::IInspectable Header();
        void Header(winrt::Windows::Foundation::IInspectable header);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty HeaderProperty();

        winrt::Windows::Foundation::IInspectable Content();
        void Content(winrt::Windows::Foundation::IInspectable value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ContentProperty();

        winrt::Windows::Foundation::IInspectable Description();
        void Description(winrt::Windows::Foundation::IInspectable title);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty DescriptionProperty();

        winrt::Windows::Foundation::IInspectable HeaderIcon();
        void HeaderIcon(winrt::Windows::Foundation::IInspectable symbol);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty HeaderIconProperty();

        winrt::WinUINamespace::UI::Xaml::UIElement ItemsHeader();
        void ItemsHeader(winrt::WinUINamespace::UI::Xaml::UIElement expanderContent);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ItemsHeaderProperty();

        winrt::WinUINamespace::UI::Xaml::UIElement ItemsFooter();
        void ItemsFooter(winrt::WinUINamespace::UI::Xaml::UIElement expanderContent);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ItemsFooterProperty();

        bool IsExpanded();
        void IsExpanded(bool value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty IsExpandedProperty();
#pragma endregion

#pragma region Events
        winrt::event_token Expanded(PackageRoot::SignalDelegate const& handler);
        void Expanded(winrt::event_token const& token);

        winrt::event_token Collapsed(PackageRoot::SignalDelegate const& handler);
        void Collapsed(winrt::event_token const& token);
#pragma endregion

#pragma region ItemsControl
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Items();
        void Items(winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ItemsProperty();

        winrt::Windows::Foundation::IInspectable ItemsSource();
        void ItemsSource(winrt::Windows::Foundation::IInspectable value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ItemsSourceProperty();

        winrt::Windows::Foundation::IInspectable ItemTemplate();
        void ItemTemplate(winrt::Windows::Foundation::IInspectable value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ItemTemplateProperty();

        winrt::WinUINamespace::UI::Xaml::Controls::StyleSelector ItemContainerStyleSelector();
        void ItemContainerStyleSelector(winrt::WinUINamespace::UI::Xaml::Controls::StyleSelector value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ItemContainerStyleSelectorProperty();


#pragma endregion

    private:
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_headerProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_contentProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_descriptionProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_headerIconProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_itemsHeaderProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_itemsFooterProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_isExpandedProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_itemsProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_itemsSourceProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_itemTemplateProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_itemContainerStyleSelectorProperty = nullptr;

        winrt::event<PackageRoot::SignalDelegate> m_expandedEvent;
        winrt::event<PackageRoot::SignalDelegate> m_collapsedEvent;
        winrt::event_token m_elementPrepared;

        constexpr static auto PART_ItemsRepeater = L"PART_ItemsRepeater";
        void onIsExpandedPropertyChanged(bool oldValue, bool newValue)
        {
            if (newValue)
            {
                m_expandedEvent();
            }
            else
            {
                m_collapsedEvent();
            }
        }

        static void onItemsConnectedPropertyChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        void elementPrepared(
            winrt::Microsoft::UI::Xaml::Controls::ItemsRepeater sender,
            winrt::Microsoft::UI::Xaml::Controls::ItemsRepeaterElementPreparedEventArgs const& args
        );

        winrt::Microsoft::UI::Xaml::Controls::ItemsRepeater m_itemsRepeater{ nullptr };
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct SettingsExpander : SettingsExpanderT<SettingsExpander, implementation::SettingsExpander>
    {
    };
}
