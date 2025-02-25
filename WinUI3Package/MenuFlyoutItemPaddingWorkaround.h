#pragma once
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Windows.Foundation.Collections.h>

#pragma region Forward Declarations
namespace winrt::Microsoft::UI::Xaml::Controls
{
	struct MenuFlyout;
	struct MenuFlyoutItem;
}
#pragma endregion

/**
 * @brief workaround for https://github.com/microsoft/microsoft-ui-xaml/issues/7374
 * 
 * @detail When calling `MenuFlyout.ShowAt()` for the first time, without previous interaction,
 * the menu item will show as "touch-friendly" mode, meaning a wider padding. And successive call will
 * show as "mouse-friendly" mode, with a thinner padding. This will look like buggy for most users.
 * This method recursively force the `MenuFlyoutItem` padding.
 */
class MenuFlyoutItemPaddingWorkaround
{
	constexpr static auto ForceHeight = 32.0;
	constexpr static winrt::Microsoft::UI::Xaml::Thickness ForcePadding{ 8,5,5,5 };

	struct ItemKindCount
	{
		int numNormalItems;
		int numSeparators;
	};
	static ItemKindCount applyImpl(
		winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItemBase> const& items
	);
public:
	static void Apply(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& menu);
};
