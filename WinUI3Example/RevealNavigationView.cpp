#include "pch.h"
#include "RevealNavigationView.h"
#if __has_include("RevealNavigationView.g.cpp")
#include "RevealNavigationView.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	void RevealNavigationView::OnApplyTemplate()
	{
		base_type::OnApplyTemplate();

		m_revealFocusPanel = GetTemplateChild(L"RevealFocusPanel").as<winrt::WinUI3Package::RevealFocusPanel>();
		GetTemplateChild(L"MenuItemsHost")
			.as<winrt::Microsoft::UI::Xaml::Controls::ItemsRepeater>()
			.ElementPrepared({this, &RevealNavigationView::onItemsRepeaterElementPrepared});
		GetTemplateChild(L"FooterMenuItemsHost")
			.as<winrt::Microsoft::UI::Xaml::Controls::ItemsRepeater>()
			.ElementPrepared({ this, &RevealNavigationView::onItemsRepeaterElementPrepared });
		GetTemplateChild(L"TopFooterMenuItemsHost")
			.as<winrt::Microsoft::UI::Xaml::Controls::ItemsRepeater>()
			.ElementPrepared({ this, &RevealNavigationView::onItemsRepeaterElementPrepared });
	}

	void RevealNavigationView::onItemsRepeaterElementPrepared(
		winrt::Microsoft::UI::Xaml::Controls::ItemsRepeater const&, 
		winrt::Microsoft::UI::Xaml::Controls::ItemsRepeaterElementPreparedEventArgs const& args)
	{
		auto element = args.Element();
		winrt::WinUI3Package::RevealFocusPanel::SetAttachToPanel(element.as<winrt::Microsoft::UI::Xaml::FrameworkElement>(), m_revealFocusPanel);
	}
}
