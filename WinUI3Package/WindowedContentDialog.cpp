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

    void WindowedContentDialog::Content(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& value)
    {
        m_dialog = value;
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

        m_dialog.Style(winrt::Microsoft::UI::Xaml::Application::Current().Resources().Lookup(winrt::box_value(L"WindowedContentDialogStyle")).as<winrt::Microsoft::UI::Xaml::Style>());
        m_placeholder.Children().ReplaceAll({ winrt::WinUI3Package::WindowCaptionButtonThemeWorkaround{m_window}, m_dialog });

        m_dialog.XamlRoot(m_placeholder.XamlRoot());
        m_dialog.UpdateLayout();
      
        auto appWindow = m_window.AppWindow();
        appWindow.ResizeClient(getDesiredWindowSize());

        if (parentWindow)
            centerAndResizeWindow(appWindow, parentWindow);

        appWindow.Presenter().as<winrt::Microsoft::UI::Windowing::OverlappedPresenter>().IsModal(true);
        
        //This will NOT leak
        appWindow.Closing([strongThis = get_strong()](auto&&, auto&& args)
        {
            if (strongThis->m_isClosingByCode)
                return;

            args.Cancel(true);
            strongThis->m_dialog.Hide();
        });
        appWindow.Show();

        winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult result = winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult::None;
        try
        {
            result = co_await m_dialog.ShowAsync();
        }
        catch (...)
        {
            // If the dialog is canceled or the window is closed externally, ShowAsync might throw.
        }

        m_isClosingByCode = true;
        m_window.Close();
        m_isClosingByCode = false;
        if (parentWindow)
            parentWindow.Activate();
        co_return result;
    }

    winrt::Windows::Graphics::SizeInt32 WindowedContentDialog::getDesiredWindowSize()
    {
        auto backgroundElement = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::FrameworkElement>(m_dialog, L"BackgroundElement");
        auto commandSpace = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Grid>(m_dialog, L"CommandSpace");
        auto primaryButton = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Button>(m_dialog, L"PrimaryButton");
        auto secondaryButton = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Button>(m_dialog, L"SecondaryButton");
        auto closeButton = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Button>(m_dialog, L"CloseButton");
        float width = 320.0f;
        float height = 200.0f;
        auto const availableSize = winrt::Windows::Foundation::Size{
            std::numeric_limits<float>::infinity(),
            std::numeric_limits<float>::infinity()
        };
        if (backgroundElement)
        {
            backgroundElement.Measure(availableSize);
            auto desiredSize = backgroundElement.DesiredSize();
            if (desiredSize.Width > 0 && desiredSize.Height > 0)
            {
                width = desiredSize.Width;
                height = desiredSize.Height;
            }
        }

        if (commandSpace)
        {
            int buttonCount = 0;
            double longestButtonWidth = 0.0;

            auto measureButton = [&buttonCount, &longestButtonWidth, availableSize](winrt::Microsoft::UI::Xaml::Controls::Button const& button, winrt::hstring const& text)
            {
                if (!button || text.empty())
                {
                    return;
                }

                button.Measure(availableSize);
                longestButtonWidth = (std::max)(longestButtonWidth, static_cast<double>(button.DesiredSize().Width));
                ++buttonCount;
            };

            measureButton(primaryButton, m_dialog.PrimaryButtonText());
            measureButton(secondaryButton, m_dialog.SecondaryButtonText());
            measureButton(closeButton, m_dialog.CloseButtonText());

            if (buttonCount > 0)
            {
                auto const resources = winrt::Microsoft::UI::Xaml::Application::Current().Resources();
                auto const buttonMaxWidth = winrt::unbox_value<double>(resources.Lookup(winrt::box_value(L"ContentDialogButtonMaxWidth")));
                auto const buttonSpacing = buttonCount > 1
                    ? winrt::unbox_value<winrt::Microsoft::UI::Xaml::GridLength>(resources.Lookup(winrt::box_value(L"ContentDialogButtonSpacing"))).Value
                    : 0.0;
                auto const padding = commandSpace.Padding();
                auto const commandWidth = padding.Left + padding.Right + buttonCount * (std::min)(longestButtonWidth, buttonMaxWidth) + (buttonCount - 1) * buttonSpacing;
                width = static_cast<float>((std::max)(static_cast<double>(width), commandWidth));
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

        m_window.SystemBackdrop(winrt::Microsoft::UI::Xaml::Media::DesktopAcrylicBackdrop{});
        m_window.Content(m_placeholder);
        m_window.ExtendsContentIntoTitleBar(true);
    }

    void WindowedContentDialog::centerAndResizeWindow(winrt::Microsoft::UI::Windowing::AppWindow const& appWindow, winrt::Microsoft::UI::Xaml::Window const& parentWindow)
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
}
