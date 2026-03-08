#include "pch.h"
#include "WindowedContentDialog.h"
#if __has_include("WindowedContentDialog.g.cpp")
#include "WindowedContentDialog.g.cpp"
#endif
#include "VisualTreeHelper.hpp"
#include <winrt/Microsoft.UI.Windowing.h>
#include "HwndHelper.hpp"

namespace winrt::WinUI3Package::implementation
{
    WindowedContentDialog::WindowedContentDialog()
    {
        setContent();
    }

    WindowedContentDialog::WindowedContentDialog(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& dialog) : m_dialog{dialog}
    {
        setContent();
    }

    winrt::Microsoft::UI::Xaml::Controls::ContentDialog WindowedContentDialog::Content()
    {
        return m_dialog;
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult> WindowedContentDialog::ShowAsync()
    {
        co_return co_await ShowAsync(nullptr);
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult> WindowedContentDialog::ShowAsync(winrt::Microsoft::UI::Xaml::Window parentWindow)
    {
        //keep this alive
		auto strongThis = get_strong();

        if (!m_placeholder.IsLoaded())
        {
            winrt::handle loadedEvent{ CreateEventW(nullptr, TRUE, FALSE, nullptr) };
            auto token = m_placeholder.Loaded([hEvent = loadedEvent.get()](auto&&...) { SetEvent(hEvent); });
            co_await winrt::resume_on_signal(loadedEvent.get());
            m_placeholder.Loaded(token);
            co_await wil::resume_foreground(m_window.DispatcherQueue());
        }

        m_dialog.XamlRoot(m_placeholder.XamlRoot());
        m_dialog.UpdateLayout();
      
        auto appWindow = m_window.AppWindow();
        appWindow.ResizeClient(getDesiredWindowSize());

        if (parentWindow)
        {
            auto const parentHwnd = GetHwnd(parentWindow);
            SetWindowLongPtr(GetHwnd(m_window), GWLP_HWNDPARENT, reinterpret_cast<LONG_PTR>(parentHwnd));
            RECT parentRect;
            GetWindowRect(parentHwnd, &parentRect);

            auto const windowSize = appWindow.Size();
            auto const x = parentRect.left + (parentRect.right - parentRect.left - windowSize.Width) / 2;
            auto const y = parentRect.top + (parentRect.bottom - parentRect.top - windowSize.Height) / 2;

            appWindow.Move({ x, y });
        }


        m_window.Activate();
        
        winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult result = winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult::None;
        try
        {
            result = co_await m_dialog.ShowAsync();
        }
        catch (...)
        {
            // If the dialog is canceled or the window is closed externally, ShowAsync might throw.
        }

        m_window.Close();
        co_return result;
    }

    winrt::Windows::Graphics::SizeInt32 WindowedContentDialog::getDesiredWindowSize()
    {
        auto backgroundElement = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::FrameworkElement>(m_dialog, L"BackgroundElement");
        float width = 320.0f;
        float height = 200.0f;
        if (backgroundElement)
        {
            backgroundElement.Measure({ std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity() });
            auto desiredSize = backgroundElement.DesiredSize();
            if (desiredSize.Width > 0 && desiredSize.Height > 0)
            {
                width = desiredSize.Width;
                height = desiredSize.Height;
            }
        }

        width = (std::max)(width, 320.0f);
        height = (std::max)(height, 200.0f);

        auto const scale = m_placeholder.XamlRoot().RasterizationScale();
        return 
        {
             static_cast<int32_t>(width * scale),
             static_cast<int32_t>(height * scale)
		};
    }

    void WindowedContentDialog::setContent()
    {
        static bool resourceAdded = [] {
            winrt::Microsoft::UI::Xaml::ResourceDictionary resources;
            resources.Source(winrt::Windows::Foundation::Uri{ L"ms-appx:///WinUI3Package/WindowedContentDialog_Resource.xaml" });
			winrt::Microsoft::UI::Xaml::Application::Current().Resources().MergedDictionaries().Append(resources);
            return true;
        }();
		m_dialog.Style(winrt::Microsoft::UI::Xaml::Application::Current().Resources().Lookup(winrt::box_value(L"WindowedContentDialogStyle")).as<winrt::Microsoft::UI::Xaml::Style>());
        m_placeholder.Children().ReplaceAll({ winrt::WinUI3Package::WindowCaptionButtonThemeWorkaround{m_window}, m_dialog });
        m_window.SystemBackdrop(winrt::Microsoft::UI::Xaml::Media::DesktopAcrylicBackdrop{});
        m_window.Content(m_placeholder);
        m_window.ExtendsContentIntoTitleBar(true);
    }
}
