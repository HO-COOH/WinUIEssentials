#include "pch.h"
#include "FlipWindow.xaml.h"
#if __has_include("FlipWindow.g.cpp")
#include "FlipWindow.g.cpp"
#endif
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include "FakeTitleBar.h"
#include <HwndHelper.hpp>

template<typename T>
T ScaleForDpi(auto value, UINT dpi)
{
    return value * dpi / 96.0;
}
// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    void FlipWindow::addWindowShowAnimation()
    {
        constexpr static std::chrono::milliseconds duration{ 500 };
        auto visual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(RootCanvas());
        m_compositor = visual.Compositor();

        auto opacityAnimation = m_compositor.CreateScalarKeyFrameAnimation();
        opacityAnimation.InsertKeyFrame(0.f, 0.f);
        opacityAnimation.InsertKeyFrame(1.f, 1.f);
        opacityAnimation.Duration(duration);
        opacityAnimation.Target(L"Opacity");

        auto scaleAnimation = m_compositor.CreateVector2KeyFrameAnimation();
        scaleAnimation.InsertKeyFrame(0.f, { 0.8f, 0.8f });
        scaleAnimation.InsertKeyFrame(1.f, { 1.f, 1.f });
        scaleAnimation.Target(L"Scale.XY");
        scaleAnimation.Duration(duration);

        visual.StartAnimation(L"CenterPoint", m_compositor.CreateExpressionAnimation(CenterPointExpression));

        auto slideUpAnimation = m_compositor.CreateVector2KeyFrameAnimation();
        slideUpAnimation.InsertKeyFrame(0.f, { 0, 200.f });
        slideUpAnimation.InsertKeyFrame(1.f, { 0.f, 0.f });
        slideUpAnimation.Target(L"Translation.XY");
        slideUpAnimation.Duration(duration);

        auto slideRotationAnimation = m_compositor.CreateScalarKeyFrameAnimation();
        slideRotationAnimation.InsertKeyFrame(0.f, 60.f);
        slideRotationAnimation.InsertKeyFrame(1.f, 0);
        slideRotationAnimation.Target(L"RotationAngleInDegrees");
        slideRotationAnimation.Duration(duration);
        visual.RotationAxis(winrt::Windows::Foundation::Numerics::float3{ 1.f, 0.f, 0.f });

        auto group = m_compositor.CreateAnimationGroup();
        group.Add(opacityAnimation);
        group.Add(scaleAnimation);
        group.Add(slideUpAnimation);
        group.Add(slideRotationAnimation);
        winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetIsTranslationEnabled(RootCanvas(), true);
        winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetImplicitShowAnimation(RootCanvas(), group);
    }

    void FlipWindow::addWindowCloseAnimation()
    {
        constexpr static std::chrono::milliseconds duration{ 300 };
        auto visual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(RootCanvas());
        m_compositor = visual.Compositor();

        auto opacityAnimation = m_compositor.CreateScalarKeyFrameAnimation();
        opacityAnimation.InsertKeyFrame(0.f, 1.f);
        opacityAnimation.InsertKeyFrame(1.f, 0.f);
        opacityAnimation.Duration(duration);
        opacityAnimation.Target(L"Opacity");

        auto scaleAnimation = m_compositor.CreateVector2KeyFrameAnimation();
        scaleAnimation.InsertKeyFrame(0.f, { 1.f, 1.f });
        scaleAnimation.InsertKeyFrame(1.f, { 0.8f, 0.8f });

        scaleAnimation.Target(L"Scale.XY");
        scaleAnimation.Duration(duration);

        auto group = m_compositor.CreateAnimationGroup();
        group.Add(opacityAnimation);
        group.Add(scaleAnimation);
        winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetImplicitHideAnimation(RootCanvas(), group);
    }

    FlipWindow::FlipWindow()
    {
        auto const dpi = GetDpiForWindow(GetHwnd(*this));
        AppWindow().ResizeClient({ 
            ScaleForDpi<int>(c_WindowWidth, dpi), 
            ScaleForDpi<int>(c_WindowHeight, dpi) 
        });
        InitializeComponent();

        addWindowShowAnimation();
        addWindowCloseAnimation();
        
        winrt::get_self<winrt::WinUI3Example::implementation::FakeTitleBar>(FakeTitleBar())->ParentWindow = this;
        addShadows();
        winrt::Microsoft::UI::Input::InputNonClientPointerSource::GetForWindowId(AppWindow().Id())
            .SetRegionRects(
                winrt::Microsoft::UI::Input::NonClientRegionKind::Caption, 
                {
                    winrt::Windows::Graphics::RectInt32
                    {
                        .X = 0,
                        .Y = 0,
                        .Width = ScaleForDpi<int>(c_WindowWidth - 150, dpi),
                        .Height = ScaleForDpi<int>(50, dpi)
                    }
                }
            );
        
        m_windowClosedToken = Closed([this](auto&&, winrt::Microsoft::UI::Xaml::WindowEventArgs const& args)->winrt::fire_and_forget 
        {
            auto strongThis = get_strong();
            args.Handled(true);
            Closed(m_windowClosedToken);
            RootCanvas().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
            co_await winrt::resume_after(std::chrono::milliseconds(350));
            co_await wil::resume_foreground(strongThis->DispatcherQueue());
            strongThis->Close();
        });
    }

    void FlipWindow::addShadows()
    {
        auto frontShadowContainerVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(ShadowGrid());

        m_frontShadow = m_compositor.CreateSpriteVisual();
        auto sizeExpression = m_compositor.CreateExpressionAnimation(L"host.Size");
        sizeExpression.SetReferenceParameter(L"host", frontShadowContainerVisual);
        m_frontShadow.StartAnimation(L"Size", sizeExpression);

        auto shadow = m_compositor.CreateDropShadow();
        shadow.BlurRadius(ShadowRadius);
        m_frontShadow.Shadow(shadow);
        winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(ShadowGrid(), m_frontShadow);
    
        auto backShadowContainerVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(BackShadowGrid());
        m_backShadow = m_compositor.CreateSpriteVisual();
        sizeExpression.SetReferenceParameter(L"host", backShadowContainerVisual);
        m_backShadow.StartAnimation(L"Size", sizeExpression);
        m_backShadow.Shadow(shadow);
        m_backShadow.Opacity(0);
        winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(BackShadowGrid(), m_backShadow);
    }

    void FlipWindow::createCompositionObjects()
    {
        m_frontVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(RootGrid());
        m_backVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(BackGrid());

        m_frontVisual.RotationAxis(m_rotationAxis);
        m_backVisual.RotationAxis(m_rotationAxis);

        rotationAnimation = m_compositor.CreateScalarKeyFrameAnimation();
        rotationAnimation.Target(L"RotationAngleInDegrees");
        rotationAnimation.InsertExpressionKeyFrame(1.f, L"this.FinalValue");
        rotationAnimation.Duration(std::chrono::milliseconds{ static_cast<int64_t>(m_animationDurationMilli) });
         
        auto implicitAnimations = m_compositor.CreateImplicitAnimationCollection();
        implicitAnimations.Insert(L"RotationAngleInDegrees", rotationAnimation);
        m_backVisual.RotationAngleInDegrees(-180.f);
        m_backShadow.RotationAngleInDegrees(-180.f);

        m_frontVisual.ImplicitAnimations(implicitAnimations);
        m_backVisual.ImplicitAnimations(implicitAnimations);

        auto frontVisualOpacityAnimation = m_compositor.CreateExpressionAnimation(L"this.Target.RotationAngleInDegrees >= 90 ? 0 : 1");
        auto backVisualOpacityAnimation = m_compositor.CreateExpressionAnimation(L"this.Target.RotationAngleInDegrees >= -90 ? 1 : 0");
        m_frontVisual.StartAnimation(L"Opacity", frontVisualOpacityAnimation);
        m_backVisual.StartAnimation(L"Opacity", backVisualOpacityAnimation);

        auto centerPointAnimation = m_compositor.CreateExpressionAnimation(CenterPointExpression);
        m_frontVisual.StartAnimation(L"CenterPoint", centerPointAnimation);
        m_backVisual.StartAnimation(L"CenterPoint", centerPointAnimation);
        
        auto shadowRotationExpression = m_compositor.CreateExpressionAnimation(L"host.RotationAngleInDegrees");
        if (m_frontShadow)
        {
            m_frontShadow.RotationAxis(m_rotationAxis);
            m_frontShadow.ImplicitAnimations(implicitAnimations);
            m_frontShadow.StartAnimation(L"CenterPoint", centerPointAnimation);
            m_frontShadow.StartAnimation(L"Opacity", frontVisualOpacityAnimation);
            shadowRotationExpression.SetReferenceParameter(L"host", m_frontVisual);
            m_frontShadow.StartAnimation(L"RotationAngleInDegrees", shadowRotationExpression);
        }
        if (m_backShadow)
        {
            m_backShadow.RotationAxis(m_rotationAxis);
            m_backShadow.ImplicitAnimations(implicitAnimations);
            m_backShadow.StartAnimation(L"CenterPoint", centerPointAnimation);
            m_backShadow.StartAnimation(L"Opacity", backVisualOpacityAnimation);
            shadowRotationExpression.SetReferenceParameter(L"host", m_backVisual);
            m_backShadow.StartAnimation(L"RotationAngleInDegrees", shadowRotationExpression);
        }
    }

    void FlipWindow::myButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        if (!m_frontVisual)
            createCompositionObjects();

        m_frontVisual.RotationAngleInDegrees(180.f);
        m_backVisual.RotationAngleInDegrees(0.f);
        ZIndexForwardAnimation().Begin();
    }

    void FlipWindow::GoBackButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        m_frontVisual.RotationAngleInDegrees(0.f);
        m_backVisual.RotationAngleInDegrees(-180.f);
        ZIndexBackwardAnimation().Begin();
    }

    double FlipWindow::ContentWidth()
    {
        return c_WindowWidth - 2 * ShadowRadius;
    }

    double FlipWindow::ContentHeight()
    {
        return c_WindowHeight - 2 * ShadowRadius;
    }

    double FlipWindow::WindowWidth()
    {
        return c_WindowWidth;
    }

    double FlipWindow::WindowHeight()
    {
        return c_WindowHeight;
    }

    void FlipWindow::AnimationDuration(double value)
    {
        if (m_animationDurationMilli == value)
            return;

        m_animationDurationMilli = value;
        if (rotationAnimation)
            rotationAnimation.Duration(std::chrono::milliseconds{ static_cast<int64_t>(m_animationDurationMilli) });
    }

    void FlipWindow::RadioButtons_SelectionChanged(
        winrt::Windows::Foundation::IInspectable const& sender, 
        winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
    {
        switch (sender.as<winrt::Microsoft::UI::Xaml::Controls::RadioButtons>().SelectedIndex())
        {
            case 0:
                m_rotationAxis = winrt::Windows::Foundation::Numerics::float3{ 1.f, 0.f, 0.f };
                break;
            case 1:
                m_rotationAxis = winrt::Windows::Foundation::Numerics::float3{ 0.f, 1.f, 0.f };
                break;
            case 2:
                m_rotationAxis = winrt::Windows::Foundation::Numerics::float3{ 0.f, 0.f, 1.f };
                break;
        }

        if (m_frontVisual)
        {
            m_frontVisual.RotationAxis(m_rotationAxis);
            m_backVisual.RotationAxis(m_rotationAxis);
        }
        if (m_frontShadow)
            m_frontShadow.RotationAxis(m_rotationAxis);
        if (m_backShadow)
            m_backShadow.RotationAxis(m_rotationAxis);
    }

}
