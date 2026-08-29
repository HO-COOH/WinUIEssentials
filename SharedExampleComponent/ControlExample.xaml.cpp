#include "pch.h"
#include "ControlExample.xaml.h"
#if __has_include("ControlExample.g.cpp")
#include "ControlExample.g.cpp"
#endif
#include "CodeSource.h"
#include <winrt/Microsoft.Web.WebView2.Core.h>
#if defined Build_WinUIExample
#include "CodeWindow.xaml.h"
#else
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.WindowManagement.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.Foundation.Metadata.h>
#include "CodeWindowPage.h"
#endif

using namespace winrt;
using namespace WinUINamespace::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::PackageRoot::implementation
{
	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlExample::m_headerTextProperty = nullptr;
	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlExample::m_exampleProperty = nullptr;
	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlExample::m_optionsProperty = nullptr;
	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlExample::m_outputProperty = nullptr;
	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlExample::m_xamlProperty = nullptr;
	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlExample::m_idlProperty = nullptr;
	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlExample::m_headerProperty = nullptr;
	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlExample::m_cppProperty = nullptr;
	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlExample::m_substitutionsProperty = nullptr;

	void ControlExample::EnsureDependencyProperties()
	{
		if (m_headerTextProperty) return;

		m_headerTextProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"HeaderText",
			winrt::xaml_typename<winrt::hstring>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);
		m_exampleProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"Example",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);
		m_optionsProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"Options",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);
		m_outputProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"Output",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);
		m_xamlProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"Xaml",
			winrt::xaml_typename<winrt::PackageRoot::CodeSource>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &ControlExample::onXamlChanged }
		);
		m_idlProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"Idl",
			winrt::xaml_typename<winrt::PackageRoot::CodeSource>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &ControlExample::onIdlChanged }
		);
		m_cppProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"Cpp",
			winrt::xaml_typename<winrt::PackageRoot::CodeSource>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &ControlExample::onCppChanged }
		);
		m_headerProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"Header",
			winrt::xaml_typename<winrt::PackageRoot::CodeSource>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &ControlExample::onHeaderChanged }
		);
		m_substitutionsProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"Substitutions",
			winrt::xaml_typename<winrt::Windows::Foundation::Collections::IVector<winrt::PackageRoot::ControlExampleSubstitution>>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);
	}

	ControlExample::ControlExample()
	{
		Substitutions(winrt::single_threaded_vector<winrt::PackageRoot::ControlExampleSubstitution>());
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

	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlExample::HeaderTextProperty()
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

	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlExample::ExampleProperty()
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

	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlExample::OptionsProperty()
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

	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlExample::OutputProperty()
	{
		return m_outputProperty;
	}

	winrt::PackageRoot::CodeSource ControlExample::Xaml()
	{
		return winrt::unbox_value<winrt::PackageRoot::CodeSource>(GetValue(m_xamlProperty));
	}

	void ControlExample::Xaml(winrt::PackageRoot::CodeSource const& value)
	{
		SetValue(m_xamlProperty, winrt::box_value(value));
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlExample::XamlProperty()
	{
		return m_xamlProperty;
	}

	winrt::PackageRoot::CodeSource ControlExample::Idl()
	{
		return winrt::unbox_value<winrt::PackageRoot::CodeSource>(GetValue(m_idlProperty));
	}

	void ControlExample::Idl(winrt::PackageRoot::CodeSource const& value)
	{
		SetValue(m_idlProperty, value);
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlExample::IdlProperty()
	{
		return m_idlProperty;
	}

	winrt::PackageRoot::CodeSource ControlExample::Header()
	{
		return winrt::unbox_value<winrt::PackageRoot::CodeSource>(GetValue(m_headerProperty));
	}

	void ControlExample::Header(winrt::PackageRoot::CodeSource const& value)
	{
		SetValue(m_headerProperty, winrt::box_value(value));
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlExample::HeaderProperty()
	{
		return m_headerProperty;
	}

	winrt::PackageRoot::CodeSource ControlExample::Cpp()
	{
		return winrt::unbox_value<winrt::PackageRoot::CodeSource>(GetValue(m_cppProperty));
	}

	void ControlExample::Cpp(winrt::PackageRoot::CodeSource const& value)
	{
		SetValue(m_cppProperty, winrt::box_value(value));
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlExample::CppProperty()
	{
		return m_cppProperty;
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::PackageRoot::ControlExampleSubstitution> ControlExample::Substitutions()
	{
		return winrt::unbox_value<winrt::Windows::Foundation::Collections::IVector<winrt::PackageRoot::ControlExampleSubstitution>>(GetValue(m_substitutionsProperty));
	}

	void ControlExample::Substitutions(winrt::Windows::Foundation::Collections::IVector<winrt::PackageRoot::ControlExampleSubstitution> const& value)
	{
		SetValue(m_substitutionsProperty, value);
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlExample::SubstitutionsProperty()
	{
		return m_substitutionsProperty;
	}

	void ControlExample::makePivotItem(winrt::PackageRoot::CodeSource const& code, winrt::PackageRoot::Language language)
	{
		auto codeImpl = winrt::get_self<CodeSource>(code);
		codeImpl->m_codeLanguage = language;
		m_codeItems.Append(code);
	}

	void ControlExample::createAnimations(winrt::WinUINamespace::UI::Composition::Compositor const& compositor)
	{
		m_iconShowAnimation = compositor.CreateScalarKeyFrameAnimation();
		m_iconShowAnimation.InsertExpressionKeyFrame(0.f, L"this.Target.Size.Y * 1.5");
		m_iconShowAnimation.InsertKeyFrame(1.f, 0);
		m_iconShowAnimation.Target(L"Translation.Y");

		m_iconHideAnimation = compositor.CreateScalarKeyFrameAnimation();
		m_iconHideAnimation.InsertKeyFrame(0.f, 0);
		m_iconHideAnimation.InsertExpressionKeyFrame(1.f, L"this.Target.Size.Y * 1.5");
		m_iconHideAnimation.DelayBehavior(winrt::WinUINamespace::UI::Composition::AnimationDelayBehavior::SetInitialValueBeforeDelay);
		m_iconHideAnimation.Target(L"Translation.Y");
	}

	void ControlExample::onXamlChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const&)
	{
		auto self = getSelf(d);
		self->makePivotItem(self->Xaml(), winrt::PackageRoot::Language::Xaml);
	}

	void ControlExample::onIdlChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const&)
	{
		auto self = getSelf(d);
		self->makePivotItem(self->Idl(), winrt::PackageRoot::Language::Idl);
	}

	void ControlExample::onHeaderChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const&)
	{
		auto self = getSelf(d);
		self->makePivotItem(self->Header(), winrt::PackageRoot::Language::H);
	}

	void ControlExample::onCppChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const&)
	{
		auto self = getSelf(d);
		self->makePivotItem(self->Cpp(), winrt::PackageRoot::Language::Cpp);
	}

	void ControlExample::onSubstitutionsChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const&,
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const&)
	{
	}

	winrt::WinUINamespace::UI::Xaml::Controls::PathIcon ControlExample::languageHeader(winrt::PackageRoot::Language language)
	{
		winrt::hstring str;
		switch (language)
		{
			case winrt::PackageRoot::Language::Xaml: str = winrt::unbox_value<winrt::hstring>(Resources().Lookup(winrt::box_value(L"XamlIcon"))); break;
			case winrt::PackageRoot::Language::Cpp: str = winrt::unbox_value<winrt::hstring>(Resources().Lookup(winrt::box_value(L"CppIcon"))); break;
			case winrt::PackageRoot::Language::H: str = winrt::unbox_value<winrt::hstring>(Resources().Lookup(winrt::box_value(L"HIcon"))); break;
			case winrt::PackageRoot::Language::Idl: str = winrt::unbox_value<winrt::hstring>(Resources().Lookup(winrt::box_value(L"IdlIcon"))); break;
		}

		winrt::WinUINamespace::UI::Xaml::Controls::PathIcon result;
		result.HorizontalAlignment(winrt::WinUINamespace::UI::Xaml::HorizontalAlignment::Center);
		result.Data(
			winrt::WinUINamespace::UI::Xaml::Markup::XamlBindingHelper::ConvertValue
			(
				winrt::xaml_typename<winrt::WinUINamespace::UI::Xaml::Media::Geometry>(),
				winrt::box_value(str)
			).as<winrt::WinUINamespace::UI::Xaml::Media::Geometry>()
		);
		return result;
	}

	ControlExample* ControlExample::getSelf(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d)
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

	void ControlExample::Expander_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const&)
	{
		//sender.as<winrt::Microsoft::UI::Xaml::Controls::Expander>().IsExpanded(false);

#if defined Build_WinUIExample
		if (!m_iconShowAnimation)
			createAnimations(winrt::WinUINamespace::UI::Xaml::Media::CompositionTarget::GetCompositorForCurrentThread());
#else
		if (!m_iconShowAnimation)
			createAnimations(winrt::Windows::UI::Xaml::Window::Current().Compositor());
#endif
	}

	void ControlExample::startExpanderIconAnimations(winrt::WinUINamespace::UI::Composition::ScalarKeyFrameAnimation& animation)
	{
		if (!m_iconShowAnimation)
			return;

		auto addAnimation = [&animation, i = 0](winrt::WinUINamespace::UI::Xaml::Controls::Viewbox const& icon) mutable
		{
			//this animation must be played on the visual, not the control itself
			//as the expression "this.Target.Size.Y" will complain when using on a normal control
			auto visual = winrt::WinUINamespace::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(icon);
			winrt::WinUINamespace::UI::Xaml::Hosting::ElementCompositionPreview::SetIsTranslationEnabled(icon, true);
			animation.DelayTime(std::chrono::milliseconds{ 50 * i });
			visual.StartAnimation(L"Translation.Y", animation);
			++i;
		};

		if (Xaml())
			addAnimation(XamlIcon());
		if (Idl())
			addAnimation(IdlIcon());
		if (Header())
			addAnimation(HIcon());
		if (Cpp())
			addAnimation(CppIcon());
	}

	void ControlExample::Expander_Expanding(winrt::Microsoft::UI::Xaml::Controls::Expander const&, winrt::Microsoft::UI::Xaml::Controls::ExpanderExpandingEventArgs const&)
	{
		startExpanderIconAnimations(m_iconHideAnimation);
	}

	void ControlExample::Expander_Collapsed(winrt::Microsoft::UI::Xaml::Controls::Expander const&, winrt::Microsoft::UI::Xaml::Controls::ExpanderCollapsedEventArgs const&)
	{
		startExpanderIconAnimations(m_iconShowAnimation);
	}

#if defined Build_WinUIExample
	void ControlExample::OpenCodeInNewWindowButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const& e)
	{

		winrt::make_self<CodeWindow>(HeaderText(), m_codeItems)->Activate();


	}
#else

	std::vector<ControlExample::CodeItemData> ControlExample::cloneCodeItem()
	{
		std::vector<ControlExample::CodeItemData> data;
		data.reserve(m_codeItems.Size());
		std::ranges::transform(m_codeItems, std::back_inserter(data), [](winrt::Windows::Foundation::IInspectable const& item) {
			auto codeSource = item.as<winrt::PackageRoot::CodeSource>();
			auto codeSourceImpl = winrt::get_self<CodeSource>(codeSource);
			return ControlExample::CodeItemData{
				codeSourceImpl->m_code,
				codeSourceImpl->m_codeLanguage
			};
		});
		return data;
	}

	winrt::fire_and_forget ControlExample::OpenCodeInNewWindowButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const& e)
	{
		if (winrt::Windows::Foundation::Metadata::ApiInformation::IsTypePresent(L"Windows.UI.WindowManagement.AppWindow"))
		{
			//18362+ same thread new window
			auto appWindow = co_await winrt::Windows::UI::WindowManagement::AppWindow::TryCreateAsync();
			winrt::PackageRoot::CodePivot codePivot;
			codePivot.ItemsSource(m_codeItems);
			winrt::Windows::UI::Xaml::Hosting::ElementCompositionPreview::SetAppWindowContent(appWindow, codePivot);
			appWindow.Title(HeaderText());
			appWindow.TryShowAsync();
			co_return;
		}


		auto newView = winrt::Windows::ApplicationModel::Core::CoreApplication::CreateNewView();
		newView.Dispatcher().RunAsync({}, [title = HeaderText(), codeItem = cloneCodeItem()]
		{
			auto window = winrt::Windows::UI::Xaml::Window::Current();

			std::vector<winrt::Windows::Foundation::IInspectable> copiedCodeItems;
			std::ranges::transform(codeItem, std::back_inserter(copiedCodeItems), [](ControlExample::CodeItemData const& data) {
				return winrt::Windows::Foundation::IInspectable{ *winrt::make_self<CodeSource>(data.language, data.m_code) };
			});

			window.Content(
				winrt::make<CodeWindowPage>(title, winrt::single_threaded_vector(std::move(copiedCodeItems)))
			);
			winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Title(title);
			window.Activate();

			winrt::Windows::UI::ViewManagement::ApplicationViewSwitcher::TryShowAsStandaloneAsync(
				winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Id()
			);
		});
	}
#endif
}
