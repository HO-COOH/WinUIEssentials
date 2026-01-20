#include "pch.h"
#include "RevealFocusPanel.h"
#if __has_include("RevealFocusPanel.g.cpp")
#include "RevealFocusPanel.g.cpp"
#endif
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include "RevealBrush.h"
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Microsoft.UI.Input.h>

namespace winrt::WinUI3Package::implementation
{
    winrt::Microsoft::UI::Xaml::DependencyProperty RevealFocusPanel::s_panelProperty = 
        winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
            L"Panel",
            winrt::xaml_typename<class_type>(),
            winrt::xaml_typename<class_type>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                nullptr
            }
	);

    winrt::Microsoft::UI::Xaml::DependencyProperty RevealFocusPanel::s_setAsPanelProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
            L"SetAsPanel",
            winrt::xaml_typename<bool>(),
            winrt::xaml_typename<class_type>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                winrt::box_value(false),
                &RevealFocusPanel::onSetAsPanelChanged
            }
        );

	winrt::Microsoft::UI::Xaml::DependencyProperty RevealFocusPanel::s_attachToPanelProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"AttachToPanel",
			winrt::xaml_typename<winrt::Microsoft::UI::Xaml::FrameworkElement>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr,
				&RevealFocusPanel::onAttachToPanelChanged
			}
		);

	RevealFocusPanel::RevealFocusPanel(winrt::Microsoft::UI::Xaml::FrameworkElement const& element)
	{
        m_compositor = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(element).Compositor();
		createResourcesIfNeeded(element);
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty RevealFocusPanel::AttachToPanelProperty()
	{
		return s_attachToPanelProperty;
	}

    winrt::Microsoft::UI::Xaml::DependencyProperty RevealFocusPanel::SetAsPanelProperty()
    {
        return s_setAsPanelProperty;
	}

    void RevealFocusPanel::SetSetAsPanel(
        winrt::Microsoft::UI::Xaml::FrameworkElement const& element,
        bool value
    )
    {
        element.SetValue(SetAsPanelProperty(), winrt::box_value(value));
	}

    bool RevealFocusPanel::GetSetAsPanel(winrt::Microsoft::UI::Xaml::FrameworkElement const& element)
    {
        return winrt::unbox_value<bool>(element.GetValue(SetAsPanelProperty()));
	}
	
	void RevealFocusPanel::SetAttachToPanel(
		winrt::Microsoft::UI::Xaml::FrameworkElement const& element,
        winrt::Microsoft::UI::Xaml::FrameworkElement const& panel
	)
	{
		element.SetValue(AttachToPanelProperty(), panel);
	}

    winrt::Microsoft::UI::Xaml::FrameworkElement RevealFocusPanel::GetAttachToPanel(winrt::Microsoft::UI::Xaml::FrameworkElement const& element)
	{
		return element.GetValue(AttachToPanelProperty()).as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
	}

    void RevealFocusPanel::onSetAsPanelChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
		d.SetValue(s_panelProperty, winrt::WinUI3Package::RevealFocusPanel{ d.as<winrt::Microsoft::UI::Xaml::FrameworkElement>() });
    }

    void RevealFocusPanel::onAttachToPanelChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& d,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
	)
	{
        auto panel = e.NewValue().as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
        auto revealFocusPanelProperty = panel.GetValue(s_panelProperty);

        if (!revealFocusPanelProperty)
            return;

        auto revealFocusPanel = winrt::get_self<RevealFocusPanel>(revealFocusPanelProperty.as<class_type>());

        //create border geometry
        auto child = d.as<winrt::Microsoft::UI::Xaml::UIElement>();
        auto elementVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(child);

        auto borderGeometry = revealFocusPanel->m_compositor.CreateRoundedRectangleGeometry();
        auto overlayGeometry = revealFocusPanel->m_compositor.CreateRoundedRectangleGeometry();

        // Adjust size to account for stroke being centered (inset by half stroke thickness)
        float const strokeThickness = 1.0f;
        float const halfStroke = strokeThickness / 2.0f;
        revealFocusPanel->m_borderGeometrySizeExpressionAnimation.SetReferenceParameter(L"hostVisual", elementVisual);
        revealFocusPanel->m_borderGeometrySizeExpressionAnimation.SetScalarParameter(L"strokeWidth", strokeThickness);
        borderGeometry.StartAnimation(L"Size", revealFocusPanel->m_borderGeometrySizeExpressionAnimation);

        //set CornerRadius if child has such property
        winrt::Microsoft::UI::Xaml::CornerRadius cornerRadius{};
        if (auto control = child.try_as<winrt::Microsoft::UI::Xaml::Controls::Control>())
            cornerRadius = control.CornerRadius();
        else if (auto contentPresenter = child.try_as<winrt::Microsoft::UI::Xaml::Controls::ContentPresenter>())
            cornerRadius = contentPresenter.CornerRadius();
        if (cornerRadius.TopLeft)
        {
            float const adjustedRadius = (std::max)(0.0f, static_cast<float>(cornerRadius.TopLeft) - halfStroke);
            borderGeometry.CornerRadius({ adjustedRadius, adjustedRadius });
            overlayGeometry.CornerRadius({ static_cast<float>(cornerRadius.TopLeft), static_cast<float>(cornerRadius.TopLeft) });
        }

        borderGeometry.Offset({ halfStroke, halfStroke });

        RevealBrush brush{ revealFocusPanel->m_compositor };
        auto borderShape = revealFocusPanel->m_compositor.CreateSpriteShape(borderGeometry);
        borderShape.StrokeThickness(strokeThickness);
        borderShape.StrokeBrush(brush);

        auto borderVisual = revealFocusPanel->m_compositor.CreateShapeVisual();
        borderVisual.Shapes().Append(borderShape);
        revealFocusPanel->m_hostVisualSizeExpressionAnimation.SetReferenceParameter(L"hostVisual", elementVisual);
        borderVisual.StartAnimation(L"Size", revealFocusPanel->m_hostVisualSizeExpressionAnimation);
        borderVisual.BorderMode(winrt::Microsoft::UI::Composition::CompositionBorderMode::Soft);

        auto localProperty = revealFocusPanel->m_compositor.CreatePropertySet();
        localProperty.InsertVector2(L"elementPosition", {});
        revealFocusPanel->m_ellipseCenterExpressionAnimation.SetReferenceParameter(L"localProperty", localProperty);


        child.as<winrt::Microsoft::UI::Xaml::FrameworkElement>().LayoutUpdated([localProperty, child, panel](auto&&...) {
            auto transform = child.TransformToVisual(panel).TransformPoint({});
            localProperty.InsertVector2(L"elementPosition", transform);
        });


        brush.StartAnimation(L"EllipseCenter", revealFocusPanel->m_ellipseCenterExpressionAnimation);

        revealFocusPanel->m_hostVisualSizeExpressionAnimation.SetReferenceParameter(L"hostVisual", elementVisual);
        overlayGeometry.StartAnimation(L"Size", revealFocusPanel->m_hostVisualSizeExpressionAnimation);

        auto overlayShape = revealFocusPanel->m_compositor.CreateSpriteShape(overlayGeometry);
        overlayShape.FillBrush(brush);
        auto overlayVisual = revealFocusPanel->m_compositor.CreateShapeVisual();
        overlayVisual.Shapes().Append(overlayShape);
        overlayVisual.StartAnimation(L"Size", revealFocusPanel->m_hostVisualSizeExpressionAnimation);
        overlayVisual.Opacity(0.f);

        // Position the overlay at the element's location within the panel
        revealFocusPanel->m_visualOffsetExpressionAnimation.SetReferenceParameter(L"localProperty", localProperty);
        overlayVisual.StartAnimation(L"Offset.XY", revealFocusPanel->m_visualOffsetExpressionAnimation);
        borderVisual.StartAnimation(L"Offset.XY", revealFocusPanel->m_visualOffsetExpressionAnimation);

        // Add overlay to panel's overlay container (renders at panel level, behind XAML children)
        auto overlayVisuals = revealFocusPanel->m_overlayContainer.Children();
        overlayVisuals.InsertAtTop(overlayVisual);
        overlayVisuals.InsertAtTop(borderVisual);

        child.PointerEntered([overlayVisual, revealFocusPanel](auto&&...) {
            overlayVisual.StartAnimation(L"Opacity", revealFocusPanel->m_opacityForwardAnimation);
        });
        child.PointerExited([overlayVisual, revealFocusPanel](auto&&...) {
            overlayVisual.StartAnimation(L"Opacity", revealFocusPanel->m_opacityBackwardAnimation);
        });

        child.AddHandler(
            winrt::Microsoft::UI::Xaml::UIElement::PointerPressedEvent(),
            winrt::box_value(winrt::Microsoft::UI::Xaml::Input::PointerEventHandler{ 
                [revealFocusPanel, brush](auto&&...)
                {
                    brush.StartAnimation(L"EllipseRadius", revealFocusPanel->m_revealBrushRadiusForwardAnimation);
                }     
            }),
            true
        );

        child.AddHandler(
            winrt::Microsoft::UI::Xaml::UIElement::PointerReleasedEvent(),
            winrt::box_value(winrt::Microsoft::UI::Xaml::Input::PointerEventHandler{
                [revealFocusPanel, brush](auto&&...)
                {
                    brush.StartAnimation(L"EllipseRadius", revealFocusPanel->m_revealBrushRadiusBackwardAnimation);
                }
                }),
            true
        );
	}

	void RevealFocusPanel::createResourcesIfNeeded(winrt::Microsoft::UI::Xaml::FrameworkElement const& element)
	{
        if (m_globalPropertySet)
            return;

        m_globalPropertySet = m_compositor.CreatePropertySet();
        m_globalPropertySet.InsertVector2(L"MousePosition", InitialMousePosition);

        m_opacityForwardAnimation = m_compositor.CreateScalarKeyFrameAnimation();
        m_opacityForwardAnimation.InsertKeyFrame(1.f, 0.8f);

        m_opacityBackwardAnimation = m_compositor.CreateScalarKeyFrameAnimation();
        m_opacityBackwardAnimation.InsertKeyFrame(1.f, 0.f);

        m_revealBrushRadiusForwardAnimation = m_compositor.CreateVector2KeyFrameAnimation();
        m_revealBrushRadiusForwardAnimation.InsertKeyFrame(1.f, { 200.f, 200.f });

        m_revealBrushRadiusBackwardAnimation = m_compositor.CreateVector2KeyFrameAnimation();
        m_revealBrushRadiusBackwardAnimation.InsertKeyFrame(1.f, { 100.f, 100.f });

        m_hostVisualSizeExpressionAnimation = m_compositor.CreateExpressionAnimation(hostVisualSizeExpression);
        m_borderGeometrySizeExpressionAnimation = m_compositor.CreateExpressionAnimation(borderGeometrySizeExpression);

        m_ellipseCenterExpressionAnimation = m_compositor.CreateExpressionAnimation(ellipseCenterExpression);
        m_ellipseCenterExpressionAnimation.SetReferenceParameter(L"globalProperty", m_globalPropertySet);

        m_visualOffsetExpressionAnimation = m_compositor.CreateExpressionAnimation(L"localProperty.elementPosition");

        // Create overlay container and attach to the overlay canvas (which has ZIndex = -1)
        // This ensures overlays render behind other Grid children
        m_overlayContainer = m_compositor.CreateContainerVisual();
        
        // Clip the overlay container to the panel's bounds
        // This prevents overlays from showing outside scrollable areas
        auto panelVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(element).as < winrt::Microsoft::UI::Composition::ContainerVisual>();
        auto sizeExpression = m_compositor.CreateExpressionAnimation(L"panelVisual.Size");
        sizeExpression.SetReferenceParameter(L"panelVisual", panelVisual);
        m_overlayContainer.StartAnimation(L"Size", sizeExpression);
        m_overlayContainer.Clip(m_compositor.CreateInsetClip());
        panelVisual.Children().InsertAtBottom(m_overlayContainer);
        
        //winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(element, m_overlayContainer);

        element.PointerEntered({ this, &RevealFocusPanel::onUpdateMousePosition });
        element.PointerMoved({this, &RevealFocusPanel::onUpdateMousePosition});

        element.PointerExited([this](auto const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args) {
            m_globalPropertySet.InsertVector2(L"MousePosition", InitialMousePosition);
        });
	}

    void RevealFocusPanel::onUpdateMousePosition(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args)
    {
        m_globalPropertySet.InsertVector2(L"MousePosition", args.GetCurrentPoint(sender.as<winrt::Microsoft::UI::Xaml::UIElement>()).Position());
    }
}
