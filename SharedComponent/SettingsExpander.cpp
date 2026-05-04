#include "pch.h"
#include "SettingsExpander.h"
#if __has_include("SettingsExpander.g.cpp")
#include "SettingsExpander.g.cpp"
#endif

namespace winrt::PackageRoot::implementation
{
	void SettingsExpander::EnsureDependencyProperties()
	{
		if (m_headerIconProperty) return;
		m_headerIconProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"HeaderIcon",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<PackageRoot::SettingsExpander>(),
			WinUINamespace::UI::Xaml::PropertyMetadata::Create(winrt::Windows::Foundation::IInspectable{})
		);
		m_contentProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"Content",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<PackageRoot::SettingsExpander>(),
			WinUINamespace::UI::Xaml::PropertyMetadata::Create(winrt::Windows::Foundation::IInspectable{})
		);
		m_descriptionProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"Description",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<PackageRoot::SettingsExpander>(),
			{ nullptr }
		);
		m_itemsFooterProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"ItemsFooter",
			winrt::xaml_typename<winrt::WinUINamespace::UI::Xaml::UIElement>(),
			winrt::xaml_typename<PackageRoot::SettingsExpander>(),
			{ nullptr }
		);
		m_isExpandedProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"IsExpanded",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<PackageRoot::SettingsExpander>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{
				winrt::box_value(false),
				[](winrt::WinUINamespace::UI::Xaml::DependencyObject d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs e)
				{
					winrt::get_self<SettingsExpander>(d.as<PackageRoot::SettingsExpander>())->onIsExpandedPropertyChanged(
						winrt::unbox_value<bool>(e.OldValue()),
						winrt::unbox_value<bool>(e.NewValue())
					);
				}
			}
		);
		m_headerProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"Header",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<PackageRoot::SettingsExpander>(),
			{ nullptr }
		);
		m_itemsHeaderProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"ItemsHeader",
			winrt::xaml_typename<winrt::WinUINamespace::UI::Xaml::UIElement>(),
			winrt::xaml_typename<PackageRoot::SettingsExpander>(),
			{ nullptr }
		);
		m_itemsProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"Items",
			winrt::xaml_typename<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable>>(),
			winrt::xaml_typename<PackageRoot::SettingsExpander>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{
				nullptr,
				&SettingsExpander::onItemsConnectedPropertyChanged
			}
		);
		m_itemsSourceProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"ItemsSource",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<PackageRoot::SettingsExpander>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{
				nullptr,
				&SettingsExpander::onItemsConnectedPropertyChanged
			}
		);
		m_itemTemplateProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"ItemTemplate",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<PackageRoot::SettingsExpander>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr }
		);
		m_itemContainerStyleSelectorProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"ItemContainerStyleSelector",
			winrt::xaml_typename<winrt::WinUINamespace::UI::Xaml::Controls::StyleSelector>(),
			winrt::xaml_typename<PackageRoot::SettingsExpander>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr }
		);
	}

//header
    winrt::Windows::Foundation::IInspectable SettingsExpander::Header()
    {
        return GetValue(m_headerProperty);
    }
    void SettingsExpander::Header(winrt::Windows::Foundation::IInspectable header)
    {
        SetValue(m_headerProperty, header);
    }
    winrt::WinUINamespace::UI::Xaml::DependencyProperty SettingsExpander::HeaderProperty()
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

    winrt::WinUINamespace::UI::Xaml::DependencyProperty SettingsExpander::ContentProperty()
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
    winrt::WinUINamespace::UI::Xaml::DependencyProperty SettingsExpander::DescriptionProperty()
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
    winrt::WinUINamespace::UI::Xaml::DependencyProperty SettingsExpander::HeaderIconProperty()
    {
        return m_headerIconProperty;
    }

    //items header
    winrt::WinUINamespace::UI::Xaml::UIElement SettingsExpander::ItemsHeader()
    {
        return GetValue(m_itemsHeaderProperty).as<winrt::WinUINamespace::UI::Xaml::UIElement>();
    }
    void SettingsExpander::ItemsHeader(winrt::WinUINamespace::UI::Xaml::UIElement expanderContent)
    {
        SetValue(m_itemsHeaderProperty, expanderContent);
    }
    winrt::WinUINamespace::UI::Xaml::DependencyProperty SettingsExpander::ItemsHeaderProperty()
    {
        return m_itemsHeaderProperty;
    }

    //items footer
    winrt::WinUINamespace::UI::Xaml::UIElement SettingsExpander::ItemsFooter()
    {
        return GetValue(m_itemsFooterProperty).as<winrt::WinUINamespace::UI::Xaml::UIElement>();
    }
    void SettingsExpander::ItemsFooter(winrt::WinUINamespace::UI::Xaml::UIElement expanderContent)
    {
        SetValue(m_itemsFooterProperty, expanderContent);
    }
    winrt::WinUINamespace::UI::Xaml::DependencyProperty SettingsExpander::ItemsFooterProperty()
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
    winrt::WinUINamespace::UI::Xaml::DependencyProperty SettingsExpander::IsExpandedProperty()
    {
        return m_isExpandedProperty;
    }

    //Expanded event
    winrt::event_token SettingsExpander::Expanded(PackageRoot::SignalDelegate const& handler)
    {
        return m_expandedEvent.add(handler);
    }
    void SettingsExpander::Expanded(winrt::event_token const& token)
    {
        m_expandedEvent.remove(token);
    }

    //Collapsed event
    winrt::event_token SettingsExpander::Collapsed(PackageRoot::SignalDelegate const& handler)
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

    winrt::WinUINamespace::UI::Xaml::DependencyProperty SettingsExpander::ItemsProperty()
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

    winrt::WinUINamespace::UI::Xaml::DependencyProperty SettingsExpander::ItemsSourceProperty()
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

    winrt::WinUINamespace::UI::Xaml::DependencyProperty SettingsExpander::ItemTemplateProperty()
    {
        return m_itemTemplateProperty;
    }

    winrt::WinUINamespace::UI::Xaml::Controls::StyleSelector SettingsExpander::ItemContainerStyleSelector()
    {
        return GetValue(m_itemContainerStyleSelectorProperty).as<winrt::WinUINamespace::UI::Xaml::Controls::StyleSelector>();
    }

    void SettingsExpander::ItemContainerStyleSelector(winrt::WinUINamespace::UI::Xaml::Controls::StyleSelector value)
    {
        SetValue(m_itemContainerStyleSelectorProperty, value);
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty SettingsExpander::ItemContainerStyleSelectorProperty()
    {
        return m_itemContainerStyleSelectorProperty;
    }

    void SettingsExpander::onItemsConnectedPropertyChanged(
        winrt::WinUINamespace::UI::Xaml::DependencyObject d,
        winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        if (auto expander = winrt::get_self<SettingsExpander>(d.try_as<PackageRoot::SettingsExpander>()); expander && expander->m_itemsRepeater)
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
            if (auto element = args.Element().try_as<winrt::WinUINamespace::UI::Xaml::FrameworkElement>();
                element.ReadLocalValue(winrt::WinUINamespace::UI::Xaml::FrameworkElement::StyleProperty()) == winrt::WinUINamespace::UI::Xaml::DependencyProperty::UnsetValue())
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
        //expanderHeader.as<winrt::WinUINamespace::UI::Xaml::Controls::Primitives::ToggleButton>().Click(
        //    [](auto...)
        //    {
        //        OutputDebugString(L"clicked\n");
        //    }
        //);
    }
}
