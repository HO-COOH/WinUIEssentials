#pragma once
#include "ControlExample.g.h"
#include <EnsureDependencyProperty.hpp>

namespace winrt::PackageRoot::implementation
{
	struct ControlExample : ControlExampleT<ControlExample>, EnsureDependencyProperty<ControlExample>
	{
		static void EnsureDependencyProperties();
		ControlExample();

		winrt::hstring HeaderText();
		void HeaderText(winrt::hstring const& value);
		static winrt::WinUINamespace::UI::Xaml::DependencyProperty HeaderTextProperty();

		winrt::Windows::Foundation::IInspectable Example();
		void Example(winrt::Windows::Foundation::IInspectable const& value);
		static winrt::WinUINamespace::UI::Xaml::DependencyProperty ExampleProperty();

		winrt::Windows::Foundation::IInspectable Options();
		void Options(winrt::Windows::Foundation::IInspectable const& value);
		static winrt::WinUINamespace::UI::Xaml::DependencyProperty OptionsProperty();

		winrt::Windows::Foundation::IInspectable Output();
		void Output(winrt::Windows::Foundation::IInspectable const& value);
		static winrt::WinUINamespace::UI::Xaml::DependencyProperty OutputProperty();

		winrt::PackageRoot::CodeSource Xaml();
		void Xaml(winrt::PackageRoot::CodeSource const& value);
		static winrt::WinUINamespace::UI::Xaml::DependencyProperty XamlProperty();

		winrt::PackageRoot::CodeSource Idl();
		void Idl(winrt::PackageRoot::CodeSource const& value);
		static winrt::WinUINamespace::UI::Xaml::DependencyProperty IdlProperty();

		winrt::PackageRoot::CodeSource Header();
		void Header(winrt::PackageRoot::CodeSource const& value);
		static winrt::WinUINamespace::UI::Xaml::DependencyProperty HeaderProperty();

		winrt::PackageRoot::CodeSource Cpp();
		void Cpp(winrt::PackageRoot::CodeSource const& value);
		static winrt::WinUINamespace::UI::Xaml::DependencyProperty CppProperty();

		winrt::Windows::Foundation::Collections::IVector<winrt::PackageRoot::ControlExampleSubstitution> Substitutions();
		void Substitutions(winrt::Windows::Foundation::Collections::IVector<winrt::PackageRoot::ControlExampleSubstitution> const& value);
		static winrt::WinUINamespace::UI::Xaml::DependencyProperty SubstitutionsProperty();

		static winrt::hstring UnboxString(winrt::Windows::Foundation::IInspectable const& value);
		static winrt::hstring BooleanToString(bool value);

		winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> CodeItems();
	private:
		static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_headerTextProperty = nullptr;
		static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_exampleProperty = nullptr;
		static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_optionsProperty = nullptr;
		static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_outputProperty = nullptr;
		static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_xamlProperty = nullptr;
		static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_idlProperty = nullptr;
		static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_headerProperty = nullptr;
		static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_cppProperty = nullptr;
		static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_substitutionsProperty = nullptr;
		static inline winrt::WinUINamespace::UI::Composition::ScalarKeyFrameAnimation m_iconShowAnimation{ nullptr };
		static inline winrt::WinUINamespace::UI::Composition::ScalarKeyFrameAnimation m_iconHideAnimation{ nullptr };
		winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> m_codeItems = winrt::single_threaded_vector<winrt::Windows::Foundation::IInspectable>();

		void makePivotItem(winrt::PackageRoot::CodeSource const& code, winrt::PackageRoot::Language language);

		void createAnimations(winrt::WinUINamespace::UI::Composition::Compositor const& compositor);
		void startExpanderIconAnimations(winrt::WinUINamespace::UI::Composition::ScalarKeyFrameAnimation& animation);

		static void onXamlChanged(
			winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
			winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
		static void onIdlChanged(
			winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
			winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
		static void onHeaderChanged(
			winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
			winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
		static void onCppChanged(
			winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
			winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
		static void onSubstitutionsChanged(
			winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
			winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);

		winrt::WinUINamespace::UI::Xaml::Controls::PathIcon languageHeader(winrt::PackageRoot::Language language);
		static ControlExample* getSelf(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d);
	public:
		void Expander_Loaded(
			winrt::Windows::Foundation::IInspectable const& sender,
			winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const& e);
		void Expander_Expanding(winrt::Microsoft::UI::Xaml::Controls::Expander const& sender, winrt::Microsoft::UI::Xaml::Controls::ExpanderExpandingEventArgs const& args);
		void Expander_Collapsed(winrt::Microsoft::UI::Xaml::Controls::Expander const& sender, winrt::Microsoft::UI::Xaml::Controls::ExpanderCollapsedEventArgs const& args);
	};
}

namespace winrt::PackageRoot::factory_implementation
{
	struct ControlExample : ControlExampleT<ControlExample, implementation::ControlExample>
	{
	};
}
