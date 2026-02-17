#include "pch.h"
#include "Editor.xaml.h"
#if __has_include("Editor.g.cpp")
#include "Editor.g.cpp"
#endif
#include <winrt/Microsoft.Web.WebView2.Core.h>

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{

    double Editor::measureHeight(winrt::hstring const& value)
    {
        return max(10, 20.0 * (std::count(value.begin(), value.end(), L'\n') + 1));
    }

    std::wstring_view Editor::ltrim(std::wstring_view str)
    {
        auto const pos = str.find_first_not_of(L" \t\n\r\f\v");
        str.remove_prefix(min(pos, str.length()));
        return str;
    }

    std::wstring_view Editor::rtrim(std::wstring_view str)
    {
        auto const pos = str.find_last_not_of(L" \t\n\r\f\v");
        str.remove_suffix(min(str.length() - pos - 1, str.length()));
        return str;
    }

    winrt::hstring Editor::stripEmptyLine(winrt::hstring const& value)
    {
        return winrt::hstring{ rtrim(ltrim(value)) };
    }

    std::wstring Editor::getJavascript()
    {
        return std::format(LR"(window.editor = window.create(document.getElementById('container'), 
    {{
        value: String.raw`{}`,
        automaticLayout: true,
        readOnly: true,
        "semanticHighlighting.enabled": true,
        language: '{}',
        theme: 'vs-dark'
    }});
)", m_code.data(), languageString());
    }

	void Editor::WebView2_CoreWebView2Initialized(
		winrt::Microsoft::UI::Xaml::Controls::WebView2 const& sender, 
		winrt::Microsoft::UI::Xaml::Controls::CoreWebView2InitializedEventArgs const& args)
	{
        auto coreWebView = sender.CoreWebView2();
        coreWebView.SetVirtualHostNameToFolderMapping(
            L"local",
            L"",
            winrt::Microsoft::Web::WebView2::Core::CoreWebView2HostResourceAccessKind::Allow
        );
        sender.Source(winrt::Windows::Foundation::Uri{ L"https://local/Monaco.html" });
        sender.NavigationCompleted([weakThis = get_weak(), js = getJavascript()](
            winrt::Microsoft::UI::Xaml::Controls::WebView2 const& sender, 
            winrt::Microsoft::Web::WebView2::Core::CoreWebView2NavigationCompletedEventArgs const& args)->winrt::Windows::Foundation::IAsyncAction
        {
                if (auto strongThis = weakThis.get())
                {
                    if (!strongThis->m_code.empty())
                    {
                        auto coreWebView = sender.CoreWebView2();
                        co_await coreWebView.ExecuteScriptAsync(js);
                        strongThis->Height(measureHeight(strongThis->m_code));
                        strongThis->LoadingProgress().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
                    }
                }
        });
	}

    winrt::hstring Editor::Code()
    {
        return m_code;
    }

    void Editor::Code(winrt::hstring const& value)
    {
        m_code = value;
    }

    winrt::WinUI3Example::Language Editor::CodeLanguage()
    {
        return m_language;
    }

    void Editor::CodeLanguage(winrt::WinUI3Example::Language value)
    {
        m_language = value;
    }
}
