#include "pch.h"
#include "FlipWindow.xaml.h"
#if __has_include("FlipWindow.g.cpp")
#include "FlipWindow.g.cpp"
#endif
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include "FakeTitleBar.h"
using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    FlipWindow::FlipWindow()
    {
        auto const dpi = GetDpiForWindow(GetHwnd(*this));
        AppWindow().ResizeClient({ 
            ScaleForDpi<int>(c_WindowWidth, dpi), 
            ScaleForDpi<int>(c_WindowHeight, dpi) 
        });
        InitializeComponent();
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
    }

    void FlipWindow::addShadows()
    {
        auto frontShadowContainerVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(ShadowGrid());
        auto compositor = frontShadowContainerVisual.Compositor();

        m_frontShadow = compositor.CreateSpriteVisual();
        auto sizeExpression = compositor.CreateExpressionAnimation(L"host.Size");
        sizeExpression.SetReferenceParameter(L"host", frontShadowContainerVisual);
        m_frontShadow.StartAnimation(L"Size", sizeExpression);

        auto shadow = compositor.CreateDropShadow();
        shadow.BlurRadius(ShadowRadius);
        m_frontShadow.Shadow(shadow);
        winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(ShadowGrid(), m_frontShadow);
    
        auto backShadowContainerVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(BackShadowGrid());
        m_backShadow = compositor.CreateSpriteVisual();
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

        auto compositor = m_frontVisual.Compositor();
        m_frontVisual.RotationAxis({ 0.0f, 1.0f, 0.0f });
        m_backVisual.RotationAxis({ 0.0f, 1.0f, 0.0f });

        rotationAnimation = compositor.CreateScalarKeyFrameAnimation();
        rotationAnimation.Target(L"RotationAngleInDegrees");
        rotationAnimation.InsertExpressionKeyFrame(1.f, L"this.FinalValue");
        rotationAnimation.Duration(std::chrono::milliseconds{ static_cast<int64_t>(m_animationDurationMilli) });
         
        auto implicitAnimations = compositor.CreateImplicitAnimationCollection();
        implicitAnimations.Insert(L"RotationAngleInDegrees", rotationAnimation);
        m_backVisual.RotationAngleInDegrees(-180.f);
        m_backShadow.RotationAngleInDegrees(-180.f);

        m_frontVisual.ImplicitAnimations(implicitAnimations);
        m_backVisual.ImplicitAnimations(implicitAnimations);

        auto frontVisualOpacityAnimation = compositor.CreateExpressionAnimation(L"this.Target.RotationAngleInDegrees >= 90 ? 0 : 1");
        auto backVisualOpacityAnimation = compositor.CreateExpressionAnimation(L"this.Target.RotationAngleInDegrees >= -90 ? 1 : 0");
        m_frontVisual.StartAnimation(L"Opacity", frontVisualOpacityAnimation);
        m_backVisual.StartAnimation(L"Opacity", backVisualOpacityAnimation);

        auto centerPointAnimation = compositor.CreateExpressionAnimation(L"Vector3(this.Target.Size.X / 2, this.Target.Size.Y / 2, 0.0f)");
        m_frontVisual.StartAnimation(L"CenterPoint", centerPointAnimation);
        m_backVisual.StartAnimation(L"CenterPoint", centerPointAnimation);
        
        auto shadowRotationExpression = compositor.CreateExpressionAnimation(L"host.RotationAngleInDegrees");
        if (m_frontShadow)
        {
            m_frontShadow.RotationAxis({ 0.0f, 1.0f, 0.0f });
            m_frontShadow.ImplicitAnimations(implicitAnimations);
            m_frontShadow.StartAnimation(L"CenterPoint", centerPointAnimation);
            m_frontShadow.StartAnimation(L"Opacity", frontVisualOpacityAnimation);
            shadowRotationExpression.SetReferenceParameter(L"host", m_frontVisual);
            m_frontShadow.StartAnimation(L"RotationAngleInDegrees", shadowRotationExpression);
        }
        if (m_backShadow)
        {
            m_backShadow.RotationAxis({ 0.0f, 1.0f, 0.0f });
            m_backShadow.ImplicitAnimations(implicitAnimations);
            m_backShadow.StartAnimation(L"CenterPoint", centerPointAnimation);
            m_backShadow.StartAnimation(L"Opacity", backVisualOpacityAnimation);
            shadowRotationExpression.SetReferenceParameter(L"host", m_backVisual);
            m_backShadow.StartAnimation(L"RotationAngleInDegrees", shadowRotationExpression);
        }
    }

    void FlipWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
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
}
