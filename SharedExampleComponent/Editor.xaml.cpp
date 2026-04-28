#include "pch.h"
#include "Editor.xaml.h"
#if __has_include("Editor.g.cpp")
#include "Editor.g.cpp"
#endif
#include "CodeSource.h"
#include <winrt/Microsoft.Web.WebView2.Core.h>
#include <winrt/Windows.Data.Json.h>

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::PackageRoot::implementation
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

    std::wstring Editor::getCreateEditorJavascript() const
    {
        return std::format(LR"(window.editor = window.create(document.getElementById('container'), 
    {{
        value: {},
        automaticLayout: true,
        readOnly: true,
        "semanticHighlighting.enabled": true,
        language: '{}',
        theme: 'vs-dark'
    }});
)", winrt::Windows::Data::Json::JsonValue::CreateStringValue(m_code).Stringify(), languageString());
    }

    std::wstring Editor::getSetCodeJavascript() const
    {
        return std::format(
            LR"(if (window.editor) {{ window.editor.setValue({}); }})",
            winrt::Windows::Data::Json::JsonValue::CreateStringValue(m_code).Stringify()
        );
    }

    winrt::fire_and_forget Editor::UpdateEditorCode()
    {
        auto strongThis = get_strong();
        if (m_closed || !m_editorReady)
            co_return;

        try
        {
            auto coreWebView = EditorWebView().CoreWebView2();
            if (!coreWebView)
            {
                co_return;
            }

            co_await coreWebView.ExecuteScriptAsync(getSetCodeJavascript());
            if (!m_closed)
            {
                Height(measureHeight(m_code));
                LoadingProgress().Visibility(winrt::WinUINamespace::UI::Xaml::Visibility::Collapsed);
            }
        }
        catch (...)
        {
        }
    }

    void Editor::Editor_Loaded(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const&)
    {
        m_closed = false;
        if (auto codeSource = DataContext().try_as<winrt::PackageRoot::CodeSource>())
        {
            auto weakThis = get_weak();
            auto codeSourceImpl = winrt::get_self<winrt::PackageRoot::implementation::CodeSource>(codeSource);
            codeSourceImpl->ValueChanged = [weakThis](std::wstring const& value)
            {
                if (auto self = weakThis.get())
                {
                    self->Code(winrt::hstring{ value });
                }
            };

            Code(winrt::hstring{ codeSourceImpl->FormatCode() });
        }
    }

	void Editor::WebView2_Closed(
		winrt::Microsoft::UI::Xaml::Controls::WebView2 const&,
		winrt::Windows::Foundation::IInspectable const&)
	{
		m_closed = true;
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
        sender.NavigationCompleted([weakThis = get_weak()](
            winrt::Microsoft::UI::Xaml::Controls::WebView2 const& sender,
            winrt::Microsoft::Web::WebView2::Core::CoreWebView2NavigationCompletedEventArgs const& args)->winrt::Windows::Foundation::IAsyncAction
        {
                if (auto strongThis = weakThis.get())
                {
                    if (!strongThis->m_closed && !strongThis->m_code.empty())
                    {
                        auto coreWebView = sender.CoreWebView2();
                        co_await coreWebView.ExecuteScriptAsync(strongThis->getCreateEditorJavascript());
                        if (!strongThis->m_closed)
                        {
                            strongThis->m_editorReady = true;
                            strongThis->Height(measureHeight(strongThis->m_code));
                            strongThis->LoadingProgress().Visibility(winrt::WinUINamespace::UI::Xaml::Visibility::Collapsed);
                        }
                    }
                    else if (!strongThis->m_closed)
                    {
                        strongThis->m_editorReady = true;
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
        UpdateEditorCode();
    }

    winrt::PackageRoot::Language Editor::CodeLanguage()
    {
        return m_language;
    }

    void Editor::CodeLanguage(winrt::PackageRoot::Language value)
    {
        m_language = value;
    }

    void Editor::EditorWebView_Unloaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const& e)
    {
        m_closed = true;
        m_editorReady = false;
    }

}
