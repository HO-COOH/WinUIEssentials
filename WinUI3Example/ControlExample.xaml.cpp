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

	void ControlExample::makePivotItem(winrt::WinUI3Example::CodeSource const& code, winrt::WinUI3Example::Language language)
	{
		auto codeImpl = winrt::get_self<CodeSource>(code);
		codeImpl->m_codeLanguage = language;
		m_codeItems.Append(code);
	}

	void ControlExample::onXamlChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto self = getSelf(d);
		self->makePivotItem(self->Xaml(), winrt::WinUI3Example::Language::Xaml);
	}

	void ControlExample::onIdlChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto self = getSelf(d);
		self->makePivotItem(self->Idl(), winrt::WinUI3Example::Language::Idl);
	}

	void ControlExample::onHeaderChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto self = getSelf(d);
		self->makePivotItem(self->Header(), winrt::WinUI3Example::Language::H);
	}

	void ControlExample::onCppChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto self = getSelf(d);
		self->makePivotItem(self->Cpp(), winrt::WinUI3Example::Language::Cpp);
	}

	void ControlExample::onSubstitutionsChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& d,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
	}

	winrt::Microsoft::UI::Xaml::Controls::PathIcon ControlExample::languageHeader(winrt::WinUI3Example::Language language)
	{
		winrt::hstring str;
		switch (language)
		{
			case winrt::WinUI3Example::Language::Xaml: str = winrt::unbox_value<winrt::hstring>(Resources().Lookup(winrt::box_value(L"XamlIcon"))); break;
			case winrt::WinUI3Example::Language::Cpp: str = winrt::unbox_value<winrt::hstring>(Resources().Lookup(winrt::box_value(L"CppIcon"))); break;
			case winrt::WinUI3Example::Language::H: str = winrt::unbox_value<winrt::hstring>(Resources().Lookup(winrt::box_value(L"HIcon"))); break;
			case winrt::WinUI3Example::Language::Idl: str = winrt::unbox_value<winrt::hstring>(Resources().Lookup(winrt::box_value(L"IdlIcon"))); break;
		}

		winrt::Microsoft::UI::Xaml::Controls::PathIcon result;
		result.HorizontalAlignment(winrt::Microsoft::UI::Xaml::HorizontalAlignment::Center);
		result.Data(
			winrt::Microsoft::UI::Xaml::Markup::XamlBindingHelper::ConvertValue
			(
				winrt::xaml_typename<winrt::Microsoft::UI::Xaml::Media::Geometry>(),
				winrt::box_value(str)
			).as<winrt::Microsoft::UI::Xaml::Media::Geometry>()
		);
		return result;
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

	winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> ControlExample::CodeItems()
	{
		return m_codeItems;
	}

	void ControlExample::Expander_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		sender.as<winrt::Microsoft::UI::Xaml::Controls::Expander>().IsExpanded(false);
	}

}
