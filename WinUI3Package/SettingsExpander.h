#pragma once

#include "SettingsExpander.g.h"
#include "include/TemplateControlHelper.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct SettingsExpander : SettingsExpanderT<SettingsExpander>, TemplateControlHelper<SettingsExpander>
    {
        SettingsExpander();

        void OnApplyTemplate();
#pragma region Properties
        winrt::Windows::Foundation::IInspectable Header();
        void Header(winrt::Windows::Foundation::IInspectable header);
        static winrt::Microsoft::UI::Xaml::DependencyProperty HeaderProperty();

        winrt::Windows::Foundation::IInspectable Content();
        void Content(winrt::Windows::Foundation::IInspectable value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ContentProperty();

        winrt::Windows::Foundation::IInspectable Description();
        void Description(winrt::Windows::Foundation::IInspectable title);
        static winrt::Microsoft::UI::Xaml::DependencyProperty DescriptionProperty();

        winrt::Windows::Foundation::IInspectable HeaderIcon();
        void HeaderIcon(winrt::Windows::Foundation::IInspectable symbol);
        static winrt::Microsoft::UI::Xaml::DependencyProperty HeaderIconProperty();

        winrt::Microsoft::UI::Xaml::UIElement ItemsHeader();
        void ItemsHeader(winrt::Microsoft::UI::Xaml::UIElement expanderContent);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ItemsHeaderProperty();

        winrt::Microsoft::UI::Xaml::UIElement ItemsFooter();
        void ItemsFooter(winrt::Microsoft::UI::Xaml::UIElement expanderContent);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ItemsFooterProperty();

        bool IsExpanded();
        void IsExpanded(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty IsExpandedProperty();
#pragma endregion

#pragma region Events
        winrt::event_token Expanded(WinUI3Package::SignalDelegate const& handler);
        void Expanded(winrt::event_token const& token);

        winrt::event_token Collapsed(WinUI3Package::SignalDelegate const& handler);
        void Collapsed(winrt::event_token const& token);
#pragma endregion

#pragma region ItemsControl
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Items();
        void Items(winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ItemsProperty();

        winrt::Windows::Foundation::IInspectable ItemsSource();
        void ItemsSource(winrt::Windows::Foundation::IInspectable value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ItemsSourceProperty();

        winrt::Windows::Foundation::IInspectable ItemTemplate();
        void ItemTemplate(winrt::Windows::Foundation::IInspectable value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ItemTemplateProperty();

        winrt::Microsoft::UI::Xaml::Controls::StyleSelector ItemContainerStyleSelector();
        void ItemContainerStyleSelector(winrt::Microsoft::UI::Xaml::Controls::StyleSelector value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ItemContainerStyleSelectorProperty();


#pragma endregion

    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_headerProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_contentProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_descriptionProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_headerIconProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_itemsHeaderProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_itemsFooterProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_isExpandedProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_itemsProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_itemsSourceProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_itemTemplateProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_itemContainerStyleSelectorProperty;

        winrt::event<WinUI3Package::SignalDelegate> m_expandedEvent;
        winrt::event<WinUI3Package::SignalDelegate> m_collapsedEvent;
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
            winrt::Microsoft::UI::Xaml::DependencyObject d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        void elementPrepared(
            winrt::Microsoft::UI::Xaml::Controls::ItemsRepeater sender,
            winrt::Microsoft::UI::Xaml::Controls::ItemsRepeaterElementPreparedEventArgs const& args
        );

        winrt::Microsoft::UI::Xaml::Controls::ItemsRepeater m_itemsRepeater{ nullptr };
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct SettingsExpander : SettingsExpanderT<SettingsExpander, implementation::SettingsExpander>
    {
    };
}
