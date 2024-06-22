#pragma once

#include "SettingsExpander.g.h"
#include "include/TemplateControlHelper.hpp"

namespace winrt::UWPPackage::implementation
{
    struct SettingsExpander : SettingsExpanderT<SettingsExpander>, TemplateControlHelper<SettingsExpander>
    {
        SettingsExpander();

        void OnApplyTemplate();
#pragma region Properties
        winrt::Windows::Foundation::IInspectable Header();
        void Header(winrt::Windows::Foundation::IInspectable header);
        static winrt::Windows::UI::Xaml::DependencyProperty HeaderProperty();

        winrt::Windows::Foundation::IInspectable Content();
        void Content(winrt::Windows::Foundation::IInspectable value);
        static winrt::Windows::UI::Xaml::DependencyProperty ContentProperty();

        winrt::Windows::Foundation::IInspectable Description();
        void Description(winrt::Windows::Foundation::IInspectable title);
        static winrt::Windows::UI::Xaml::DependencyProperty DescriptionProperty();

        winrt::Windows::Foundation::IInspectable HeaderIcon();
        void HeaderIcon(winrt::Windows::Foundation::IInspectable symbol);
        static winrt::Windows::UI::Xaml::DependencyProperty HeaderIconProperty();

        winrt::Windows::UI::Xaml::UIElement ItemsHeader();
        void ItemsHeader(winrt::Windows::UI::Xaml::UIElement expanderContent);
        static winrt::Windows::UI::Xaml::DependencyProperty ItemsHeaderProperty();

        winrt::Windows::UI::Xaml::UIElement ItemsFooter();
        void ItemsFooter(winrt::Windows::UI::Xaml::UIElement expanderContent);
        static winrt::Windows::UI::Xaml::DependencyProperty ItemsFooterProperty();

        bool IsExpanded();
        void IsExpanded(bool value);
        static winrt::Windows::UI::Xaml::DependencyProperty IsExpandedProperty();
#pragma endregion

#pragma region Events
        winrt::event_token Expanded(UWPPackage::SignalDelegate const& handler);
        void Expanded(winrt::event_token const& token);

        winrt::event_token Collapsed(UWPPackage::SignalDelegate const& handler);
        void Collapsed(winrt::event_token const& token);
#pragma endregion

#pragma region ItemsControl
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Items();
        void Items(winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> value);
        static winrt::Windows::UI::Xaml::DependencyProperty ItemsProperty();

        winrt::Windows::Foundation::IInspectable ItemsSource();
        void ItemsSource(winrt::Windows::Foundation::IInspectable value);
        static winrt::Windows::UI::Xaml::DependencyProperty ItemsSourceProperty();

        winrt::Windows::Foundation::IInspectable ItemTemplate();
        void ItemTemplate(winrt::Windows::Foundation::IInspectable value);
        static winrt::Windows::UI::Xaml::DependencyProperty ItemTemplateProperty();

        winrt::Windows::UI::Xaml::Controls::StyleSelector ItemContainerStyleSelector();
        void ItemContainerStyleSelector(winrt::Windows::UI::Xaml::Controls::StyleSelector value);
        static winrt::Windows::UI::Xaml::DependencyProperty ItemContainerStyleSelectorProperty();


#pragma endregion

    private:
        static winrt::Windows::UI::Xaml::DependencyProperty m_headerProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_contentProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_descriptionProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_headerIconProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_itemsHeaderProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_itemsFooterProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_isExpandedProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_itemsProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_itemsSourceProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_itemTemplateProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_itemContainerStyleSelectorProperty;

        winrt::event<UWPPackage::SignalDelegate> m_expandedEvent;
        winrt::event<UWPPackage::SignalDelegate> m_collapsedEvent;
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
            winrt::Windows::UI::Xaml::DependencyObject d,
            winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        void elementPrepared(
            winrt::Microsoft::UI::Xaml::Controls::ItemsRepeater sender,
            winrt::Microsoft::UI::Xaml::Controls::ItemsRepeaterElementPreparedEventArgs const& args
        );

        winrt::Microsoft::UI::Xaml::Controls::ItemsRepeater m_itemsRepeater{ nullptr };
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct SettingsExpander : SettingsExpanderT<SettingsExpander, implementation::SettingsExpander>
    {
    };
}
