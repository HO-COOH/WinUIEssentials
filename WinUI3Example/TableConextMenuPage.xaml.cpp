#include "pch.h"
#include "TableConextMenuPage.xaml.h"
#if __has_include("TableConextMenuPage.g.cpp")
#include "TableConextMenuPage.g.cpp"
#endif
#include <format>

namespace winrt::WinUI3Example::implementation
{
    void TableConextMenuPage::OnTableContextMenuRequested(
        winrt::WinUI3Package::Table const&,
        winrt::WinUI3Package::ContextMenuRequestedEventArgs const& args)
    {
        if (!EnableContextMenuSwitch().IsOn())
        {
			args.Handled(true);
			return;
        }

        winrt::Microsoft::UI::Xaml::Controls::MenuFlyout flyout;

        winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItem item;
        item.Text(std::format(L"This is Row {}, Column {}", args.RowIndex(), args.ColumnIndex()));
        flyout.Items().ReplaceAll({ item });

        args.ContextMenu(flyout);
    }
}
