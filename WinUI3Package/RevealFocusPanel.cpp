#include "pch.h"
#include "RevealFocusPanel.h"
#if __has_include("RevealFocusPanel.g.cpp")
#include "RevealFocusPanel.g.cpp"
#endif
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Microsoft.UI.Input.h>

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty RevealFocusPanel::s_attachToPanelProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"AttachToPanel",
			winrt::xaml_typename<class_type>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr,
				&RevealFocusPanel::onAttachToPanelChanged
			}
		);

	RevealFocusPanel::RevealFocusPanel()
	{
        m_compositor = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(*this).Compositor();
        Background(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush{ winrt::Windows::UI::Colors::Transparent() });

        // Create a Canvas for overlays that sits behind all other content (ZIndex = -1)
        winrt::Microsoft::UI::Xaml::Controls::Canvas::SetZIndex(m_overlayCanvas, -1);
        Children().Append(m_overlayCanvas);
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty RevealFocusPanel::AttachToPanelProperty()
	{
		return s_attachToPanelProperty;
	}
	
	void RevealFocusPanel::SetAttachToPanel(
		winrt::Microsoft::UI::Xaml::FrameworkElement const& element,
		winrt::WinUI3Package::RevealFocusPanel const& panel
	)
	{
		element.SetValue(AttachToPanelProperty(), panel);
	}

	winrt::WinUI3Package::RevealFocusPanel RevealFocusPanel::GetAttachToPanel(winrt::Microsoft::UI::Xaml::FrameworkElement const& element)
	{
		return element.GetValue(AttachToPanelProperty()).as<winrt::WinUI3Package::RevealFocusPanel>();
	}

	void RevealFocusPanel::onAttachToPanelChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& d,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
	)
	{
        auto panel = e.NewValue().as<winrt::WinUI3Package::RevealFocusPanel>();
        auto revealFocusPanel = winrt::get_self<RevealFocusPanel>(panel);
        revealFocusPanel->createResourcesIfNeeded();

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
        winrt::Microsoft::UI::Xaml::CornerRadius cornerRadius{ -1 };
        if (auto control = child.try_as<winrt::Microsoft::UI::Xaml::Controls::Control>())
            cornerRadius = control.CornerRadius();
        else if (auto contentPresenter = child.try_as<winrt::Microsoft::UI::Xaml::Controls::ContentPresenter>())
            cornerRadius = contentPresenter.CornerRadius();
        if (cornerRadius.TopLeft != -1)
        {
            float const adjustedRadius = (std::max)(0.0f, static_cast<float>(cornerRadius.TopLeft) - halfStroke);
            borderGeometry.CornerRadius({ adjustedRadius, adjustedRadius });
            overlayGeometry.CornerRadius({ static_cast<float>(cornerRadius.TopLeft), static_cast<float>(cornerRadius.TopLeft) });
        }

        borderGeometry.Offset({ halfStroke, halfStroke });
        auto borderShape = revealFocusPanel->m_compositor.CreateSpriteShape(borderGeometry);
        borderShape.StrokeThickness(strokeThickness);

        auto borderVisual = revealFocusPanel->m_compositor.CreateShapeVisual();
        borderVisual.Shapes().Append(borderShape);
        revealFocusPanel->m_hostVisualSizeExpressionAnimation.SetReferenceParameter(L"hostVisual", elementVisual);
        borderVisual.StartAnimation(L"Size", revealFocusPanel->m_hostVisualSizeExpressionAnimation);
        borderVisual.BorderMode(winrt::Microsoft::UI::Composition::CompositionBorderMode::Soft);

        auto localProperty = revealFocusPanel->m_compositor.CreatePropertySet();
        localProperty.InsertVector2(L"elementPosition", {});

        child.as<winrt::Microsoft::UI::Xaml::FrameworkElement>().LayoutUpdated([localProperty, child, panel](auto&&...) {
            auto transform = child.TransformToVisual(panel).TransformPoint({});
            localProperty.InsertVector2(L"elementPosition", transform);
        });

        //create brush
        revealFocusPanel->m_ellipseCenterExpressionAnimation.SetReferenceParameter(L"localProperty", localProperty);
        RevealBrush revealBrush{ revealFocusPanel->m_compositor };
        revealBrush.StartAnimation(L"EllipseCenter", revealFocusPanel->m_ellipseCenterExpressionAnimation);

        borderShape.StrokeBrush(revealBrush);

        //overlay, the highlight when cursor is inside the control
        revealFocusPanel->m_hostVisualSizeExpressionAnimation.SetReferenceParameter(L"hostVisual", elementVisual);
        overlayGeometry.StartAnimation(L"Size", revealFocusPanel->m_hostVisualSizeExpressionAnimation);
        auto overlayShape = revealFocusPanel->m_compositor.CreateSpriteShape(overlayGeometry);
        overlayShape.FillBrush(revealBrush);
        auto overlayVisual = revealFocusPanel->m_compositor.CreateShapeVisual();
        overlayVisual.Shapes().Append(overlayShape);
        overlayVisual.StartAnimation(L"Size", revealFocusPanel->m_hostVisualSizeExpressionAnimation);
        overlayVisual.Opacity(0.f);

        // Position the overlay at the element's location within the panel
        auto offsetExpression = revealFocusPanel->m_compositor.CreateExpressionAnimation(L"localProperty.elementPosition");
        offsetExpression.SetReferenceParameter(L"localProperty", localProperty);
        overlayVisual.StartAnimation(L"Offset.XY", offsetExpression);
        borderVisual.StartAnimation(L"Offset.XY", offsetExpression);

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
                [revealBrush, revealFocusPanel](auto&&...)
                {
                    revealBrush.StartAnimation(L"EllipseRadius", revealFocusPanel->m_revealBrushRadiusForwardAnimation);
                }     
            }),
            true
        );

        child.AddHandler(
            winrt::Microsoft::UI::Xaml::UIElement::PointerReleasedEvent(),
            winrt::box_value(winrt::Microsoft::UI::Xaml::Input::PointerEventHandler{
                [revealBrush, revealFocusPanel](auto&&...)
                {
                    revealBrush.StartAnimation(L"EllipseRadius", revealFocusPanel->m_revealBrushRadiusBackwardAnimation);
                }
            }),
            true
        );

	}

	void RevealFocusPanel::createResourcesIfNeeded()
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

        // Create overlay container and attach to the overlay canvas (which has ZIndex = -1)
        // This ensures overlays render behind other Grid children
        m_overlayContainer = m_compositor.CreateContainerVisual();
        winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(m_overlayCanvas, m_overlayContainer);

        PointerEntered({ this, &RevealFocusPanel::onUpdateMousePosition });
        PointerMoved({this, &RevealFocusPanel::onUpdateMousePosition});

        PointerExited([this](auto const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args) {
            m_globalPropertySet.InsertVector2(L"MousePosition", InitialMousePosition);
        });

        auto panelVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(*this);
        auto sizeExpression = m_compositor.CreateExpressionAnimation(L"panelVisual.Size");
        sizeExpression.SetReferenceParameter(L"panelVisual", panelVisual);
        m_overlayContainer.StartAnimation(L"Size", sizeExpression);
        m_overlayContainer.Clip(m_compositor.CreateInsetClip());
	}

    void RevealFocusPanel::onUpdateMousePosition(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args)
    {
        m_globalPropertySet.InsertVector2(L"MousePosition", args.GetCurrentPoint(*this).Position());
    }
}
