#include "pch.h"
#include "TableContextMenuPage.h"
#if __has_include("TableContextMenuPage.g.cpp")
#include "TableContextMenuPage.g.cpp"
#endif


namespace winrt::UWPExample::implementation
{
	void TableContextMenuPage::OnTableContextMenuRequested(
		winrt::UWPPackage::Table const&, 
		winrt::UWPPackage::ContextMenuRequestedEventArgs const& args)
	{
		if (!EnableContextMenuSwitch().IsOn())
		{
			args.Handled(true);
			return;
		}

		winrt::Windows::UI::Xaml::Controls::MenuFlyout flyout;

		winrt::Windows::UI::Xaml::Controls::MenuFlyoutItem item;
		item.Text(std::format(L"This is Row {}, Column {}", args.RowIndex(), args.ColumnIndex()));
		flyout.Items().ReplaceAll({ item });

		args.ContextMenu(flyout);
	}
}
