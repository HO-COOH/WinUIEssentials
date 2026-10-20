#include "pch.h"
#include "TeachingTipTail.h"
#include <algorithm>
#include <iterator>
#include <limits>

static std::array<winrt::Windows::Foundation::Point, 3> transformedTailpolygonPoints(
    winrt::Microsoft::UI::Xaml::Shapes::Polygon const& tailPolygon,
    winrt::Microsoft::UI::Xaml::UIElement const& relativeTo
)
{
    auto points = tailPolygon.Points();
    auto transform = tailPolygon.TransformToVisual(relativeTo);

    return std::array<winrt::Windows::Foundation::Point, 3>
    {
        transform.TransformPoint(points.GetAt(0)),
        transform.TransformPoint(points.GetAt(1)),
        transform.TransformPoint(points.GetAt(2)),
    };
}

/*
    2. TeachingTipTail::TeachingTipTail, where the tail is
        B is the body outline, the center line of the bottom border: ContentRootGrid's bottom - strokeThickness / 2.
        The apex A is the point of TailPolygon that sticks out of the body outline the furthest, and the side it sticks out of is the tail side.
        The other 2 points P are inside the body (the 1 pixel offset above), so they slide along the tail edges P -> A up to y = B:

                          P = "0,0" +------------------+ "20,0" = P     P, the other 2 points of TailPolygon, t = 1
                                     \                /
                ----------------------+--------------+---------------   y = B, the body outline, the base is between A and P, 0 < t < 1
                              base[1]  \            / base[0]   |
                                        \          /            |
                                         \        /             |
                                          \      /              h       h = A.y - B
                                           \    /               |
                                            \  /                |
                                             \/ ________________|       A = "10,10", the apex, t = 0
                                             A

            t    = (B - A.y) / (P.y - A.y)
            base = A + (P - A) * t, then clamped into the body's width
        The tail edges are at 45 degrees, so the opening is 2h wide. The base is ordered clockwise, which is right to left on the bottom side:
            base[0] = (A.x + h, B)
            base[1] = (A.x - h, B)
*/
void TeachingTipTail::findApexAndSideFromTriangle(
    std::array<winrt::Windows::Foundation::Point, 3> triangle,
    D2D1_RECT_F bodyOutline
)
{
    auto const [left, top, right, bottom] = bodyOutline;

    //The apex is the corner that sticks out of the body the furthest
    float maxDistance = -std::numeric_limits<float>::infinity();
    for (auto i = 0; i < 3; ++i)
    {
        auto corner = triangle[i];
        //How far the corner sticks out of each side, ordered the same as TeachingTipTailSide
        float const distances[]
        {
            top - corner.Y,     //Top
            corner.X - right,   //Right
            corner.Y - bottom,  //Bottom
            left - corner.X     //Left
        };
        auto const furthest = std::max_element(std::begin(distances), std::end(distances));
        if (*furthest > maxDistance)
        {
            maxDistance = *furthest;
            side = static_cast<TeachingTipTailSide>(std::distance(std::begin(distances), furthest));
            apex = corner;
            base[0] = triangle[(i + 1) % 3];
            base[1] = triangle[(i + 2) % 3];
        }
    }
}

void TeachingTipTail::alignBaseToBodyOutline(D2D1_RECT_F bodyOutline)
{
    auto const [left, top, right, bottom] = bodyOutline;

    //TailPolygon overlaps into the body, slide its base corners along the tail edges onto the body outline
    auto const isHorizontal = isIntersectHorizontal();
    auto const sideLine = getSideLine(bodyOutline);
    for (auto& point : base)
    {
        auto const apexToSide = isHorizontal ? sideLine - apex.Y : sideLine - apex.X;
        auto const apexToPoint = isHorizontal ? point.Y - apex.Y : point.X - apex.X;
        auto const t = apexToSide / apexToPoint;
        point = { apex.X + (point.X - apex.X) * t, apex.Y + (point.Y - apex.Y) * t };
        if (isHorizontal)
            point = { std::clamp(point.X, left, right), sideLine };
        else
            point = { sideLine, std::clamp(point.Y, top, bottom) };
    }
}

TeachingTipTail::TeachingTipTail(
    winrt::Microsoft::UI::Xaml::Shapes::Polygon const& tailPolygon,
    winrt::Microsoft::UI::Xaml::UIElement const& relativeTo,
    winrt::Windows::Foundation::Rect bodyOutline
)
{
    D2D1_RECT_F const bodyOutlineEdges
    {
        bodyOutline.X,
        bodyOutline.Y,
        bodyOutline.X + bodyOutline.Width,
        bodyOutline.Y + bodyOutline.Height
    };

    findApexAndSideFromTriangle(transformedTailpolygonPoints(tailPolygon, relativeTo), bodyOutlineEdges);
    alignBaseToBodyOutline(bodyOutlineEdges);

    //Order the base corners clockwise, the same direction TeachingTipOutline::CreateGeometry walks the body
    if (!isClockwise())
        std::swap(base[0], base[1]);
}
