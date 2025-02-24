#include "pch.h"
#include "Editor.h"
#if __has_include("Editor.g.cpp")
#include "Editor.g.cpp"
#endif
#include <winrt/Microsoft.Web.WebView2.Core.h>

namespace winrt::WinUI3Example::implementation
{
	Editor::Editor()
	{
        DefaultBackgroundColor(winrt::Windows::UI::Colors::Transparent());
        Loaded([this](auto&&...){ loadHtml(); });
	}

	Editor::Editor(winrt::hstring const& code, winrt::WinUI3Example::Language language) : m_code{ code }, m_language{ language }
    {
        DefaultBackgroundColor(winrt::Windows::UI::Colors::Transparent());
        Loaded([this](auto&&...) { loadHtml(); });
    }

    winrt::hstring Editor::Code()
    {
        return m_code;
    }

    void Editor::Code(winrt::hstring const& value)
    {
        if (m_coreWebView)
        {
            m_coreWebView.ExecuteScriptAsync(L"editor.setValue(String.raw`" + stripEmptyLine(value) + L"`)");
            Height(measureHeight(value));
            return;
		}

		m_code = stripEmptyLine(value);
    }

    winrt::fire_and_forget Editor::loadHtml()
    {
        co_await consume_Microsoft_UI_Xaml_Controls_IWebView2::EnsureCoreWebView2Async();
        auto coreWebView = CoreWebView2();
        //We don't assign it to the member yet, because we need to wait until the navigation finished 
        // then we can assign it, so that our code setter can safely call `editor.setValue`, 
        // although this is very unlikely
        coreWebView.SetVirtualHostNameToFolderMapping(
            L"local",
            L"",
            winrt::Microsoft::Web::WebView2::Core::CoreWebView2HostResourceAccessKind::Allow
        );
        Source(winrt::Windows::Foundation::Uri{ L"https://local/Monaco.html" });
		NavigationCompleted([this](auto&&...)
		{
            m_coreWebView = CoreWebView2();
            if (!m_code.empty())
            {
                createEditor();
                Height(measureHeight(m_code));
            }
		});
    }

    void Editor::createEditor()
    {
        auto js = std::format(LR"(window.editor = window.create(document.getElementById('container'), 
    {{
        value: String.raw`{}`,
        automaticLayout: true,
        readOnly: true,
        "semanticHighlighting.enabled": true,
        language: '{}',
        theme: 'vs-dark'
    }});
)", m_code.data(), languageString());
        m_coreWebView.ExecuteScriptAsync(js);
    }

    double Editor::measureHeight(winrt::hstring const& value)
    {
        return max(10, 20.0 * (std::count(value.begin(), value.end(), L'\n') + 1));
    }

    std::wstring_view Editor::ltrim(std::wstring_view str)
    {
        const auto pos(str.find_first_not_of(L" \t\n\r\f\v"));
        str.remove_prefix(min(pos, str.length()));
        return str;
    }

    std::wstring_view Editor::rtrim(std::wstring_view str)
    {
        const auto pos(str.find_last_not_of(L" \t\n\r\f\v"));
        str.remove_suffix(min(str.length() - pos - 1, str.length()));
        return str;
    }

    winrt::hstring Editor::stripEmptyLine(winrt::hstring const& value)
    {
        return winrt::hstring{ rtrim(ltrim(value)) };
    }


    wchar_t const* Editor::languageString() const
    {
        switch (m_language)
        {
        case winrt::WinUI3Example::Language::Xaml:
            return L"xml";
        case winrt::WinUI3Example::Language::Cpp:
        case winrt::WinUI3Example::Language::H:
            return L"cpp";
        case winrt::WinUI3Example::Language::Idl:
            return L"idl";
        default:
            return L"";
        }
    }
}
