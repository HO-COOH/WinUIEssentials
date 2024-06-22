#include "pch.h"
#include "SettingsExpander.h"
#if __has_include("SettingsExpander.g.cpp")
#include "SettingsExpander.g.cpp"
#endif

namespace winrt::UWPPackage::implementation
{
    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::m_headerIconProperty =
        winrt::Windows::UI::Xaml::DependencyProperty::Register(
            L"HeaderIcon",
            winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
            winrt::xaml_typename<UWPPackage::SettingsExpander>(),
            Windows::UI::Xaml::PropertyMetadata::Create(winrt::Windows::Foundation::IInspectable{})
        );

    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::m_contentProperty =
        winrt::Windows::UI::Xaml::DependencyProperty::Register(
            L"Content",
            winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
            winrt::xaml_typename<UWPPackage::SettingsExpander>(),
            Windows::UI::Xaml::PropertyMetadata::Create(winrt::Windows::Foundation::IInspectable{})
        );

    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::m_descriptionProperty =
        winrt::Windows::UI::Xaml::DependencyProperty::Register(
            L"Description",
            winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
            winrt::xaml_typename<UWPPackage::SettingsExpander>(),
            { nullptr }
    );

    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::m_itemsFooterProperty =
        winrt::Windows::UI::Xaml::DependencyProperty::Register(
            L"ItemsFooter",
            winrt::xaml_typename<winrt::Windows::UI::Xaml::UIElement>(),
            winrt::xaml_typename<UWPPackage::SettingsExpander>(),
            { nullptr }
    );

    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::m_isExpandedProperty =
        winrt::Windows::UI::Xaml::DependencyProperty::Register(
            L"IsExpanded",
            winrt::xaml_typename<bool>(),
            winrt::xaml_typename<UWPPackage::SettingsExpander>(),
            Windows::UI::Xaml::PropertyMetadata{
                winrt::box_value(false),
                [](winrt::Windows::UI::Xaml::DependencyObject d, winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs e)
                {
                    winrt::get_self<SettingsExpander>(d.as<UWPPackage::SettingsExpander>())->onIsExpandedPropertyChanged(
                        winrt::unbox_value<bool>(e.OldValue()),
                        winrt::unbox_value<bool>(e.NewValue())
                    );
                }
            }
    );

    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::m_headerProperty =
        winrt::Windows::UI::Xaml::DependencyProperty::Register(
            L"Header",
            winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
            winrt::xaml_typename<UWPPackage::SettingsExpander>(),
            { nullptr }
    );

    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::m_itemsHeaderProperty =
        winrt::Windows::UI::Xaml::DependencyProperty::Register(
            L"ItemsHeader",
            winrt::xaml_typename<winrt::Windows::UI::Xaml::UIElement>(),
            winrt::xaml_typename<UWPPackage::SettingsExpander>(),
            { nullptr }
    );

    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::m_itemsProperty =
        winrt::Windows::UI::Xaml::DependencyProperty::Register(
            L"Items",
            winrt::xaml_typename<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable>>(),
            winrt::xaml_typename<UWPPackage::SettingsExpander>(),
            winrt::Windows::UI::Xaml::PropertyMetadata{
                nullptr,
                &SettingsExpander::onItemsConnectedPropertyChanged
            }
    );

    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::m_itemsSourceProperty =
        winrt::Windows::UI::Xaml::DependencyProperty::Register(
            L"ItemsSource",
            winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
            winrt::xaml_typename<UWPPackage::SettingsExpander>(),
            winrt::Windows::UI::Xaml::PropertyMetadata{
                nullptr,
                &SettingsExpander::onItemsConnectedPropertyChanged
            }
    );

    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::m_itemTemplateProperty =
        winrt::Windows::UI::Xaml::DependencyProperty::Register(
            L"ItemTemplate",
            winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
            winrt::xaml_typename<UWPPackage::SettingsExpander>(),
            winrt::Windows::UI::Xaml::PropertyMetadata{ nullptr }
    );

    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::m_itemContainerStyleSelectorProperty =
        winrt::Windows::UI::Xaml::DependencyProperty::Register(
            L"ItemContainerStyleSelector",
            winrt::xaml_typename<winrt::Windows::UI::Xaml::Controls::StyleSelector>(),
            winrt::xaml_typename<UWPPackage::SettingsExpander>(),
            winrt::Windows::UI::Xaml::PropertyMetadata{ nullptr }
    );


    //header
    winrt::Windows::Foundation::IInspectable SettingsExpander::Header()
    {
        return GetValue(m_headerProperty);
    }
    void SettingsExpander::Header(winrt::Windows::Foundation::IInspectable header)
    {
        SetValue(m_headerProperty, header);
    }
    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::HeaderProperty()
    {
        return m_headerProperty;
    }

    winrt::Windows::Foundation::IInspectable SettingsExpander::Content()
    {
        return GetValue(m_contentProperty);
    }

    void SettingsExpander::Content(winrt::Windows::Foundation::IInspectable value)
    {
        SetValue(m_contentProperty, value);
    }

    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::ContentProperty()
    {
        return m_contentProperty;
    }

    //description
    winrt::Windows::Foundation::IInspectable SettingsExpander::Description()
    {
        return winrt::unbox_value<winrt::Windows::Foundation::IInspectable>(GetValue(m_descriptionProperty));
    }
    void SettingsExpander::Description(winrt::Windows::Foundation::IInspectable title)
    {
        SetValue(m_descriptionProperty, winrt::box_value(title));
    }
    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::DescriptionProperty()
    {
        return m_descriptionProperty;
    }

    //header icon
    winrt::Windows::Foundation::IInspectable SettingsExpander::HeaderIcon()
    {
        return GetValue(m_headerIconProperty);
    }
    void SettingsExpander::HeaderIcon(winrt::Windows::Foundation::IInspectable symbol)
    {
        SetValue(m_headerIconProperty, symbol);
    }
    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::HeaderIconProperty()
    {
        return m_headerIconProperty;
    }

    //items header
    winrt::Windows::UI::Xaml::UIElement SettingsExpander::ItemsHeader()
    {
        return GetValue(m_itemsHeaderProperty).as<winrt::Windows::UI::Xaml::UIElement>();
    }
    void SettingsExpander::ItemsHeader(winrt::Windows::UI::Xaml::UIElement expanderContent)
    {
        SetValue(m_itemsHeaderProperty, expanderContent);
    }
    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::ItemsHeaderProperty()
    {
        return m_itemsHeaderProperty;
    }

    //items footer
    winrt::Windows::UI::Xaml::UIElement SettingsExpander::ItemsFooter()
    {
        return GetValue(m_itemsFooterProperty).as<winrt::Windows::UI::Xaml::UIElement>();
    }
    void SettingsExpander::ItemsFooter(winrt::Windows::UI::Xaml::UIElement expanderContent)
    {
        SetValue(m_itemsFooterProperty, expanderContent);
    }
    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::ItemsFooterProperty()
    {
        return m_itemsFooterProperty;
    }

    //is expanded
    bool SettingsExpander::IsExpanded()
    {
        return winrt::unbox_value<bool>(GetValue(m_isExpandedProperty));
    }
    void SettingsExpander::IsExpanded(bool value)
    {
        SetValue(m_isExpandedProperty, winrt::box_value(value));
    }
    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::IsExpandedProperty()
    {
        return m_isExpandedProperty;
    }

    //Expanded event
    winrt::event_token SettingsExpander::Expanded(UWPPackage::SignalDelegate const& handler)
    {
        return m_expandedEvent.add(handler);
    }
    void SettingsExpander::Expanded(winrt::event_token const& token)
    {
        m_expandedEvent.remove(token);
    }

    //Collapsed event
    winrt::event_token SettingsExpander::Collapsed(UWPPackage::SignalDelegate const& handler)
    {
        return m_collapsedEvent.add(handler);
    }
    void SettingsExpander::Collapsed(winrt::event_token const& token)
    {
        m_collapsedEvent.remove(token);
    }

    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> SettingsExpander::Items()
    {
        return GetValue(m_itemsProperty).as<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable>>();
    }

    void SettingsExpander::Items(winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> value)
    {
        SetValue(m_itemsProperty, value);
    }

    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::ItemsProperty()
    {
        return m_itemsProperty;
    }

    winrt::Windows::Foundation::IInspectable SettingsExpander::ItemsSource()
    {
        return GetValue(m_itemsSourceProperty);
    }

    void SettingsExpander::ItemsSource(winrt::Windows::Foundation::IInspectable value)
    {
        SetValue(m_itemsSourceProperty, value);
    }

    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::ItemsSourceProperty()
    {
        return m_itemsSourceProperty;
    }

    winrt::Windows::Foundation::IInspectable SettingsExpander::ItemTemplate()
    {
        return GetValue(m_itemTemplateProperty);
    }

    void SettingsExpander::ItemTemplate(winrt::Windows::Foundation::IInspectable value)
    {
        SetValue(m_itemTemplateProperty, value);
    }

    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::ItemTemplateProperty()
    {
        return m_itemTemplateProperty;
    }

    winrt::Windows::UI::Xaml::Controls::StyleSelector SettingsExpander::ItemContainerStyleSelector()
    {
        return GetValue(m_itemContainerStyleSelectorProperty).as<winrt::Windows::UI::Xaml::Controls::StyleSelector>();
    }

    void SettingsExpander::ItemContainerStyleSelector(winrt::Windows::UI::Xaml::Controls::StyleSelector value)
    {
        SetValue(m_itemContainerStyleSelectorProperty, value);
    }

    winrt::Windows::UI::Xaml::DependencyProperty SettingsExpander::ItemContainerStyleSelectorProperty()
    {
        return m_itemContainerStyleSelectorProperty;
    }

    void SettingsExpander::onItemsConnectedPropertyChanged(
        winrt::Windows::UI::Xaml::DependencyObject d,
        winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        if (auto expander = winrt::get_self<SettingsExpander>(d.try_as<UWPPackage::SettingsExpander>()); expander && expander->m_itemsRepeater)
        {
            auto dataSource = expander->ItemsSource();
            if (!dataSource)
                dataSource = expander->Items();

            expander->m_itemsRepeater.ItemsSource(dataSource);
        }
    }

    void SettingsExpander::elementPrepared(
        winrt::Microsoft::UI::Xaml::Controls::ItemsRepeater sender,
        winrt::Microsoft::UI::Xaml::Controls::ItemsRepeaterElementPreparedEventArgs const& args)
    {
        if (ItemContainerStyleSelector())
        {
            if (auto element = args.Element().try_as<winrt::Windows::UI::Xaml::FrameworkElement>();
                element.ReadLocalValue(winrt::Windows::UI::Xaml::FrameworkElement::StyleProperty()) == winrt::Windows::UI::Xaml::DependencyProperty::UnsetValue())
            {
                element.Style(ItemContainerStyleSelector().SelectStyle(nullptr, element));
            }
        }
    }


    SettingsExpander::SettingsExpander()
    {
        Items(winrt::single_threaded_vector<winrt::Windows::Foundation::IInspectable>());
    }

    void SettingsExpander::OnApplyTemplate()
    {
        base_type::OnApplyTemplate();

        if (m_itemsRepeater)
            m_itemsRepeater.ElementPrepared(m_elementPrepared);

        m_itemsRepeater = GetTemplateChild(PART_ItemsRepeater).as<winrt::Microsoft::UI::Xaml::Controls::ItemsRepeater>();
        if (m_itemsRepeater)
        {
            m_elementPrepared = m_itemsRepeater.ElementPrepared({ this, &SettingsExpander::elementPrepared });
            onItemsConnectedPropertyChanged(*this, nullptr);
        }

        //auto expanderHeader = GetTemplateChild(L"ExpanderHeader");
        //expanderHeader.as<winrt::Windows::UI::Xaml::Controls::Primitives::ToggleButton>().Click(
        //    [](auto...)
        //    {
        //        OutputDebugString(L"clicked\n");
        //    }
        //);
    }
}
