#include "pch.h"
#include "TeachingTipAcrylicStyle.h"
#include <algorithm>
#include <cmath>
#include "TeachingTipTailSide.hpp"
#include "BindingHelper.h"
#include "GridHelper.hpp"

class BindingWrapper : public winrt::Microsoft::UI::Xaml::Data::Binding
{
public:
    BindingWrapper(wchar_t const* property, winrt::Windows::Foundation::IInspectable const& source)
    {
        Path(winrt::Microsoft::UI::Xaml::PropertyPath{ property });
        Source(source);
    }
};

/*
    0. Original:
        This is the runtime tree structure of a TeachingTip:
            Grid (unamed) -> It seems to have exactly the same area as the entire TailOcclusionGrid
                TailOcclusionGrid:      This include the tail area and the the content inside the TeachingTip, with a big padding surrounding it (likely used for shadow)
                    ContentRootGrid:    This include the rounded rectangular body (including the visible border), no padding
                    TailPolygon:        This is the tail triangle (which is actually a rectangle but with an offset into the body area)

        For a TeachingTip pointing downwards, the detail of the polygon and the body is like this:

                   +------------------+              TailPolygon's "real" top edge, which is inside the body
                    \                /
       --------------+--------------+--------------- the body's bottom edge
                      \            /
                       \          /
                        \        /
                         \      /
                          \    /
                           \  /
                            \/
                          target

    1. Add the acrylic:
        What draws what in TailOcclusionGrid, from bottom to top:
            ContentRootGrid         the body acrylic is inserted as its first child, its border is set -> transparent
            TailPolygon             Opacity set to -> 0, only read for where the tail is
            tailCanvas              the tail acrylic, a square rotated by 45 degrees and clipped
                tailAcrylicVisual
            outlineCanvas           one Path for the border of both the body and the tail, without a line between them
                outlinePath

        An AcrylicVisual can only be a rectangle, so the tail acrylic is a rotated square with its upper half clipped off.

                                ^
                               / \
                              /   \                   clipped
                             /     \
                            /       \
              _____________<_________>_____________ <- cut along the body's bottom edge
                            \       /
                             \     /
                              \   /
                               \ /                  <- AcrylicVisual, rotated
                                v

*/
TargetedTeachingTipAcrylicStyle::TargetedTeachingTipAcrylicStyle(
    winrt::Microsoft::UI::Xaml::Controls::TeachingTip const& teachingTip,
    winrt::Microsoft::UI::Xaml::Controls::Grid const& tailOcclusionGrid,
    winrt::Microsoft::UI::Xaml::Controls::Grid const& contentRootGrid,
    winrt::Microsoft::UI::Xaml::Shapes::Polygon const& tailPolygon
) : m_tailOcclusionGrid{ tailOcclusionGrid }, m_contentRootGrid{ contentRootGrid }, m_tailPolygon{ tailPolygon }
{
    contentRootGrid.BorderBrush(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush{ winrt::Windows::UI::Colors::Transparent() });
    tailPolygon.Opacity(0);//Opacity instead of Fill and Stroke, because the LightDismiss visual state will set TailPolygon.Fill

    winrt::Microsoft::UI::Xaml::Shapes::Path outline;
    outline.SetBinding(winrt::Microsoft::UI::Xaml::Shapes::Shape::StrokeProperty(), BindingWrapper{ L"BorderBrush", teachingTip });//stroke="{Binding BorderBrush, ElementName=teachingTip}" / stroke="{x:Bind teachingTip.BorderBrush}"
    outline.IsHitTestVisible(false);

    winrt::Microsoft::UI::Xaml::Controls::Canvas outlineCanvas;
    outlineCanvas.IsHitTestVisible(false);
    outlineCanvas.Children().Append(outline);
    GridHelper::SpanGrid(outlineCanvas, tailOcclusionGrid);

    auto tailAcrylicVisual = makeRotatedTailAcrylicVisual();
    tailAcrylicVisual.RequestedTheme(teachingTip.ActualTheme());
    if (auto parent = teachingTip.Parent().try_as<winrt::Microsoft::UI::Xaml::FrameworkElement>())
        BindingHelper::BindTheme(tailAcrylicVisual, parent);

    winrt::Microsoft::UI::Xaml::Controls::Canvas tailCanvas;
    tailCanvas.IsHitTestVisible(false);
    GridHelper::SpanGrid(tailCanvas, tailOcclusionGrid);
    tailCanvas.Children().Append(tailAcrylicVisual);

    auto tailOcclusionGridChild = tailOcclusionGrid.Children();
    tailOcclusionGridChild.Append(tailCanvas);
    tailOcclusionGridChild.Append(outlineCanvas);

    m_tailCanvas = tailCanvas;
    m_tailAcrylicVisual = tailAcrylicVisual;
    m_outlinePath = outline;

    onLayoutChanged();
    tailOcclusionGrid.LayoutUpdated([*this](auto&&...) mutable
    {
        onLayoutChanged();
    });
}


/*
    4. Why the square is bigger than the tail
        The symbols, all of them are labeled in the diagrams below:
            A                   the apex, also the square's bottom corner
            B                   the y of the outline on the tail side, the center line of the bottom border, see (2)
            base[0], base[1]    where the tail edges cross y = B, see (2)
            h                   A.y - B, the height of the tail
            L                   |base - A| = sqrt(2) * h, the length of a tail edge, also the side of a square of the tail's size
            r                   how far above y = B the square's side corners are
            size                the side of the square, Width and Height of the AcrylicVisual
            C                   the center of the square
            bodyAcrylic.Bottom  where the body acrylic stops, ContentRootGrid's bottom - BorderThickness.Bottom
            band                from bodyAcrylic.Bottom down to y = B, (BorderThickness.Bottom - strokeThickness / 2)
            antialiasingMargin  1 pixel, how far the clip goes into the body acrylic to hide its soft edge, see (7)
            clip top            bodyAcrylic.Bottom - antialiasingMargin, band + antialiasingMargin above y = B

        The square's bottom corner is A and its lower sides lie on the tail edges,
        so its side corners are on the tail edges continued past base[1] and base[0], r above y = B:

                                    ^
                                   / \
                                  /   \
                                 /     \ size
                                /       \
                               /         \
                  side corner <     C     > ................+
                               \         / sqrt(2) * r      | r
            --------------------+-------+-------------------+ y = B
                        base[1]  \     /  base[0]           |
                                  \   / L                   | h
                                   \ /                      |
                                    v A ....................+

            size = L + sqrt(2) * r      a tail edge, continued by sqrt(2) * r for r more height
            C    = (A.x, B - r)         the middle of the 2 side corners

        Outside the opening the band is under the outline's stroke. In the opening the outline is skipped, so only the tail acrylic can cover it,
        up to the clip top. Past a side corner the upper side turns back inwards by 1 pixel per pixel of height,
        so the square covers the full width of the opening up to 2r above y = B.
        
        Zoomed in at base[0], with a 1 pixel border and the smallest r:

                                             x = base[0].x
                                     the opening   :  outside the opening
               +...+...............................+........................ clip top
               |   |                               :\
               |   |  antialiasingMargin           : \
            2r |   |                               :  > .......+............ side corner
               |   +_______________________________:_/_________|____________ bodyAcrylic.Bottom
               |   |  band                         :/          | r
               +---+-------------------------------+===========+============ y = B, the outline is only drawn outside the opening
                                                  /  base[0]
                                 the tail edge   /

            2r >= band + antialiasingMargin
        With a 1 pixel border the band is 0.5 pixel, so the smallest square is r = 0.75 and size = L + sqrt(2)*r = L + 1.414*0.75 = L + 1.06.

        We use a square with size = 2L because:
            - it covers the full width up to 2h above y = B, so it works for any border with band + antialiasingMargin <= 2h
            - its center C = (A.x, B - h), which is simply the apex mirrored by the base

    5. resizeAndTranslateTailAcrylic, the 2L square
        This is 4. with r = h. The dotted lines are the upper sides of the L square (r = 0), its lower sides are the tail edges shared with the 2L square.

                                        ^  C - (0, 2h)
                                       / \
                                      /   \
                                     /     \
                                    /       \ size
                                   /         \
                                  /           \
                                 /             \
                   C - (2h, 0)  <       C       > C + (2h, 0) ........+
                                 \     . .     /                      |
                                  \   .   .   /                       | h
                                   \ .     . /                        |
            ------------------------+-------+-------------------------+ y = B
                          base[1]    \     /   base[0]                |
                                      \   / L                         | h
                                       \ /                            |
                                        v A = C + (0, 2h) ............+

            size = L + sqrt(2) * h = 2L
            C    = (A.x, B - h) = base[0] + base[1] - A     the apex mirrored by the base
        The half diagonal is size / sqrt(2) = 2h, so the corners are C -/+ (2h, 0) and C -/+ (0, 2h), the bottom one is (A.x, B + h) = A,
        and the lower sides pass through base[1] and base[0] at their middle. Below y = B the square is exactly the tail.

    6. Placing it
        The AcrylicVisual stays at (0, 0) of tailCanvas. CompositeTransform rotates it around RenderTransformOrigin (0.5, 0.5) first,
        then translates its center from (size / 2, size / 2) to C:

              (0, 0) of tailCanvas                                      ^
              +-----------+                                            / \
              |           |    Rotation = 45 around the center        /   \
              |     +     |    ------------------------------->      <  C  >
              |           |    then Translate = C - size / 2          \   /
              +-----------+                                            \ /
              <--  size -->                                             v

            TranslateX = C.x - size / 2
            TranslateY = C.y - size / 2
        (Note: the 0,0 point of tailCanvas is THE top-left corner of the entire TeachingTip because we span it to the entire TailOcclusionGrid, 
        and all coordinates here are measured with that original point)
        
        The position is set by the transform, because Canvas.Left/Top would be layout rounded by up to half a pixel in x and y,
        which moves the lower sides by up to 0.71 pixel, more than the half stroke.
        The size is still layout rounded, by e of up to half a physical pixel. The rotation is around the rounded center but Translate takes the unrounded size / 2,
        so the lower sides move by at most 1.21 * |e|, 0.6 pixel at 100% scale and 0.48 at 125%.
        That is about the half stroke, and what is left over is within the acrylic's soft edge, so UseLayoutRounding is left on.

    7. Clipping it
        tailCanvas.Clip keeps the tail and the band, and removes the upper half that would cover the content. The dots are what is left:

              body acrylic       +.................+                    clip top    = bodyAcrylic.Bottom - 1
              ___________________|.................|___________________ bodyAcrylic.Bottom
              -------------------|-+.............+-|------------------- y = B, the outline
                                 |  \.........../  |
                                 |   \........./   |
                                 |    \......./    |
                                 |     \...../     |
                                 |      \.../      |
                                 |       \./       |
                                 |        v A      |
                                 +-----------------+                    clip bottom = A.y + 1
                          base[1].x - 1      base[0].x + 1

            left   = min(A.x, base[0].x, base[1].x) - 1 = base[1].x - 1
            right  = max(A.x, base[0].x, base[1].x) + 1 = base[0].x + 1
            top    = bodyAcrylic.Bottom - 1             overlaps the body acrylic to hide its soft edge,
                                                        both acrylics sample what is behind the window, not each other
            bottom = A.y + 1
        The 1 pixel margins on the left, right and bottom keep the antialiased edges of the tail.
*/
void TargetedTeachingTipAcrylicStyle::resizeAndTranslateTailAcrylic(TeachingTipOutline const& outline, winrt::Windows::Foundation::Rect const& bodyAcrylic)
{
    auto tailCanvas = m_tailCanvas.get();
    auto tailAcrylicVisual = m_tailAcrylicVisual.get();
    if (!tailCanvas || !tailAcrylicVisual)
        return;

    auto const size = 2 * std::hypot(outline.tail.base[0].X - outline.tail.apex.X, outline.tail.base[0].Y - outline.tail.apex.Y);
    tailAcrylicVisual.Width(size);
    tailAcrylicVisual.Height(size);

    //The apex mirrored by the tail base
    winrt::Windows::Foundation::Point const center
    { 
        outline.tail.base[0].X + outline.tail.base[1].X - outline.tail.apex.X, 
        outline.tail.base[0].Y + outline.tail.base[1].Y - outline.tail.apex.Y 
    };

    //Canvas.Left/Top are layout rounded and can put the square up to half a pixel off the outline, use transform here
    auto transform = tailAcrylicVisual.RenderTransform().as<winrt::Microsoft::UI::Xaml::Media::CompositeTransform>();
    transform.TranslateX(center.X - size / 2);
    transform.TranslateY(center.Y - size / 2);


    winrt::Microsoft::UI::Xaml::Media::RectangleGeometry clipGeometry;
    clipGeometry.Rect(outline.CreateClip());
    tailCanvas.Clip(clipGeometry);
}

winrt::WinUI3Package::AcrylicVisual TargetedTeachingTipAcrylicStyle::makeRotatedTailAcrylicVisual()
{
    winrt::WinUI3Package::AcrylicVisual tailAcrylicVisual;
    tailAcrylicVisual.IsHitTestVisible(false);

    winrt::Microsoft::UI::Xaml::Media::CompositeTransform tailTransform;
    tailTransform.Rotation(45);
    tailAcrylicVisual.RenderTransform(tailTransform);
    tailAcrylicVisual.RenderTransformOrigin({ 0.5f, 0.5f });

    return tailAcrylicVisual;
}

constexpr static auto insetCornerRadius(winrt::Microsoft::UI::Xaml::CornerRadius cornerRadius, float halfStroke)
{
    auto insetRadius = [halfStroke](double radius) { return (std::max)(0.0, radius - halfStroke); };
    return winrt::Microsoft::UI::Xaml::CornerRadius
    {
        insetRadius(cornerRadius.TopLeft),
        insetRadius(cornerRadius.TopRight),
        insetRadius(cornerRadius.BottomRight),
        insetRadius(cornerRadius.BottomLeft)
    };
}

constexpr static auto insetRect(winrt::Windows::Foundation::Rect rect, float halfStroke)
{
    return winrt::Windows::Foundation::Rect
    {
        rect.X + halfStroke, //X
        rect.Y + halfStroke, //Y
        (std::max)(0.f, rect.Width - 2 * halfStroke), //Width
        (std::max)(0.f, rect.Height - 2 * halfStroke) //Height
    };
}

constexpr static auto insetRect(winrt::Windows::Foundation::Rect rect, winrt::Microsoft::UI::Xaml::Thickness borderThickness)
{
    return winrt::Windows::Foundation::Rect
    {
        rect.X + static_cast<float>(borderThickness.Left),
        rect.Y + static_cast<float>(borderThickness.Top),
        (std::max)(0.f, rect.Width - static_cast<float>(borderThickness.Left + borderThickness.Right)),
        (std::max)(0.f, rect.Height - static_cast<float>(borderThickness.Top + borderThickness.Bottom))
    };
}

void TargetedTeachingTipAcrylicStyle::onLayoutChanged()
{
    //LayoutUpdated is raised for layout passes anywhere in the app, including when the TeachingTip is closed
    auto tailOcclusionGrid = m_tailOcclusionGrid.get();
    if (!tailOcclusionGrid || !tailOcclusionGrid.IsLoaded())
        return;

    auto tailPolygon = m_tailPolygon.get();
    auto contentRootGrid = m_contentRootGrid.get();
    if (!tailPolygon || !contentRootGrid)
        return;

    auto const width = static_cast<float>(contentRootGrid.ActualWidth());
    auto const height = static_cast<float>(contentRootGrid.ActualHeight());
    if (width <= 0 || height <= 0)
        return;

    //The border on the tail side can be 0, take the thickest one
    auto const borderThickness = contentRootGrid.BorderThickness();
    float const strokeThickness = (std::max)({ borderThickness.Left, borderThickness.Top, borderThickness.Right, borderThickness.Bottom, tailPolygon.StrokeThickness() });

    //A stroke is centered on its geometry, inset the outline by half of it so the stroke covers exactly where ContentRootGrid's border was
    auto const halfStroke = strokeThickness / 2.f;
    auto const bodyRect = contentRootGrid.TransformToVisual(tailOcclusionGrid).TransformBounds({ 0.f, 0.f, width, height });
    auto const bodyOutline = insetRect(bodyRect, halfStroke);
    compareAndSetOutlinePath(TeachingTipOutline
    {
        .body = bodyOutline,
        .cornerRadius = insetCornerRadius(contentRootGrid.CornerRadius(), halfStroke),
        .tail = TeachingTipTail{ tailPolygon, tailOcclusionGrid, bodyOutline },
        .strokeThickness = strokeThickness,
        .bodyAcrylic = insetRect(bodyRect, borderThickness)
    });
}

void TargetedTeachingTipAcrylicStyle::compareAndSetOutlinePath(TeachingTipOutline&& outline)
{
    if (m_lastOutline == outline)
        return;
    m_lastOutline = outline;

    auto outlinePath = m_outlinePath.get();

    outlinePath.StrokeThickness(outline.strokeThickness);
    outlinePath.Data(outline.CreateGeometry());
    resizeAndTranslateTailAcrylic(outline, outline.bodyAcrylic);
}
