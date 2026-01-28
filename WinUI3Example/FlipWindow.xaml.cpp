#include "pch.h"
#include "FlipWindow.xaml.h"
#if __has_include("FlipWindow.g.cpp")
#include "FlipWindow.g.cpp"
#endif
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>

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
    }

    void FlipWindow::createCompositionObjects()
    {
        m_frontVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(RootGrid());
        m_backVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(BackGrid());

        auto compositor = m_frontVisual.Compositor();
        m_frontVisual.RotationAxis({ 0.0f, 1.0f, 0.0f });
        m_backVisual.RotationAxis({ 0.0f, 1.0f, 0.0f });

        //0 -> 180 -> 0
        m_frontVisualRotationAnimation = compositor.CreateScalarKeyFrameAnimation();
        m_frontVisualRotationAnimation.InsertKeyFrame(0.2f, 180.f);
        m_frontVisualRotationAnimation.InsertKeyFrame(0.8f, 180.f);
        m_frontVisualRotationAnimation.InsertKeyFrame(1.0f, 0.f);
        m_frontVisualRotationAnimation.Duration(std::chrono::seconds{ 5 });

        //-180 -> 0 -> 180
        m_backVisualRotationAnimation = compositor.CreateScalarKeyFrameAnimation();
        m_backVisualRotationAnimation.InsertKeyFrame(0.0f, -180.f);
        m_backVisualRotationAnimation.InsertKeyFrame(0.2f, 0.f);
        m_backVisualRotationAnimation.InsertKeyFrame(0.8f, 0.f);
        m_backVisualRotationAnimation.InsertKeyFrame(1.0f, -180.f);
        m_backVisualRotationAnimation.Duration(std::chrono::seconds{ 5 });

        m_frontVisualOpacityAnimation = compositor.CreateExpressionAnimation(L"this.Target.RotationAngleInDegrees >= 90 ? 0 : 1");
        m_backVisualOpacityAnimation = compositor.CreateExpressionAnimation(L"this.Target.RotationAngleInDegrees >= -90 ? 1 : 0");

        m_centerPointAnimation = compositor.CreateExpressionAnimation(L"Vector3(this.Target.Size.X / 2, this.Target.Size.Y, 0.0f)");

        m_shadowVisual.RotationAxis({ 0.0f, 1.0f, 0.0f });
    }

    void FlipWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));

        if (!m_frontVisual)
            createCompositionObjects();


        ZIndexAnimation().Begin();
        m_frontVisual.StartAnimation(L"RotationAngleInDegrees", m_frontVisualRotationAnimation);
        m_frontVisual.StartAnimation(L"Opacity", m_frontVisualOpacityAnimation);
        m_frontVisual.StartAnimation(L"CenterPoint", m_centerPointAnimation);
        m_backVisual.StartAnimation(L"RotationAngleInDegrees", m_backVisualRotationAnimation);
        m_backVisual.StartAnimation(L"Opacity", m_backVisualOpacityAnimation);
        m_backVisual.StartAnimation(L"CenterPoint", m_centerPointAnimation);

        m_shadowVisual.StartAnimation(L"RotationAngleInDegrees", m_frontVisualRotationAnimation);
        m_shadowVisual.StartAnimation(L"Opacity", m_frontVisualOpacityAnimation);
        m_shadowVisual.StartAnimation(L"CenterPoint", m_centerPointAnimation);
    }

    void FlipWindow::RootGrid_Loaded(
        winrt::Windows::Foundation::IInspectable const& sender, 
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto uiElement = sender.as<winrt::Microsoft::UI::Xaml::UIElement>();
        m_shadowVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(uiElement).as<winrt::Microsoft::UI::Composition::ContainerVisual>();
        auto compositor = m_shadowVisual.Compositor();
        
        auto transparentVisual = compositor.CreateSpriteVisual();
        auto size = uiElement.ActualSize();
        transparentVisual.Size(size);

        auto shadow = compositor.CreateDropShadow();
        shadow.BlurRadius(ShadowRadius);
        transparentVisual.Shadow(shadow);

        m_shadowVisual.Children().InsertAtBottom(transparentVisual);
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

}

