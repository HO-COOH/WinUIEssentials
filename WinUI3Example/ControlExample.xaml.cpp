#include "pch.h"
#include "ControlExample.xaml.h"
#if __has_include("ControlExample.g.cpp")
#include "ControlExample.g.cpp"
#endif
#include "CodeSource.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

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

	winrt::WinUI3Example::Editor ControlExample::makePivotItem(winrt::WinUI3Example::CodeSource const& code, winrt::WinUI3Example::Language language)
	{
		winrt::Microsoft::UI::Xaml::Controls::Grid grid;
		auto child = grid.Children();

		auto codeImpl = winrt::get_self<CodeSource>(code);
		winrt::WinUI3Example::Editor editor{ codeImpl->Code(), language};
		editor.Code(codeImpl->Code());
		editor.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);

		winrt::Microsoft::UI::Xaml::Controls::ProgressBar loadingProgressBar;
		loadingProgressBar.IsIndeterminate(true);
		loadingProgressBar.Width(200);

		child.Append(editor);
		child.Append(loadingProgressBar);

		editor.NavigationCompleted([loadingProgressBar, editorRef = winrt::make_weak(editor)](auto&&...)
		{
			loadingProgressBar.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
			editorRef.get().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			editorRef.get().Height(500);
		});
		codeImpl->ValueChanged = [editorRef = winrt::make_weak(editor)](std::wstring const& code) {
			editorRef.get().Code(code);
		};

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
			self->m_xamlEditor = self->makePivotItem(self->Xaml(), winrt::WinUI3Example::Language::Xaml);
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
			self->m_headerEditor = self->makePivotItem(self->Header(), winrt::WinUI3Example::Language::H);
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
			self->m_cppEditor = self->makePivotItem(self->Cpp(), winrt::WinUI3Example::Language::Cpp);
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
}


void winrt::WinUI3Example::implementation::ControlExample::Expander_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	sender.as<winrt::Microsoft::UI::Xaml::Controls::Expander>().IsExpanded(false);
}
