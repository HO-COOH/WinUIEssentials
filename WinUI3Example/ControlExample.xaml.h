#pragma once

#include "ControlExample.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ControlExample : ControlExampleT<ControlExample>
    {
		ControlExample();

		winrt::hstring HeaderText();
		void HeaderText(winrt::hstring const& value);
		static winrt::Microsoft::UI::Xaml::DependencyProperty HeaderTextProperty();

		winrt::Windows::Foundation::IInspectable Example();
		void Example(winrt::Windows::Foundation::IInspectable const& value);
		static winrt::Microsoft::UI::Xaml::DependencyProperty ExampleProperty();

		winrt::Windows::Foundation::IInspectable Options();
		void Options(winrt::Windows::Foundation::IInspectable const& value);
		static winrt::Microsoft::UI::Xaml::DependencyProperty OptionsProperty();

		winrt::Windows::Foundation::IInspectable Output();
		void Output(winrt::Windows::Foundation::IInspectable const& value);
		static winrt::Microsoft::UI::Xaml::DependencyProperty OutputProperty();

		winrt::WinUI3Example::CodeSource Xaml();
		void Xaml(winrt::WinUI3Example::CodeSource const& value);
		static winrt::Microsoft::UI::Xaml::DependencyProperty XamlProperty();

		winrt::WinUI3Example::CodeSource Header();
		void Header(winrt::WinUI3Example::CodeSource const& value);
		static winrt::Microsoft::UI::Xaml::DependencyProperty HeaderProperty();

		winrt::WinUI3Example::CodeSource Cpp();
		void Cpp(winrt::WinUI3Example::CodeSource const& value);
		static winrt::Microsoft::UI::Xaml::DependencyProperty CppProperty();

		winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Example::ControlExampleSubstitution> Substitutions();
		void Substitutions(winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Example::ControlExampleSubstitution> const& value);
		static winrt::Microsoft::UI::Xaml::DependencyProperty SubstitutionsProperty();

	private:
		static winrt::Microsoft::UI::Xaml::DependencyProperty m_headerTextProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty m_exampleProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty m_optionsProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty m_outputProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty m_xamlProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty m_headerProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty m_cppProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty m_substitutionsProperty;

		winrt::WinUI3Example::Editor makePivotItem(winrt::WinUI3Example::CodeSource const& code, winrt::WinUI3Example::Language language);

		winrt::WinUI3Example::Editor m_xamlEditor{ nullptr };
		winrt::WinUI3Example::Editor m_headerEditor{ nullptr };
		winrt::WinUI3Example::Editor m_cppEditor{ nullptr };

		static void onXamlChanged(
			winrt::Microsoft::UI::Xaml::DependencyObject const& d, 
			winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
		static void onHeaderChanged(
			winrt::Microsoft::UI::Xaml::DependencyObject const& d, 
			winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
		static void onCppChanged(
			winrt::Microsoft::UI::Xaml::DependencyObject const& d, 
			winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
		static void onSubstitutionsChanged(
			winrt::Microsoft::UI::Xaml::DependencyObject const& d, 
			winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e);

		constexpr static auto languageHeader(winrt::WinUI3Example::Language language)
		{
			switch (language)
			{
				case winrt::WinUI3Example::Language::Xaml: return L"XAML";
				case winrt::WinUI3Example::Language::Cpp: return L"C++";
				case winrt::WinUI3Example::Language::H: return L"Header";
				case winrt::WinUI3Example::Language::Idl: return L"idl";
			}
			return L"";
		}

		static ControlExample* getSelf(winrt::Microsoft::UI::Xaml::DependencyObject const& d);
	public:
		void Expander_Loaded(
			winrt::Windows::Foundation::IInspectable const& sender, 
			winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
	};
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ControlExample : ControlExampleT<ControlExample, implementation::ControlExample>
    {
    };
}
