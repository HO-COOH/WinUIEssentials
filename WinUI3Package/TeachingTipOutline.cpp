#include "pch.h"
#include "TeachingTipOutline.h"

static winrt::Microsoft::UI::Xaml::Media::PathSegment lineTo(winrt::Windows::Foundation::Point point)
{
    winrt::Microsoft::UI::Xaml::Media::LineSegment segment;
    segment.Point(point);
    return segment;
}

static winrt::Microsoft::UI::Xaml::Media::PathSegment arcTo(winrt::Windows::Foundation::Point point, float radius)
{
    if (radius == 0)
        return lineTo(point);

    winrt::Microsoft::UI::Xaml::Media::ArcSegment segment;
    segment.Point(point);
    segment.Size({ radius, radius });
    segment.SweepDirection(winrt::Microsoft::UI::Xaml::Media::SweepDirection::Clockwise);
    return segment;
}

winrt::Microsoft::UI::Xaml::Media::Geometry TeachingTipOutline::CreateGeometry() const
{
    winrt::Microsoft::UI::Xaml::Media::PathGeometry geometry;
    geometry.Figures().Append(createPathFigure());
    return geometry;
}


/*
    3. Draw the TeachingTip's entire outline, see TeachingTipOutline::createPathFigure()
        The outline is one closed figure walked clockwise starting from base[0]
        The part between base[1] -> base[0] is never drawn

                      (6)                             (7)                              (8)
                          .---------------------------->-----------------------------.
                         /                                                            \
                        |                                                              |
                   (5)  ^                                                              v (9)
                        |                                                              |
                         \                                                            /
                     (4)  '-----------<-----------+          +-----------<-----------'  (10)
                                     (3)  base[1]  \        /  base[0]  (11)
                                                    \      /   = StartPoint
                                                (2)  \    / (1)
                                                      \  /
                                                       \/
                                                      apex
            StartPoint          base[0]
            (1) (2)             the tail edges, base[0] -> apex -> base[1]
            (3) (5) (7) (9)     lineTo() the end of the bottom, left, top and right side range
            (4) (6) (8) (10)    arcTo() the start of the left, top, right and bottom side range, with the corner radius - halfStroke
            IsClosed(true)      the start of the bottom side range -> base[0]
*/
std::array<winrt::Microsoft::UI::Xaml::Media::PathSegment, 10> TeachingTipOutline::createPathSegments() const
{
    auto const sideRanges = getSideRanges();
    auto const currentSideIndex = static_cast<int>(tail.side);

    //The i-th side after the tail side when walking clockwise
    auto const i_th_side = [currentSideIndex](int i) { return (currentSideIndex + i) % 4; };

    //The corner leading into the i-th side after the tail side
    auto const cornerTo = [&](int i)
    {
        return arcTo(
            sideRanges[i_th_side(i)].first,
            cornerRadiusAfterSide(static_cast<TeachingTipTailSide>(i_th_side(i - 1)))
        );
    };

    return std::array<winrt::Microsoft::UI::Xaml::Media::PathSegment, 10>
    {
        lineTo(tail.apex),
        lineTo(tail.base[1]),
        lineTo(sideRanges[currentSideIndex].second),
        cornerTo(1), lineTo(sideRanges[i_th_side(1)].second),
        cornerTo(2), lineTo(sideRanges[i_th_side(2)].second),
        cornerTo(3), lineTo(sideRanges[i_th_side(3)].second),
        cornerTo(4)
    };
}

winrt::Microsoft::UI::Xaml::Media::PathFigure TeachingTipOutline::createPathFigure() const
{
    winrt::Microsoft::UI::Xaml::Media::PathFigure figure;
    figure.IsClosed(true);
    figure.StartPoint(tail.base[0]);
    figure.Segments().ReplaceAll(createPathSegments());
    return figure;
}
