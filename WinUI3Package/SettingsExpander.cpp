#include "pch.h"
#include "SettingsExpander.h"
#if __has_include("SettingsExpander.g.cpp")
#include "SettingsExpander.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::m_headerIconProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"HeaderIcon",
            winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
            winrt::xaml_typename<WinUI3Package::SettingsExpander>(),
            Microsoft::UI::Xaml::PropertyMetadata::Create(winrt::Windows::Foundation::IInspectable{})
        );

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::m_contentProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Content",
            winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
            winrt::xaml_typename<WinUI3Package::SettingsExpander>(),
            Microsoft::UI::Xaml::PropertyMetadata::Create(winrt::Windows::Foundation::IInspectable{})
        );

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::m_descriptionProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Description",
            winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
            winrt::xaml_typename<WinUI3Package::SettingsExpander>(),
            { nullptr }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::m_itemsFooterProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"ItemsFooter",
            winrt::xaml_typename<winrt::Microsoft::UI::Xaml::UIElement>(),
            winrt::xaml_typename<WinUI3Package::SettingsExpander>(),
            { nullptr }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::m_isExpandedProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"IsExpanded",
            winrt::xaml_typename<bool>(),
            winrt::xaml_typename<WinUI3Package::SettingsExpander>(),
            Microsoft::UI::Xaml::PropertyMetadata{
                winrt::box_value(false),
                [](winrt::Microsoft::UI::Xaml::DependencyObject d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e)
                {
                    winrt::get_self<SettingsExpander>(d.as<WinUI3Package::SettingsExpander>())->onIsExpandedPropertyChanged(
                        winrt::unbox_value<bool>(e.OldValue()),
                        winrt::unbox_value<bool>(e.NewValue())
                    );
                }
            }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::m_headerProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Header",
            winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
            winrt::xaml_typename<WinUI3Package::SettingsExpander>(),
            { nullptr }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::m_itemsHeaderProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"ItemsHeader",
            winrt::xaml_typename<winrt::Microsoft::UI::Xaml::UIElement>(),
            winrt::xaml_typename<WinUI3Package::SettingsExpander>(),
            { nullptr }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::m_itemsProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Items",
            winrt::xaml_typename<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable>>(),
            winrt::xaml_typename<WinUI3Package::SettingsExpander>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                nullptr,
                &SettingsExpander::onItemsConnectedPropertyChanged
            }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::m_itemsSourceProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"ItemsSource",
            winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
            winrt::xaml_typename<WinUI3Package::SettingsExpander>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                nullptr,
                &SettingsExpander::onItemsConnectedPropertyChanged
            }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::m_itemTemplateProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"ItemTemplate",
            winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
            winrt::xaml_typename<WinUI3Package::SettingsExpander>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::m_itemContainerStyleSelectorProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"ItemContainerStyleSelector",
            winrt::xaml_typename<winrt::Microsoft::UI::Xaml::Controls::StyleSelector>(),
            winrt::xaml_typename<WinUI3Package::SettingsExpander>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr }
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
    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::HeaderProperty()
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

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::ContentProperty()
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
    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::DescriptionProperty()
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
    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::HeaderIconProperty()
    {
        return m_headerIconProperty;
    }

    //items header
    winrt::Microsoft::UI::Xaml::UIElement SettingsExpander::ItemsHeader()
    {
        return GetValue(m_itemsHeaderProperty).as<winrt::Microsoft::UI::Xaml::UIElement>();
    }
    void SettingsExpander::ItemsHeader(winrt::Microsoft::UI::Xaml::UIElement expanderContent)
    {
        SetValue(m_itemsHeaderProperty, expanderContent);
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::ItemsHeaderProperty()
    {
        return m_itemsHeaderProperty;
    }

    //items footer
    winrt::Microsoft::UI::Xaml::UIElement SettingsExpander::ItemsFooter()
    {
        return GetValue(m_itemsFooterProperty).as<winrt::Microsoft::UI::Xaml::UIElement>();
    }
    void SettingsExpander::ItemsFooter(winrt::Microsoft::UI::Xaml::UIElement expanderContent)
    {
        SetValue(m_itemsFooterProperty, expanderContent);
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::ItemsFooterProperty()
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
    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::IsExpandedProperty()
    {
        return m_isExpandedProperty;
    }

    //Expanded event
    winrt::event_token SettingsExpander::Expanded(WinUI3Package::SignalDelegate const& handler)
    {
        return m_expandedEvent.add(handler);
    }
    void SettingsExpander::Expanded(winrt::event_token const& token)
    {
        m_expandedEvent.remove(token);
    }

    //Collapsed event
    winrt::event_token SettingsExpander::Collapsed(WinUI3Package::SignalDelegate const& handler)
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

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::ItemsProperty()
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

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::ItemsSourceProperty()
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

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::ItemTemplateProperty()
    {
        return m_itemTemplateProperty;
    }

    winrt::Microsoft::UI::Xaml::Controls::StyleSelector SettingsExpander::ItemContainerStyleSelector()
    {
        return GetValue(m_itemContainerStyleSelectorProperty).as<winrt::Microsoft::UI::Xaml::Controls::StyleSelector>();
    }

    void SettingsExpander::ItemContainerStyleSelector(winrt::Microsoft::UI::Xaml::Controls::StyleSelector value)
    {
        SetValue(m_itemContainerStyleSelectorProperty, value);
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsExpander::ItemContainerStyleSelectorProperty()
    {
        return m_itemContainerStyleSelectorProperty;
    }

    void SettingsExpander::onItemsConnectedPropertyChanged(
        winrt::Microsoft::UI::Xaml::DependencyObject d,
        winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        if (auto expander = winrt::get_self<SettingsExpander>(d.try_as<WinUI3Package::SettingsExpander>()); expander && expander->m_itemsRepeater)
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
            if (auto element = args.Element().try_as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
                element.ReadLocalValue(winrt::Microsoft::UI::Xaml::FrameworkElement::StyleProperty()) == winrt::Microsoft::UI::Xaml::DependencyProperty::UnsetValue())
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
        //expanderHeader.as<winrt::Microsoft::UI::Xaml::Controls::Primitives::ToggleButton>().Click(
        //    [](auto...)
        //    {
        //        OutputDebugString(L"clicked\n");
        //    }
        //);
    }
}
