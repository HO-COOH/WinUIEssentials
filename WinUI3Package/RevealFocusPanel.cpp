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

    static void bindToCornerRadiusPropertyImpl(
        auto const& element, 
        auto const& property, 
        auto halfStroke, 
        auto const& borderGeometry, 
        auto const& overlayGeometry
    )
    {
        element.RegisterPropertyChangedCallback(
            property,
            [halfStroke, borderGeometry, overlayGeometry](winrt::Microsoft::UI::Xaml::DependencyObject const& obj, winrt::Microsoft::UI::Xaml::DependencyProperty const& property)
            {
                auto const cornerRadius = winrt::unbox_value<winrt::Microsoft::UI::Xaml::CornerRadius>(obj.GetValue(property));
                float const adjustedRadius = (std::max)(0.0f, static_cast<float>(cornerRadius.TopLeft) - halfStroke);
                borderGeometry.CornerRadius({ adjustedRadius, adjustedRadius });
                overlayGeometry.CornerRadius({ static_cast<float>(cornerRadius.TopLeft), static_cast<float>(cornerRadius.TopLeft) });
            }
        );
    }

    //return a CornerRadius for convenience
    static auto bindToCornerRadiusProperty(
        winrt::Microsoft::UI::Xaml::FrameworkElement const& element,
        auto halfStroke,
        auto const& borderGeometry,
        auto const& overlayGeometry)
    {
        winrt::Microsoft::UI::Xaml::CornerRadius cornerRadius{ -1 };
        if (auto control = element.try_as<winrt::Microsoft::UI::Xaml::Controls::Control>())
        {
            cornerRadius = control.CornerRadius();
            bindToCornerRadiusPropertyImpl(
                control,
                winrt::Microsoft::UI::Xaml::Controls::Control::CornerRadiusProperty(),
                halfStroke,
                borderGeometry,
                overlayGeometry
            );
        }
        else if (auto contentPresenter = element.try_as<winrt::Microsoft::UI::Xaml::Controls::ContentPresenter>())
        {
            cornerRadius = contentPresenter.CornerRadius();
            bindToCornerRadiusPropertyImpl(
                contentPresenter,
                winrt::Microsoft::UI::Xaml::Controls::ContentPresenter::CornerRadiusProperty(),
                halfStroke,
                borderGeometry,
                overlayGeometry
            );
        }
        else if (auto grid = element.try_as<winrt::Microsoft::UI::Xaml::Controls::Grid>())
        {
            cornerRadius = grid.CornerRadius();
            bindToCornerRadiusPropertyImpl(
                grid,
                winrt::Microsoft::UI::Xaml::Controls::Grid::CornerRadiusProperty(),
                halfStroke,
                borderGeometry,
                overlayGeometry
            );
        }
        return cornerRadius;
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
        auto child = d.as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
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
        auto const cornerRadius = bindToCornerRadiusProperty(
            child,
            halfStroke,
            borderGeometry,
            overlayGeometry
		);
        if (cornerRadius.TopLeft != -1)
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


        child.LayoutUpdated([localProperty, child, panel](auto&&...) {
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

        child.PointerEntered([overlayVisual, revealFocusPanel](auto&& sender, auto&&...) {
            if (sender.as<winrt::Microsoft::UI::Xaml::FrameworkElement>().Visibility() == winrt::Microsoft::UI::Xaml::Visibility::Visible)
                overlayVisual.StartAnimation(L"Opacity", revealFocusPanel->m_opacityForwardAnimation);
        });
        child.PointerExited([overlayVisual, revealFocusPanel](auto&& sender, auto&&...) {
            if (sender.as<winrt::Microsoft::UI::Xaml::FrameworkElement>().Visibility() == winrt::Microsoft::UI::Xaml::Visibility::Visible)
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

	void RevealFocusPanel::createResourcesIfNeeded()
	{
        if (m_globalPropertySet)
            return;

        m_globalPropertySet = m_compositor.CreatePropertySet();
        m_globalPropertySet.InsertVector2(L"MousePosition", InitialMousePosition);

        m_opacityForwardAnimation = m_compositor.CreateScalarKeyFrameAnimation();
        m_opacityForwardAnimation.InsertKeyFrame(1.f, 0.4f);

        m_opacityBackwardAnimation = m_compositor.CreateScalarKeyFrameAnimation();
        m_opacityBackwardAnimation.InsertKeyFrame(1.f, 0.f);

        m_revealBrushRadiusForwardAnimation = m_compositor.CreateVector2KeyFrameAnimation();
        m_revealBrushRadiusForwardAnimation.InsertKeyFrame(1.f, RevealBrush::NormalRevealRadius * 3);
        m_revealBrushRadiusForwardAnimation.Duration(std::chrono::seconds{ 3 });

        m_revealBrushRadiusBackwardAnimation = m_compositor.CreateVector2KeyFrameAnimation();
        m_revealBrushRadiusBackwardAnimation.InsertKeyFrame(1.f, RevealBrush::NormalRevealRadius);

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
        auto panelVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(*this);
        auto sizeExpression = m_compositor.CreateExpressionAnimation(L"panelVisual.Size");
        sizeExpression.SetReferenceParameter(L"panelVisual", panelVisual);
        m_overlayContainer.StartAnimation(L"Size", sizeExpression);
        m_overlayContainer.Clip(m_compositor.CreateInsetClip());
        
        winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(m_overlayCanvas, m_overlayContainer);

        PointerEntered({ this, &RevealFocusPanel::onUpdateMousePosition });
        PointerMoved({this, &RevealFocusPanel::onUpdateMousePosition});

        PointerExited([this](auto const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args) {
            m_globalPropertySet.InsertVector2(L"MousePosition", InitialMousePosition);
        });
	}

    void RevealFocusPanel::onUpdateMousePosition(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args)
    {
        m_globalPropertySet.InsertVector2(L"MousePosition", args.GetCurrentPoint(*this).Position());
    }
}
