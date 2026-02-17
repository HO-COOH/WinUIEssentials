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

		winrt::WinUI3Example::CodeSource Idl();
		void Idl(winrt::WinUI3Example::CodeSource const& value);
		static winrt::Microsoft::UI::Xaml::DependencyProperty IdlProperty();

		winrt::WinUI3Example::CodeSource Header();
		void Header(winrt::WinUI3Example::CodeSource const& value);
		static winrt::Microsoft::UI::Xaml::DependencyProperty HeaderProperty();

		winrt::WinUI3Example::CodeSource Cpp();
		void Cpp(winrt::WinUI3Example::CodeSource const& value);
		static winrt::Microsoft::UI::Xaml::DependencyProperty CppProperty();

		winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Example::ControlExampleSubstitution> Substitutions();
		void Substitutions(winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Example::ControlExampleSubstitution> const& value);
		static winrt::Microsoft::UI::Xaml::DependencyProperty SubstitutionsProperty();

		static winrt::hstring UnboxString(winrt::Windows::Foundation::IInspectable const& value);
		static winrt::hstring BooleanToString(bool value);

		winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> CodeItems();
	private:
		static winrt::Microsoft::UI::Xaml::DependencyProperty m_headerTextProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty m_exampleProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty m_optionsProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty m_outputProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty m_xamlProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty m_idlProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty m_headerProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty m_cppProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty m_substitutionsProperty;
		winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> m_codeItems = winrt::single_threaded_vector<winrt::Windows::Foundation::IInspectable>();

		void makePivotItem(winrt::WinUI3Example::CodeSource const& code, winrt::WinUI3Example::Language language);

		static void onXamlChanged(
			winrt::Microsoft::UI::Xaml::DependencyObject const& d, 
			winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
		static void onIdlChanged(
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

		winrt::Microsoft::UI::Xaml::Controls::PathIcon languageHeader(winrt::WinUI3Example::Language language);
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
