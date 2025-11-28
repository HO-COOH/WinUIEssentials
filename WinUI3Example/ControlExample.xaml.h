#pragma once

#include "ControlExample.g.h"

namespace Impl
{
	/*TODO:
		This is a workaround for the Editor runtimeclass I created
		I used that class in `ControlExample::makePivotItem()`, and it crashed when switching from `ThemeListenerPage` to any other pages
		It seems like creating two `Editor` will cause the crash, but I may have fucked up object life time, but I tried by removing 
		all the event handlers, and it still crashes, so I'm not sure what's the problem.
		You can help to investigate by changing the `Impl::Editor` to `winrt::WinUI3Example::Editor`.
	*/
	struct Editor : winrt::Microsoft::UI::Xaml::Controls::WebView2, std::enable_shared_from_this<Editor>
	{
		Editor(std::nullptr_t) : WebView2{ nullptr } {}
		Editor(
			winrt::hstring const& code, 
			winrt::WinUI3Example::Language language, 
			winrt::Microsoft::UI::Xaml::Controls::ProgressBar const& progressBar,
			winrt::WinUI3Example::CodeSource const& codeSource);

		void Load();

		winrt::hstring Code();
		void Code(winrt::hstring const& value);

		winrt::fire_and_forget loadHtml();

		winrt::hstring m_code;
		winrt::WinUI3Example::Language m_language;
		winrt::Microsoft::Web::WebView2::Core::CoreWebView2 m_coreWebView{ nullptr };

	private:
		NavigationCompleted_revoker m_navigationCompletedRevoker;
		winrt::weak_ref<winrt::Microsoft::UI::Xaml::Controls::ProgressBar> m_progressBarRef;
		winrt::weak_ref<winrt::WinUI3Example::CodeSource> m_codeRef;
		void createEditor();
		static double measureHeight(winrt::hstring const& value);
		static std::wstring_view ltrim(std::wstring_view str);
		static std::wstring_view rtrim(std::wstring_view str);
		static winrt::hstring stripEmptyLine(winrt::hstring const& value);
		wchar_t const* languageString() const;
	};
}
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

		static winrt::hstring GetStringFromComboBoxItem(winrt::Windows::Foundation::IInspectable const& value);
		static winrt::hstring BooleanToString(bool value);
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

		std::shared_ptr<Impl::Editor> makePivotItem(winrt::WinUI3Example::CodeSource const& code, winrt::WinUI3Example::Language language);

		std::shared_ptr<Impl::Editor> m_xamlEditor{ nullptr };
		std::shared_ptr<Impl::Editor> m_idlEditor{ nullptr };
		std::shared_ptr<Impl::Editor> m_headerEditor{ nullptr };
		std::shared_ptr<Impl::Editor> m_cppEditor{ nullptr };

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
