#include "pch.h"
#include "ControlExample.xaml.h"
#if __has_include("ControlExample.g.cpp")
#include "ControlExample.g.cpp"
#endif
#include "CodeSource.h"
#include <winrt/Microsoft.Web.WebView2.Core.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.
namespace Impl
{
	Editor::Editor(
		winrt::hstring const& code, 
		winrt::WinUI3Example::Language language, 
		winrt::Microsoft::UI::Xaml::Controls::ProgressBar const& progressBar,
		winrt::WinUI3Example::CodeSource const& codeSource
	) : 
		m_code{ code }, 
		m_language{ language },
		m_progressBarRef{ winrt::make_weak(progressBar) },
		m_codeRef{winrt::make_weak(codeSource)}
	{
		DefaultBackgroundColor(winrt::Windows::UI::Colors::Transparent());
	}

	void Editor::Load()
	{
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
		auto sharedThis = shared_from_this();
		co_await EnsureCoreWebView2Async();
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
		m_navigationCompletedRevoker = NavigationCompleted(winrt::auto_revoke, [weakThis = weak_from_this()](auto&&...)
			{
				if (auto strongThis = weakThis.lock())
				{
					strongThis->m_coreWebView = strongThis->CoreWebView2();
					if (!strongThis->m_code.empty())
					{
						strongThis->createEditor();
						strongThis->Height(measureHeight(strongThis->m_code));
					}
					if (auto progressBar = strongThis->m_progressBarRef.get())
						progressBar.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
					if (auto code = strongThis->m_codeRef.get())
					{
						auto codeImpl = winrt::get_self<winrt::WinUI3Example::implementation::CodeSource>(code);
						strongThis->Code(winrt::hstring{ codeImpl->FormatCode() });
						codeImpl->ValueChanged = [weakThis](std::wstring const& code) {
							if(auto strongThis = weakThis.lock())
								strongThis->Code(winrt::hstring{ code });
							};
					}
					strongThis->Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
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

namespace winrt::WinUI3Example::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty ControlExample::m_headerTextProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"HeaderText",
			winrt::xaml_typename<winrt::hstring>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlExample::m_exampleProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Example",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlExample::m_optionsProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Options",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlExample::m_outputProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Output",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlExample::m_xamlProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Xaml",
			winrt::xaml_typename<winrt::WinUI3Example::CodeSource>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr, &ControlExample::onXamlChanged }
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlExample::m_idlProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Idl",
			winrt::xaml_typename<winrt::WinUI3Example::CodeSource>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr, &ControlExample::onIdlChanged }
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlExample::m_cppProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Cpp",
			winrt::xaml_typename<winrt::WinUI3Example::CodeSource>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr, &ControlExample::onCppChanged }
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlExample::m_headerProperty = 
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Header",
			winrt::xaml_typename<winrt::WinUI3Example::CodeSource>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr, &ControlExample::onHeaderChanged }
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlExample::m_substitutionsProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Substitutions",
			winrt::xaml_typename<winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Example::ControlExampleSubstitution>>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);

	ControlExample::ControlExample()
	{
		Substitutions(winrt::single_threaded_vector<winrt::WinUI3Example::ControlExampleSubstitution>());
	}

	winrt::hstring ControlExample::HeaderText()
	{
		//return winrt::unbox_value_or<winrt::hstring>(GetValue(m_headerTextProperty), L"");
		return winrt::unbox_value<winrt::hstring>(GetValue(m_headerTextProperty));
	}

	void ControlExample::HeaderText(winrt::hstring const& value)
	{
		SetValue(m_headerTextProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlExample::HeaderTextProperty()
	{
		return m_headerTextProperty;
	}

	winrt::Windows::Foundation::IInspectable ControlExample::Example()
	{
		return GetValue(m_exampleProperty);
	}

	void ControlExample::Example(winrt::Windows::Foundation::IInspectable const& value)
	{
		SetValue(m_exampleProperty, value);
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlExample::ExampleProperty()
	{
		return m_exampleProperty;
	}

	winrt::Windows::Foundation::IInspectable ControlExample::Options()
	{
		return winrt::unbox_value<winrt::Windows::Foundation::IInspectable>(GetValue(m_optionsProperty));
	}

	void ControlExample::Options(winrt::Windows::Foundation::IInspectable const& value)
	{
		SetValue(m_optionsProperty, value);
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlExample::OptionsProperty()
	{
		return m_optionsProperty;
	}

	winrt::Windows::Foundation::IInspectable ControlExample::Output()
	{
		return winrt::unbox_value<winrt::Windows::Foundation::IInspectable>(GetValue(m_outputProperty));
	}

	void ControlExample::Output(winrt::Windows::Foundation::IInspectable const& value)
	{
		SetValue(m_outputProperty, value);
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlExample::OutputProperty()
	{
		return m_outputProperty;
	}

	winrt::WinUI3Example::CodeSource ControlExample::Xaml()
	{
		return winrt::unbox_value<winrt::WinUI3Example::CodeSource>(GetValue(m_xamlProperty));
	}

	void ControlExample::Xaml(winrt::WinUI3Example::CodeSource const& value)
	{
		SetValue(m_xamlProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlExample::XamlProperty()
	{
		return m_xamlProperty;
	}

	winrt::WinUI3Example::CodeSource ControlExample::Idl()
	{
		return winrt::unbox_value<winrt::WinUI3Example::CodeSource>(GetValue(m_idlProperty));
	}

	void ControlExample::Idl(winrt::WinUI3Example::CodeSource const& value)
	{
		SetValue(m_idlProperty, value);
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlExample::IdlProperty()
	{
		return m_idlProperty;
	}

	winrt::WinUI3Example::CodeSource ControlExample::Header()
	{
		return winrt::unbox_value<winrt::WinUI3Example::CodeSource>(GetValue(m_headerProperty));
	}

	void ControlExample::Header(winrt::WinUI3Example::CodeSource const& value)
	{
		SetValue(m_headerProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlExample::HeaderProperty()
	{
		return m_headerProperty;
	}

	winrt::WinUI3Example::CodeSource ControlExample::Cpp()
	{
		return winrt::unbox_value<winrt::WinUI3Example::CodeSource>(GetValue(m_cppProperty));
	}

	void ControlExample::Cpp(winrt::WinUI3Example::CodeSource const& value)
	{
		SetValue(m_cppProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlExample::CppProperty()
	{
		return m_cppProperty;
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Example::ControlExampleSubstitution> ControlExample::Substitutions()
	{
		return winrt::unbox_value<winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Example::ControlExampleSubstitution>>(GetValue(m_substitutionsProperty));
	}

	void ControlExample::Substitutions(winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Example::ControlExampleSubstitution> const& value)
	{
		SetValue(m_substitutionsProperty, value);
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlExample::SubstitutionsProperty()
	{
		return m_substitutionsProperty;
	}

	std::shared_ptr<Impl::Editor> ControlExample::makePivotItem(winrt::WinUI3Example::CodeSource const& code, winrt::WinUI3Example::Language language)
	{
		winrt::Microsoft::UI::Xaml::Controls::Grid grid;

		winrt::Microsoft::UI::Xaml::Controls::ProgressBar loadingProgressBar;
		loadingProgressBar.IsIndeterminate(true);
		loadingProgressBar.Width(200);

		auto codeImpl = winrt::get_self<CodeSource>(code);
		auto editor = std::make_shared<Impl::Editor>(codeImpl->Code(), language, loadingProgressBar, code);
		editor->Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);

		grid.Children().ReplaceAll({ *editor, loadingProgressBar });

		//codeImpl->ValueChanged = [editorRef = winrt::make_weak(editor)](std::wstring const& code) {
		//	editorRef.get().Code(winrt::hstring{ code });
		//};

		winrt::Microsoft::UI::Xaml::Controls::PivotItem item;
		item.Header(winrt::box_value(languageHeader(language)));
		item.Content(grid);
		CodePivot().Items().Append(item);

		return editor;
	}

	void ControlExample::onXamlChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& d, 
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto self = getSelf(d);
		if (self->m_xamlEditor)
		{
			//change code
		}
		else
			(self->m_xamlEditor = self->makePivotItem(self->Xaml(), winrt::WinUI3Example::Language::Xaml))->Load();
	}

	void ControlExample::onIdlChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto self = getSelf(d);
		if (self->m_idlEditor)
		{
			//change code
		}
		else
			(self->m_idlEditor = self->makePivotItem(self->Idl(), winrt::WinUI3Example::Language::Idl))->Load();
	}

	void ControlExample::onHeaderChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& d, 
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto self = getSelf(d);
		if (self->m_headerEditor)
		{
			//change code
		}
		else
			(self->m_headerEditor = self->makePivotItem(self->Header(), winrt::WinUI3Example::Language::H))->Load();
	}

	void ControlExample::onCppChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& d, 
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto self = getSelf(d);
		if (self->m_cppEditor)
		{
			//change code
		}
		else
			(self->m_cppEditor = self->makePivotItem(self->Cpp(), winrt::WinUI3Example::Language::Cpp))->Load();
	}

	void ControlExample::onSubstitutionsChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& d,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
	}

	ControlExample* ControlExample::getSelf(winrt::Microsoft::UI::Xaml::DependencyObject const& d)
	{
		return winrt::get_self<ControlExample>(d.as<class_type>());
	}

	winrt::hstring ControlExample::UnboxString(winrt::Windows::Foundation::IInspectable const& value) 
	{ 
		return winrt::unbox_value_or(value, L""); 
	}

	winrt::hstring ControlExample::BooleanToString(bool value)
	{
		return value ? L"True" : L"False";
	}

	void ControlExample::Expander_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		sender.as<winrt::Microsoft::UI::Xaml::Controls::Expander>().IsExpanded(false);
	}

}
