#include "pch.h"
#include "EqualPanel.h"
#if __has_include("EqualPanel.g.cpp")
#include "EqualPanel.g.cpp"
#endif
#include <winrt/Windows.UI.Xaml.Interop.h>

namespace winrt::WinUI3Package::implementation
{
    winrt::Microsoft::UI::Xaml::DependencyProperty EqualPanel::s_horizontalSpacingProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"HorizontalSpacing",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<class_type>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(0.0) }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty EqualPanel::s_verticalSpacingProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"VerticalSpacing",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<class_type>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(0.0) }
    );

    winrt::Microsoft::UI::Xaml::DependencyProperty EqualPanel::s_orientationProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Orientation",
            winrt::xaml_typename<winrt::Microsoft::UI::Xaml::Controls::Orientation>(),
            winrt::xaml_typename<class_type>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                winrt::box_value(winrt::Microsoft::UI::Xaml::Controls::Orientation::Horizontal),
                [](winrt::Microsoft::UI::Xaml::DependencyObject obj, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs args)
                {
                    winrt::get_self<EqualPanel>(obj.as<class_type>())->UpdateLayout();
                }
            }
    );

    EqualPanel::EqualPanel()
    {
        RegisterPropertyChangedCallback(
            winrt::Microsoft::UI::Xaml::FrameworkElement::HorizontalAlignmentProperty(),
            { this, &EqualPanel::onHorizontalAlignmentChanged }
        );
    }

    double EqualPanel::HorizontalSpacing()
    {
        return winrt::unbox_value<double>(GetValue(s_horizontalSpacingProperty));
    }
    void EqualPanel::HorizontalSpacing(double value)
    {
        SetValue(s_horizontalSpacingProperty, winrt::box_value(value));
    }
    double EqualPanel::VerticalSpacing()
    {
        return winrt::unbox_value<double>(GetValue(s_verticalSpacingProperty));
    }
    void EqualPanel::VerticalSpacing(double value)
    {
        SetValue(s_verticalSpacingProperty, winrt::box_value(value));
    }
    winrt::Microsoft::UI::Xaml::Controls::Orientation EqualPanel::Orientation()
    {
        return winrt::unbox_value<winrt::Microsoft::UI::Xaml::Controls::Orientation>(GetValue(s_orientationProperty));
    }
    void EqualPanel::Orientation(winrt::Microsoft::UI::Xaml::Controls::Orientation value)
    {
        SetValue(s_orientationProperty, winrt::box_value(value));
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty EqualPanel::HorizontalSpacingProperty()
    {
        return s_horizontalSpacingProperty;
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty EqualPanel::VerticalSpacingProperty()
    {
        return s_verticalSpacingProperty;
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty EqualPanel::OrientationProperty()
    {
        return s_orientationProperty;
    }
    winrt::Windows::Foundation::Size EqualPanel::MeasureOverride(winrt::Windows::Foundation::Size availableSize)
    {
        m_visibleItemsCount = {};
        m_maxItemHeight = {};
        m_maxItemWidth = {};
        for (auto child : filterVisibleChildren())
        {
            child.Measure(availableSize);
            auto const desiredSize = child.DesiredSize();
            m_maxItemHeight = max(desiredSize.Height, m_maxItemHeight);
            m_maxItemWidth = max(desiredSize.Width, m_maxItemWidth);
            ++m_visibleItemsCount;
        }

        if (m_visibleItemsCount > 0)
        {
            auto const numItemsInterval = m_visibleItemsCount - 1;
            if (Orientation() == winrt::Microsoft::UI::Xaml::Controls::Orientation::Horizontal)
            {
                //horizontal orientation
                if (HorizontalAlignment() != winrt::Microsoft::UI::Xaml::HorizontalAlignment::Stretch || std::isinf(availableSize.Width))
                {
                    return winrt::Windows::Foundation::Size{
                        static_cast<float>(m_maxItemWidth * m_visibleItemsCount + HorizontalSpacing() * numItemsInterval),
                        m_maxItemHeight
                    };
                }
                else
                {
                    m_maxItemWidth = (availableSize.Width - (HorizontalSpacing() * numItemsInterval)) / m_visibleItemsCount;
                    //m_maxItemHeight = (availableSize.Height - (VerticalSpacing() * numItemsInterval) / m_visibleItemsCount);
                    return { availableSize.Width, m_maxItemHeight };
                }
            }
            else
            {
                //vertical orientation
                if (VerticalAlignment() != winrt::Microsoft::UI::Xaml::VerticalAlignment::Stretch || std::isinf(availableSize.Height))
                {
                    return winrt::Windows::Foundation::Size{
                        m_maxItemWidth,
                        static_cast<float>(m_maxItemHeight * m_visibleItemsCount + VerticalSpacing() * numItemsInterval)
                    };
                }
                else
                {
                    //m_maxItemWidth = (availableSize.Width - (HorizontalSpacing() * numItemsInterval)) / m_visibleItemsCount;
                    m_maxItemHeight = (availableSize.Height - (VerticalSpacing() * numItemsInterval) / m_visibleItemsCount);
                    return { m_maxItemWidth, availableSize.Height };
                }
            }
        }
        else
            return {};
    }
    winrt::Windows::Foundation::Size EqualPanel::ArrangeOverride(winrt::Windows::Foundation::Size finalSize)
    {
        if (hasMoreSpaceAvailable(finalSize))
            MeasureOverride(finalSize);

        if (Orientation() == winrt::Microsoft::UI::Xaml::Controls::Orientation::Horizontal)
        {
            float x{};
            for (auto child : filterVisibleChildren())
            {
                child.Arrange(winrt::Windows::Foundation::Rect{
                    x, 0, m_maxItemWidth, m_maxItemHeight
                    });
                x += m_maxItemWidth;
            }
        }
        else
        {
            float y{};
            for (auto child : filterVisibleChildren())
            {
                child.Arrange(winrt::Windows::Foundation::Rect{
                    0, y, m_maxItemWidth, m_maxItemHeight
                    });
                y += m_maxItemHeight;
            }
        }
        return finalSize;
    }
    bool EqualPanel::hasMoreSpaceAvailable(winrt::Windows::Foundation::Size availableSize)
    {
        auto const numItemsInterval = m_visibleItemsCount - 1;
        return availableSize.Width > m_visibleItemsCount * m_maxItemWidth + HorizontalSpacing() * numItemsInterval ||
            availableSize.Height > m_visibleItemsCount * m_maxItemHeight + VerticalSpacing() * numItemsInterval;
    }
    void EqualPanel::onHorizontalAlignmentChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& sender, winrt::Microsoft::UI::Xaml::DependencyProperty const& horizontalAlignmentProperity)
    {
        InvalidateMeasure();
    }
}
