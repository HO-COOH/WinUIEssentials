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

    void FlipWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));

        {
            auto rootVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(RootGrid());
            auto compositor = rootVisual.Compositor();
            //auto rotationAxis = rootVisual.RotationAxis(); //default to (0,0,1), rotation around z axis

            rootVisual.RotationAxis({ 0.0f, 1.0f, 0.0f });
            rootVisual.CenterPoint({ static_cast<float>(RootGrid().ActualWidth()) / 2.0f, static_cast<float>(RootGrid().ActualHeight()) / 2.0f, 0.0f });
            //rootVisual.AnchorPoint({ 0.5f, 0.5f });
            //rootVisual.CenterPoint({ 0,0,0 });

            auto scalarAnimation = compositor.CreateScalarKeyFrameAnimation();
            scalarAnimation.InsertKeyFrame(0.2f, 180.f);
            scalarAnimation.InsertKeyFrame(0.8f, 180.f);
            scalarAnimation.InsertKeyFrame(1.0f, 0.f);
            scalarAnimation.Duration(std::chrono::seconds{ 5 });


            auto scalarAnimation2 = compositor.CreateScalarKeyFrameAnimation();
            scalarAnimation2.InsertKeyFrame(0.0f, -180.f);
            scalarAnimation2.InsertKeyFrame(0.2f, 0.f);
            scalarAnimation2.InsertKeyFrame(0.8f, 0.f);
            scalarAnimation2.InsertKeyFrame(1.0f, -180.f);
            scalarAnimation2.Duration(std::chrono::seconds{ 5 });


            auto backVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(BackGrid());
            backVisual.RotationAxis({ 0.0f, 1.0f, 0.0f });
            backVisual.CenterPoint({ static_cast<float>(RootGrid().ActualWidth()) / 2.0f, static_cast<float>(RootGrid().ActualHeight()) / 2.0f, 0.0f });

            ZIndexAnimation().Begin();
            rootVisual.StartAnimation(L"RotationAngleInDegrees", scalarAnimation);
            backVisual.StartAnimation(L"RotationAngleInDegrees", scalarAnimation2);

            shadowVisual.RotationAxis({ 0.0f, 1.0f, 0.0f });
            shadowVisual.CenterPoint({ static_cast<float>(RootGrid().ActualWidth()) / 2.0f, static_cast<float>(RootGrid().ActualHeight()) / 2.0f, 0.0f });
            shadowVisual.StartAnimation(L"RotationAngleInDegrees", scalarAnimation);
            
        }
        

        //{
        //    auto backVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(BackGrid());
        //    backVisual.RotationAxis({ 0.0f, 1.0f, 0.0f });
        //    backVisual.CenterPoint({ static_cast<float>(RootGrid().ActualWidth()) / 2.0f, static_cast<float>(RootGrid().ActualHeight()) / 2.0f, 0.0f });
        //    auto compositor = backVisual.Compositor();
        //    auto scalarAnimation = compositor.CreateScalarKeyFrameAnimation();
        //    scalarAnimation.InsertKeyFrame(0.0f, -180.f);
        //    scalarAnimation.InsertKeyFrame(1.0f, 0.f);
        //    scalarAnimation.Duration(std::chrono::seconds{ 1 });
        //    backVisual.StartAnimation(L"RotationAngleInDegrees", scalarAnimation);
        //}
    }

    void FlipWindow::RootGrid_Loaded(
        winrt::Windows::Foundation::IInspectable const& sender, 
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto uiElement = sender.as<winrt::Microsoft::UI::Xaml::UIElement>();
        shadowVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(uiElement).as<winrt::Microsoft::UI::Composition::ContainerVisual>();
        auto compositor = shadowVisual.Compositor();
        
        auto transparentVisual = compositor.CreateSpriteVisual();
        auto size = uiElement.ActualSize();
        transparentVisual.Size(size);

        auto shadow = compositor.CreateDropShadow();
        shadow.BlurRadius(ShadowRadius);
        transparentVisual.Shadow(shadow);

        shadowVisual.Children().InsertAtBottom(transparentVisual);
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

