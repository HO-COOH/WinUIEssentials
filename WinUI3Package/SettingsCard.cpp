﻿#include "pch.h"
#include "SettingsCard.h"
#if __has_include("SettingsCard.g.cpp")
#include "SettingsCard.g.cpp"
#endif
#include <winrt/Microsoft.UI.Xaml.Input.h>

namespace winrt::WinUI3Package::implementation
{
    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsCard::m_headerProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Header",
            winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
            winrt::xaml_typename<WinUI3Package::SettingsCard>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                nullptr,
                [](winrt::Microsoft::UI::Xaml::DependencyObject d, auto)
                {
                    winrt::get_self<SettingsCard>(d.as<WinUI3Package::SettingsCard>())->onHeaderChanged();
                }
            }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsCard::m_descriptionProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Description",
            winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
            winrt::xaml_typename<WinUI3Package::SettingsCard>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                nullptr,
                [](winrt::Microsoft::UI::Xaml::DependencyObject d, auto)
                {
                    winrt::get_self<SettingsCard>(d.as<WinUI3Package::SettingsCard>())->onDescriptionChanged();
                }
            }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsCard::m_headerIconProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"HeaderIcon",
            winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
            winrt::xaml_typename<WinUI3Package::SettingsCard>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                nullptr,
                [](winrt::Microsoft::UI::Xaml::DependencyObject d, auto)
                {
                    winrt::get_self<SettingsCard>(d.as<WinUI3Package::SettingsCard>())->onHeaderIconChanged();
                }
            }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsCard::m_actionIconProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"ActionIcon",
            winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
            winrt::xaml_typename<WinUI3Package::SettingsCard>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                winrt::box_value(winrt::hstring{L"\ue974"})
            }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsCard::m_actionIconToolTipProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"ActionIconToolTip",
            winrt::xaml_typename<winrt::hstring>(),
            winrt::xaml_typename<WinUI3Package::SettingsCard>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsCard::m_isClickEnabledProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"IsClickEnabled",
            winrt::xaml_typename<bool>(),
            winrt::xaml_typename<WinUI3Package::SettingsCard>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                winrt::box_value(false),
                [](winrt::Microsoft::UI::Xaml::DependencyObject d, auto)
                {
                    winrt::get_self<SettingsCard>(d.as<WinUI3Package::SettingsCard>())->onIsClickEnabledChanged();
                }
            }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsCard::m_isActionIconVisibleProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"IsActionIconVisible",
            winrt::xaml_typename<bool>(),
            winrt::xaml_typename<WinUI3Package::SettingsCard>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                winrt::box_value(true),
                [](winrt::Microsoft::UI::Xaml::DependencyObject d, auto)
                {
                    winrt::get_self<SettingsCard>(d.as<WinUI3Package::SettingsCard>())->onActionIconChanged();
                }



            }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsCard::m_contentAlignmentProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"ContentAlignment",
            winrt::xaml_typename<WinUI3Package::ContentAlignment>(),
            winrt::xaml_typename<WinUI3Package::SettingsCard>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(WinUI3Package::ContentAlignment::Right) }
    );

    void SettingsCard::OnApplyTemplate()
    {
        base_type::OnApplyTemplate();
        onActionIconChanged();
        onHeaderChanged();
        onHeaderIconChanged();
        onDescriptionChanged();
        onIsClickEnabledChanged();
        winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(
            *this,
            IsEnabled() ? NormalState : DisabledState,
            true);
        IsEnabledChanged({ this, &SettingsCard::onIsEnabledChanged });
    }

    //Header
    winrt::Windows::Foundation::IInspectable SettingsCard::Header()
    {
        return GetValue(m_headerProperty);
    }
    void SettingsCard::Header(winrt::Windows::Foundation::IInspectable value)
    {
        SetValue(m_headerProperty, value);
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsCard::HeaderProperty()
    {
        return m_headerProperty;
    }

    //Description
    winrt::Windows::Foundation::IInspectable SettingsCard::Description()
    {
        return GetValue(m_descriptionProperty);
    }
    void SettingsCard::Description(winrt::Windows::Foundation::IInspectable value)
    {
        SetValue(m_descriptionProperty, value);
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsCard::DescriptionProperty()
    {
        return m_descriptionProperty;
    }

    //HeaderIcon
    winrt::Windows::Foundation::IInspectable SettingsCard::HeaderIcon()
    {
        return GetValue(m_headerIconProperty);
    }
    void SettingsCard::HeaderIcon(winrt::Windows::Foundation::IInspectable value)
    {
        SetValue(m_headerIconProperty, value);
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsCard::HeaderIconProperty()
    {
        return m_headerIconProperty;
    }

    //ActionIcon
    winrt::Windows::Foundation::IInspectable SettingsCard::ActionIcon()
    {
        return GetValue(m_actionIconProperty);
    }
    void SettingsCard::ActionIcon(winrt::Windows::Foundation::IInspectable value)
    {
        SetValue(m_actionIconProperty, value);
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsCard::ActionIconProperty()
    {
        return m_actionIconProperty;
    }

    //ActionIconToolTip
    winrt::hstring SettingsCard::ActionIconToolTip()
    {
        return winrt::unbox_value<winrt::hstring>(GetValue(m_actionIconToolTipProperty));
    }
    void SettingsCard::ActionIconToolTip(winrt::hstring value)
    {
        SetValue(m_actionIconToolTipProperty, winrt::box_value(value));
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsCard::ActionIconToolTipProperty()
    {
        return m_actionIconToolTipProperty;
    }

    //IsClickEnabled
    bool SettingsCard::IsClickEnabled()
    {
        return winrt::unbox_value<bool>(GetValue(m_isClickEnabledProperty));
    }
    void SettingsCard::IsClickEnabled(bool value)
    {
        SetValue(m_isClickEnabledProperty, winrt::box_value(value));
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsCard::IsClickEnabledProperty()
    {
        return m_isClickEnabledProperty;
    }

    //IsActionIconVisible
    bool SettingsCard::IsActionIconVisible()
    {
        return winrt::unbox_value<bool>(GetValue(m_isActionIconVisibleProperty));
    }
    void SettingsCard::IsActionIconVisible(bool value)
    {
        SetValue(m_isActionIconVisibleProperty, winrt::box_value(value));
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsCard::IsActionIconVisibleProperty()
    {
        return m_isActionIconVisibleProperty;
    }

    //ContentAlignment
    WinUI3Package::ContentAlignment SettingsCard::ContentAlignment()
    {
        return winrt::unbox_value<WinUI3Package::ContentAlignment>(GetValue(m_contentAlignmentProperty));
    }
    void SettingsCard::ContentAlignment(WinUI3Package::ContentAlignment value)
    {
        SetValue(m_contentAlignmentProperty, winrt::box_value(value));
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty SettingsCard::ContentAlignmentProperty()
    {
        return m_contentAlignmentProperty;
    }

    void SettingsCard::OnPointerPressed(winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        if (IsClickEnabled())
        {
            base_type::OnPointerPressed(e);
            winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, PressedState, true);
        }
    }

    void SettingsCard::OnPointerReleased(winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        if (IsClickEnabled())
        {
            base_type::OnPointerReleased(e);
            winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(
                *this,
                m_isPointerOver ? PointerOverState : NormalState,
                true);
        }
    }


    void SettingsCard::onIsClickEnabledChanged()
    {
        onActionIconChanged();
        if (IsClickEnabled())
        {
            enableButtonInteraction();
        }
        else
        {
            disableButtonInteraction();
        }
    }

    void SettingsCard::onActionIconChanged()
    {
        if (auto actionIconPresenter = GetTemplateChild(ActionIconPresenterHolder)
            .try_as<winrt::Microsoft::UI::Xaml::FrameworkElement>())
        {
            if (IsClickEnabled() && IsActionIconVisible())
            {
                actionIconPresenter.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
            }
            else
            {
                actionIconPresenter.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
            }
        }
    }

    void SettingsCard::onHeaderChanged()
    {
        if (auto headerPresenter = GetTemplateChild(HeaderPresenter)
            .try_as<winrt::Microsoft::UI::Xaml::FrameworkElement>())
        {
            headerPresenter.Visibility(
                Header() ?
                winrt::Microsoft::UI::Xaml::Visibility::Visible :
                winrt::Microsoft::UI::Xaml::Visibility::Collapsed
            );
        }
    }

    void SettingsCard::onHeaderIconChanged()
    {
        if (auto headerIconPresenter = GetTemplateChild(HeaderIconPresenterHolder)
            .try_as<winrt::Microsoft::UI::Xaml::FrameworkElement>())
        {
            headerIconPresenter.Visibility(
                HeaderIcon() ?
                winrt::Microsoft::UI::Xaml::Visibility::Visible :
                winrt::Microsoft::UI::Xaml::Visibility::Collapsed
            );
        }
    }

    void SettingsCard::onDescriptionChanged()
    {
        if (auto descriptionPresenter = GetTemplateChild(DescriptionPresenter)
            .try_as<winrt::Microsoft::UI::Xaml::FrameworkElement>())
        {
            descriptionPresenter.Visibility(
                Description() ?
                winrt::Microsoft::UI::Xaml::Visibility::Visible :
                winrt::Microsoft::UI::Xaml::Visibility::Collapsed
            );
        }
    }

    void SettingsCard::onIsEnabledChanged(
        winrt::Windows::Foundation::IInspectable,
        winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const&)
    {
        winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(
            *this,
            IsEnabled() ? NormalState : DisabledState,
            true
        );
    }

    void SettingsCard::disableButtonInteraction()
    {
        IsTabStop(false);
        PointerEntered(m_pointerEntered);
        PointerExited(m_pointerExited);
        PointerCaptureLost(m_pointerCaptureLost);
        PointerCanceled(m_pointerCanceled);
        PreviewKeyDown(m_previewKeyDown);
        PreviewKeyUp(m_previewKeyUp);
    }


    void SettingsCard::enableButtonInteraction()
    {
        disableButtonInteraction();

        IsTabStop(true);
        m_pointerEntered = PointerEntered({ this, &SettingsCard::pointerEntered });
        m_pointerExited = PointerExited({ this, &SettingsCard::pointerExited });
        m_pointerCaptureLost = PointerCaptureLost({ this, &SettingsCard::pointerCaptureLost });
        m_pointerCanceled = PointerCanceled({ this, &SettingsCard::pointerCanceled });
        m_previewKeyDown = PreviewKeyDown({ this, &SettingsCard::previewKeyDown });
        m_previewKeyUp = PreviewKeyUp({ this, &SettingsCard::previewKeyUp });
    }


    void SettingsCard::pointerEntered(
        winrt::Windows::Foundation::IInspectable sender,
        winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        base_type::OnPointerEntered(e);
        m_isPointerOver = true;
        winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, PointerOverState, true);
    }

    void SettingsCard::pointerExited(
        winrt::Windows::Foundation::IInspectable sender,
        winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        base_type::OnPointerExited(e);
        m_isPointerOver = false;
        winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, NormalState, true);
    }

    void SettingsCard::pointerCaptureLost(
        winrt::Windows::Foundation::IInspectable sender,
        winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        base_type::OnPointerCaptureLost(e);
        winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, NormalState, true);
    }

    void SettingsCard::pointerCanceled(
        winrt::Windows::Foundation::IInspectable sender,
        winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        base_type::OnPointerCanceled(e);
        winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, NormalState, true);
    }

    void SettingsCard::previewKeyUp(
        winrt::Windows::Foundation::IInspectable sender,
        winrt::Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& e)
    {
        if (contains(PreviewKeys, e.Key()))
        {
            winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, NormalState, true);
        }
    }

    void SettingsCard::previewKeyDown(
        winrt::Windows::Foundation::IInspectable sender,
        winrt::Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& e)
    {
        if (contains(PreviewKeys, e.Key()))
        {
            if (getFocusedElement().try_as<WinUI3Package::SettingsCard>())
            {
                winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, PressedState, true);
            }
        }
    }
    winrt::Microsoft::UI::Xaml::FrameworkElement SettingsCard::getFocusedElement()
    {
        //TODO: Add XamlRoot Api detection
        //if (XamlRoot())
        //{
        //    return winrt::Microsoft::UI::Xaml::Input::FocusManager::GetFocusedElement(XamlRoot())
        //        .try_as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
        //}
        //else
        //{
        //    return winrt::Microsoft::UI::Xaml::Input::FocusManager::GetFocusedElement()
        //        .try_as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
        //}
        return winrt::Microsoft::UI::Xaml::Input::FocusManager::GetFocusedElement()
            .try_as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
    }
}
