![](MainLogo.png) 
# WinUI Essentials
A repo dedicated for simplifying C++ development with WinUI2 (Universal Windows Platform) and WinUI3 (Windows App SDK).

![](https://img.shields.io/nuget/v/WinUIEssential.UWP?label=UWP)
![](https://img.shields.io/nuget/v/WinUIEssential.WinUI3?label=winui3)

## Usage
> [!WARNING]
> Make sure to set your C++ language version to C++20 first!

Open the `WinUIEssential.sln` containing 4 projects:
- UWPPackage (project for WinUIEssential.UWP nuget package)
- UWPExample (example gallery for using the above package)
- WinUI3Package (project for WinUIEssential.WinUI3 nuget package)
- WinUI3Example (example gallery for using the above package)

Build the `*Package` project will build the project and pack it with nuget, then install the nuget to your project and start using it.

To build the `*Example` project, do the same thing. They did not reference `*Package` for demo purposes.

> [!NOTE]
> Functionalities for UWP and WinUI3 should be exactly the same unless otherwise noted!

It should be useful until the [community toolkit](https://github.com/CommunityToolkit/WindowsCommunityToolkit) provides C++.

## Content
|Component|UWP|WinUI3|Type
|--|--|--|--|
|WinUIIncludes| :white_check_mark: | :x: | Header only
|TemplateControlHelper| :white_check_mark: | :white_check_mark: | Header only
|Glyphs| :white_check_mark: | :white_check_mark: | Header only + Xaml only
|BadgeGlyphs| :white_check_mark: | :white_check_mark: | Header only
|ToastTemplates| :white_check_mark: | :white_check_mark: | Header only
|ToastBuilder | :white_check_mark: | :white_check_mark: | Header only
|TileTemplates| :white_check_mark: | :white_check_mark: | Header only
|TileBuilder | :white_check_mark: | :white_check_mark: | Header only
|CursorController | :white_check_mark: | :white_check_mark: | WinRT component
|PropertyChangeHelper | :white_check_mark: | :white_check_mark: | Header only
|NegateBoolConverter | :white_check_mark: | :white_check_mark: | WinRT component
|BoolToVisibilityConverter | :white_check_mark: | :white_check_mark: | WinRT component
|ContainerToBoolConverter | :white_check_mark: | :white_check_mark: | WinRT component
|StringToBoolConverter | :white_check_mark: | :white_check_mark: | WinRT component
|ReferenceToBoolConverter | :white_check_mark: | :white_check_mark: | WinRT component
|ConverterGroup | :white_check_mark: | :white_check_mark: | WinRT component
|IsEqualStringTrigger| :white_check_mark: | :white_check_mark: | WinRT component
|IsNullOrEmptyStateTrigger | :white_check_mark: | :white_check_mark: | WinRT component
|ControlSizeTrigger | :white_check_mark: | :white_check_mark: | WinRT component
|CharmBar | :white_check_mark: | :x: | WinRT component
|GroupBox | :white_check_mark: | :white_check_mark: | Control
|SettingsCard | :white_check_mark: | :white_check_mark:* | Control
|SettingsExpander | :white_check_mark: | :white_check_mark:* | Control
|IconButton | :white_check_mark: | :white_check_mark: | Control
|FontIconExtension | :white_check_mark: | :white_check_mark: | WinRT component
|DependentValue| :white_check_mark: | :white_check_mark: | WinRT component
|Taskbar| :x: | :white_check_mark: | Header only
|MarqueeText | :white_check_mark: | :white_check_mark: | Control
|ProgressBarEx | :white_check_mark: | :white_check_mark: | Control
|WindowEx | :x: | :white_check_mark: | Window
|TransparentBackdrop | :x: | :white_check_mark: | SystemBackdrop
|Segmented | :white_check_mark: | :white_check_mark: | Control

*means additional settings required, see the sections for info

---
## WinUIIncludes
Include the WinUI2 headers in your `pch.h`, so you don't waste your time figuring out where the compilation error comming from./

Usage:
Add this in your `pch.h`
```cpp
#include <WinUIIncludes.hpp>
```

## TemplateControlHelper
Automatically call `DefaultStyleKey()` for your templated control so you don't waste your time when you forget to include this line and get an empty control.

Usage: Inherit this class in your header file, make the template argument your **implementation type**.
```cpp
#include <TemplateControlHelper.hpp>
...
struct MyControl : MyControlT<MyControl>, TemplateControlHelper<MyControl>
{
    ...
};
```

## ToastHelper
Helper for creating toast notifications.

### ToastTemplates --- *namespace `ToastTemplates`*
The [built-in templates](https://learn.microsoft.com/en-us/uwp/api/windows.ui.notifications.toasttemplatetype?view=winrt-22621) re-written to strongly-typed classes that derived from `winrt::Windows::UI::Notification::ToastNotification`, so that you can directly use them as arguments for`winrt::Windows::UI::Notifications::ToastNotificationManager`. Example usage:
```cpp
#include <ToastTemplates.hpp>
winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
    .Show(ToastTemplates::ImageWithHeaderAndBody{ L"ms-appx:///Assets/Windows 11.png", L"Header", L"body" });
//alternatively use Microsoft's template name
winrt::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier()
    .Show(ToastTemplates::ToastImageAndText02{ L"ms-appx:///Assets/Windows 11.png", L"Header", L"body" });
```

|Type|Template Name(which can also be used as type)|Sample|
|--|--|--|
|`BodyTextOnly`| `ToastText01` | ![](https://learn.microsoft.com/en-us/uwp/api/windows.ui.notifications/images/toast_1.png?view=winrt-22621)
|`SingleLineHeaderWithBody`| `ToastText02`| ![](https://learn.microsoft.com/en-us/uwp/api/windows.ui.notifications/images/toast_2.png?view=winrt-22621)
|`TwoLineHeaderWithBody`| `ToastText03`| ![](https://learn.microsoft.com/en-us/uwp/api/windows.ui.notifications/images/toast_4.png?view=winrt-22621)
|`HeaderWithTwoSingleLineBody`| `ToastText04`| ![](https://learn.microsoft.com/en-us/uwp/api/windows.ui.notifications/images/toast_5.png?view=winrt-22621)
|`ImageWithBodyOnly`| `ToastImageAndText01`| ![](https://learn.microsoft.com/en-us/uwp/api/windows.ui.notifications/images/toast_6.png?view=winrt-22621)
|`ImageWithHeaderAndBody`| `ToastImageAndText02`| ![](https://learn.microsoft.com/en-us/uwp/api/windows.ui.notifications/images/toast_7.png?view=winrt-22621)
|`ImageWithTwoLineHeaderAndBody`| `ToastImageAndText03`| ![](https://learn.microsoft.com/en-us/uwp/api/windows.ui.notifications/images/toast_8.png?view=winrt-22621)
|`ImageWithHeaderAndTwoSingleLineBody`| `ToastImageAndText04`| ![](https://learn.microsoft.com/en-us/uwp/api/windows.ui.notifications/images/toastimageandtext04.png?view=winrt-22621)

### ToastBuilder --- *namespace `ToastBuilder`*
Strongly-typed, declarative toast notification elements to quickly build toast notifications, as if you are writing XAML. [Schema here.](https://learn.microsoft.com/en-us/uwp/schemas/tiles/toastschema/root-elements) 
Example usage:
<table>
<tr>
    <td>XML</td> <td>C++</td>
<tr>
<tr>
<td>

```xml
<toast duration="long" scenario="reminder" useButtonStyle="true">
    <visual>
        <binding template="ToastText04">
            <text id="1">headline</text>
            <text id="2">body text1</text>
            <text id="3">body text2</text>
        </binding>
    </visual>
    <actions>
        <action content="Accept" arguments="accept"/>
    </actions>
</toast>
```
</td>
<td>

```cpp
Toast().Duration(Long).Scenario(Reminder).UseButtonStyle(true)
(
    Visual()
    (
        Binding().Template(L"ToastText04")
        (
            Text().Id(1)(L"headline"),
            Text().Id(2)(L"body text1"),
            Text().Id(3)(L"body text2")
        )
    ),
    Actions()
    (
        Action().Content(L"Accept").Arguments(L"accept")
    )
)
```

</td>
</tr>
<tr>
<td>

`<tag>...content...</tag>`

</td>
<td>

`Tag()(...content...)`

</td>
</tr>
<tr>
<td>

`attribute="value"`

</td>
<td>

`.Attribute(value)`

</td>
</tr>
<table>

Optionally add a handler to `Action` so you can handle toast notification button click right on site. For more info, see the comment documentation.
```cpp
Actions()
(
	Action().Content(L"Accept").Arguments(L"accept")
	.Click([this](winrt::Windows::ApplicationModel::Activation::ToastNotificationActivatedEventArgs args)
	{
        //Handle Accept button
	}),
	Action().Content(L"Cancel").Arguments(L"cancel")
	.Click([this](winrt::Windows::ApplicationModel::Activation::ToastNotificationActivatedEventArgs args)
	{
        //Handle Cancel button
	})
)
```

## TileTemplates --- *namespace `TileTemplates`*
Similar to [ToastTemplates](#ToastHelper), but for strongly-typed tile templates.

## TileBuilder --- *namespace `TileBuilder`*
Similar to [ToastBuilder](#ToastHelper), but for building tiles.

## Glphys --- *namespace `Glyphs`*
Font glyphs value for Segoe MDL2 Assets fonts. Usage:
```cpp
#include <Glyphs.hpp>
FontIcon().Glyph(Glyphs::GlobalNavButton);
```

There is also a `Glyph` xaml resource dictionary, so you can use name instead of glyph. Usage:
1. Add this to your `App.xaml` (UWP)
```xml
<Application.Resources>
    <controls:XamlControlsResources>
        <controls:XamlControlsResources.MergedDictionaries>
            <ResourceDictionary Source="ms-appx:///UWPPackage/Glyphs.xaml"/>
            ...
        </controls:XamlControlsResources.MergedDictionaries>
    </controls:XamlControlsResources>
</Application.Resources>
```
Add this to your `App.xaml` (WinUI3)
```xml
<Application.Resources>
    <ResourceDictionary>
        <ResourceDictionary.MergedDictionaries>
            <ResourceDictionary Source="ms-appx:///WinUI3Package/Glyphs.xaml"/>
            ...
        </ResourceDictionary.MergedDictionaries>
    </ResourceDictionary>
</Application.Resources>
```
2. Then use `StaticResource` with name to reference the glyph
```xml
<FontIcon Glyph="{StaticResource Send}"/>
```

## CursorController --- *namespace `CursorController`*
Xaml helper for controlling the cursor type when mouse enters. 
Value for `Type` is [CoreCursorType enum](https://learn.microsoft.com/en-us/uwp/api/windows.ui.core.corecursortype?view=winrt-22621). Usage:
```xml
xmlns:essential="using:WinUI3Package"
...
<Rectangle Fill="Red" essential:CursorController.Type="Hand"/>
```

## PropertyChangeHelper --- *namespace `MvvmHelper`*
Helper for `OneWay` binding.

Usage: 
1. Inherit `Windows.UI.Xaml.Data.INotifyPropertyChanged` in `idl`
```
[default_interface]
runtimeclass MyPage : Windows.UI.Xaml.Controls.Page, Windows.UI.Xaml.Data.INotifyPropertyChanged
{
    ...
};
```

2. Inherit from this class in the implementation class.
```cpp
/*MyPage.xaml.h*/
#include <include/PropertyChangeHelper.hpp>

namespace winrt::<MyProject>::implementation
{
    struct MyPage : MyMusicT<MyMusic>, MvvmHelper::PropertyChangeHelper<MyMusic>
    {
        int m_value;
        void Value(int newValue)
        {
            compareAndRaise(m_value, newValue, L"Value");
        };
    }
}
```

## Converters
- bool -> Visibility *namespace `BoolToVisibilityConverter`*
- bool negation *namespace `NegateBoolConverter`*
- container (IVector, IMap) -> bool *namespace `ContainerToBoolConverter`*
- reference (any WinRT runtime type) -> bool *namespace `ReferenceToBoolConverter`*
- String -> bool *namespace `StringToBoolConverter`*
- ConverterGroups *namespace `ConverterGroups`*:
  + define series of converters, that convert value from converter1 -> converter2 -> ...
  + usage:
  ```xml
   <essential:ConverterGroup x:Key="StringToVisibilityConverter">
       <essential:StringToBoolConverter/>
       <essential:BoolToVisibilityConverter/>
   </essential:ConverterGroup>
  ```

## BadgeGlyphs --- *namespace `BadgeGlyphs`*
Helpers for creating badge notification xml.
Usage:
```cpp
#include <include/BadgeGlyphs.hpp>

//glyph badge
winrt::Windows::UI::Notifications::BadgeUpdateManager::CreateBadgeUpdaterForApplication()
	.Update(BadgeGlyphs::MakeBadgeNotification(BadgeGlyphs::Alert));

//number badge
winrt::Windows::UI::Notifications::BadgeUpdateManager::CreateBadgeUpdaterForApplication()
	.Update(BadgeGlyphs::MakeBadgeNotification(1));
```

## Triggers
See the same class in [Community Toolkit](https://github.com/CommunityToolkit/Windows) for documentation.
### ControlSizeTrigger --- *namespace `ControlSizeTrigger`*
### IsEqualStringTrigger --- *namespace `IsEqualStringTrigger`*
Note: For the reason of lacking reflection, we cannot implement `IsEqualStateTrigger
### IsNullOrEmptyStateTrigger --- *namespace `IsNullOrEmptyStateTrigger`*

## SettingsCard --- *namespace `SettingsCard`*
See the same class in [Community Tookit](https://github.com/CommunityToolkit/Windows) for documentation.
- Add this to `App.xaml` (UWP)
```xml
<Application.Resources>
    <controls:XamlControlsResources>
        <controls:XamlControlsResources.MergedDictionaries>
            <ResourceDictionary Source="ms-appx:///UWPPackage/SettingsCard_Resource.xaml"/>
            ...
        </controls:XamlControlsResources.MergedDictionaries>
    </controls:XamlControlsResources>
</Application.Resources>
```
- Add this to `App.xaml` (WinUI3)
```xml
<Application.Resources>
    <ResourceDictionary>
        <ResourceDictionary.MergedDictionaries>
            <ResourceDictionary Source="ms-appx:///WinUI3Package/SettingsCard_Resource.xaml"/>
            ...
        </ResourceDictionary.MergedDictionaries>
    </ResourceDictionary>
</Application.Resources>
```

> [!NOTE]
> For WinUI3, add `#include #include <winrt/Microsoft.UI.Xaml.Controls.AnimatedVisuals.h>` to your `pch.h`

## SettingsExpander --- *namespace `SettingsExpander`*
See the same class in [Community Tookit](https://github.com/CommunityToolkit/Windows) for documentation.
![](assets/settings-expander.png)
Add this to `App.xaml` (UWP)
```xml
<Application.Resources>
    <controls:XamlControlsResources>
        <controls:XamlControlsResources.MergedDictionaries>
            <ResourceDictionary Source="ms-appx:///UWPPackage/SettingsCard_Resource.xaml"/>
            <ResourceDictionary Source="ms-appx:///UWPPackage/SettingsExpander_Resource.xaml"/>
            ...
        </controls:XamlControlsResources.MergedDictionaries>
    </controls:XamlControlsResources>
</Application.Resources>
```
Add this to `App.xaml` (WinUI3)
```xml
<Application.Resources>
    <ResourceDictionary>
        <ResourceDictionary.MergedDictionaries>
            <ResourceDictionary Source="ms-appx:///WinUI3Package/SettingsCard_Resource.xaml"/>
            <ResourceDictionary Source="ms-appx:///WinUI3Package/SettingsExpander_Resource.xaml"/>
            ...
        </ResourceDictionary.MergedDictionaries>
    </ResourceDictionary>
</Application.Resources>
```

> [!NOTE]
> For WinUI3, add `#include #include <winrt/Microsoft.UI.Xaml.Controls.AnimatedVisuals.h>` to your `pch.h`

## CharmBar
Installing this nuget will automatically add `Desktop Extension` to your UWP project, so  you can use the good-ol Windows 8 style charm bar. This package further simplifies it's usage by allowing you to directly define local and global settings, directly in XAML containing UI element.

- Define a global setting in resource section, with `SettingsPaneEx.Settings`
```xml
<Application.Resources>
    <ResourceDictionary>
        <essential:SettingsPaneEx.Settings>
            <!--SettingsCommandEx items-->
            <essential:SettingsCommandEx Id="Item1" Label="Item123">
                <StackPanel>
                    <TextBlock Text="Text1 in item1"/>
                    <TextBlock Text="Text2 in item1"/>
                </StackPanel>
            </essential:SettingsCommandEx>=
            <essential:SettingsCommandEx Id="Item2" Label="Item456">
                <StackPanel>
                    <TextBlock Text="Text3 in item2"/>
                    <TextBlock Text="Text4 in item2"/>
                </StackPanel>
            </essential:SettingsCommandEx>
        </essential:SettingsPaneEx.Settings>
    </ResourceDictionary>
</Application.Resources>
```
![](assets/global-settings.png)
- Define local settings, where you put instance of `SettingsPaneEx` directly in UI as any other xaml controls.
```xml
<Page
    ...
>
    <StackPanel Orientation="Horizontal" HorizontalAlignment="Center" VerticalAlignment="Center">
        <essential:SettingsPaneEx x:Name="LocalSettings">
            <!--SettingsCommandEx items-->
            ...
        </essential:SettingsPaneEx>
    </StackPanel>
</Page>
```
![](assets/local-settings.png)

Define keyboard shortcuts with `SettingsPaneEx.KeyboardAccelerator` property.
```
<essential:SettingsPaneEx.KeyboardAccelerator>
    <KeyboardAccelerator Modifiers="Control" Key="s"/> <!-- Ctrl+S to open settings -->
</essential:SettingsPaneEx.KeyboardAccelerator>
```
## DependentValue ---*namespace `DependentValue`*
A wrapper around a `double` which you can target to with a `Storyboard` and `DoubleAnimation`, and get value out of it. Value is accessed by `.Value` property, which is a `DependencyProperty`, so you can do a `OneWay` binding to it or listen for value change notification.

> [!NOTE]
> Remember to set `EnableDependentAnimation="True"` to make it work!

Usage:
```xml
<Page.Resources>
    <essential:DependentValue x:Name="MyDoubleValue"/>
    <Storyboard x:Name="DoubleValueAnimation">
        <DoubleAnimation  
            From="0"
            To="100"
            Storyboard.TargetName="MyDoubleValue"
            Storyboard.TargetProperty="Value"
            EnableDependentAnimation="True"/>
    </Storyboard>
</Page.Resources>

<StackPanel Orientation="Horizontal" HorizontalAlignment="Center" VerticalAlignment="Center">
    <Button Click="ClickHandler">Click to start storyboard</Button>
    <TextBlock Text="{x:Bind MyDoubleValue.Value, Mode=OneWay}"/>
</StackPanel>
```

## Taskbar --- *namespace `Taskbar`*
Helper for setting taskbar status and progress. Usage:
```cpp
//Set taskbar status
Taskbar::SetProgressState(hwnd, Taskbar::ProgressState::Normal);
//Set taskbar progress value 
Taskbar::SetProgressValue(hwnd, 50); //a third optional parameter for total, default -> 100
```

## MarqueeText --- *namespace `MarqueeText`*
Enhanced version of `MarqueeText` in the community toolkit.
![](assets/marquee-text.png)

## IconButton --- *namespace `IconButton`*
Expandable button, which shows an icon (actually anything) in its default state, and a content when you hover on it.

![](assets/icon-button.gif)

- Add this to `App.xaml` (UWP)
```xml
<Application.Resources>
    <controls:XamlControlsResources>
        <controls:XamlControlsResources.MergedDictionaries>
            <ResourceDictionary Source="ms-appx:///UWPPackage/IconButton_Resource.xaml"/>
            ...
        </controls:XamlControlsResources.MergedDictionaries>
    </controls:XamlControlsResources>
</Application.Resources>
```
- Add this to `App.xaml` (WinUI3)
```xml
<Application.Resources>
    <ResourceDictionary>
        <ResourceDictionary.MergedDictionaries>
            <ResourceDictionary Source="ms-appx:///WinUI3Package/IconButton_Resource.xaml"/>
            ...
        </ResourceDictionary.MergedDictionaries>
    </ResourceDictionary>
</Application.Resources>
```

## ProgressBarEx --- *namespace `ProgressBarEx`*
A progress bar with animated highlight colors (and animated progress). Default to vista-like styles but also allows you to customize its color.

|Property| DependencyProperty? | Description
|---|---|---|
|HighColor | :white_check_mark: | the shimmer highlight color
|BaseColor | :white_check_mark: | the base background color of the finish part
|Background | :white_check_mark: | the color of the rest part
|Percent | :white_check_mark: | range: 0~100 
|Value | :white_check_mark: | normalized percent, range: 0.0~1.0

![](assets/progressbarex.gif)
Add this to `App.xaml` (UWP)
```xml
<Application.Resources>
    <controls:XamlControlsResources>
        <controls:XamlControlsResources.MergedDictionaries>
            <ResourceDictionary Source="ms-appx:///Glyphs.xaml"/>
            ...
        </controls:XamlControlsResources.MergedDictionaries>
    </controls:XamlControlsResources>
</Application.Resources>
```
Add this to `App.xaml` (WinUI3)
```xml
<Application.Resources>
    <ResourceDictionary>
        <ResourceDictionary.MergedDictionaries>
            <ResourceDictionary Source="ms-appx:///WinUI3Package/ProgressBarEx_Resource.xaml"/>
            ...
        </ResourceDictionary.MergedDictionaries>
    </ResourceDictionary>
</Application.Resources>
```

## WindowEx --- *namespace `WindowEx`*
### Basic Property
|name|Description
|---|---|
|Int32 MinWidth;|Minimum width in DIP
|Int32 MaxWidth;|Maximum width in DIP
|Int32 MinHeight;|...
|Int32 MaxHeight;|...
|Int32 Width;|...
|Int32 Height;|...
|Int32 RawWidth;|Actual width in pixel
|Int32 RawHeight;|Actual height in pixel
|UInt32 Dpi{ get; };|Current window dpi
|Boolean IsMinimizable;|...
|Boolean IsMaximizable;|...
|Boolean HasBorder;|...
|Boolean HasTitleBar;|...
|Boolean IsResizable;|...
|Boolean IsAlwaysOnTop;|...
|Boolean IsShownInSwitcher;|...
|Boolean TitleBarDarkMode;| Set win32 titlebar to dark mode (support down to Windows 10 17763)
|Boolean TitleBarAutoDarkMode;| Enable automatic titlebar dark mode (support down to Windows 10 17763), works regardless of `ExtendContentIntoTitleBar`
|Microsoft.UI.Xaml.UIElement TitleBar;| Custom title bar, if set, automatically calls `ExtendContentIntoTitleBar` for you
|String Icon;| Set `.ico` icon used for win32 titlebar
### Extensions
`WindowEx.IsInteractive`: used when customizing a title bar, automatically calculate and update `InputNonClientPointerSource` for you
Usage:
```xml
<essential:WindowEx.TitleBar>
    <Grid x:Name="AppTitleBar" Height="48" Loaded="AppTitleBar_Loaded">
        <Grid.ColumnDefinitions>
            ...
        </Grid.ColumnDefinitions>

        <AutoSuggestBox x:Name="TitleBarSearchBox" 
                Grid.Column="4" 
                QueryIcon="Find"
                PlaceholderText="Search"
                VerticalAlignment="Center"
                MaxWidth="600"
                essential:WindowEx.IsInteractive="True"/>
        <PersonPicture x:Name="PersonPic" 
               Grid.Column="6" 
               Height="32" Margin="0,0,16,0"
               essential:WindowEx.IsInteractive="True"/>
    </Grid>
</essential:WindowEx.TitleBar>
```

## TransparentBackdrop --- *namespace `TransparentBackdrop*
Make your `WindowEx` fully transparent.
```xml
<essential:WindowEx
    ...
    <essential:WindowEx.SystemBackdrop>
        <essential:TransparentBackdrop/>
    <essential:WindowEx.SystemBackdrop>
</essential:WindowEx>
```
![](assets/transparent-window.png)

- left: ExtendContentIntoTitleBar
- right: Win32 Titlebar

## UIElementExtension --- *namespace `UIElementExtension`*
See the same class in [Community Toolkit](https://github.com/CommunityToolkit/Windows) for documentation.
Usage:
```xml
<Grid Width="148"
    Height="148"
    essential:UIElementExtension.ClipToBounds="True"
    .../>
```

## Segmented --- *namespace `Segmented`*
Almost like the `Segmented` control in [Community Toolkit](https://github.com/CommunityToolkit/Windows) but with more customizations.

- Animated selected-item transition
![](assets/segmented-item-animation.gif)
- Does not limited to `Icon + Text`. Use any UIElement
```xml
<essential:SegmentedItem>
    <StackPanel Orientation="Horizontal">
        <FontIcon Glyph="&#xE8C0;"/>
        <TextBlock Text="Week"/>
    </StackPanel>
</essential:SegmentedItem>
```
- Button style has 0 size margin
```xml
<essential:Segmented Style="{StaticResource ButtonSegmentedStyle}">
    <essential:SegmentedItem>
        <StackPanel Orientation="Horizontal" Spacing="4">
            <FontIcon Glyph="&#xE8BF;"/>
            <TextBlock Text="Day"/>
        </StackPanel>
    </essential:SegmentedItem>
    <essential:SegmentedItem>
        <StackPanel Orientation="Horizontal" Spacing="4">
            <FontIcon Glyph="&#xE8C0;"/>
            <TextBlock Text="Week"/>
        </StackPanel>
    </essential:SegmentedItem>
    <essential:SegmentedItem>
        <StackPanel Orientation="Horizontal" Spacing="4}">
            <FontIcon Glyph="&#xE787;"/>
            <TextBlock Text="Month"/>
        </StackPanel>
    </essential:SegmentedItem>
</essential:Segmented>
```
![](assets/button-style-segmented.png)
- Support vertical layout
```xml
<essential:Segmented>
    <essential:SegmentedItem>
        <StackPanel Orientation="Horizontal" Spacing="7">
            <SymbolIcon Symbol="Accept"/>
            <TextBlock Text="Content1"/>
        </StackPanel>
    </essential:SegmentedItem>

    <essential:SegmentedItem>
        <StackPanel Orientation="Horizontal" Spacing="7">
            <SymbolIcon Symbol="Add"/>
            <TextBlock Text="Content2"/>
        </StackPanel>
    </essential:SegmentedItem>

    <essential:SegmentedItem>
        <StackPanel Orientation="Horizontal" Spacing="7">
            <SymbolIcon Symbol="Admin"/>
            <StackPanel Orientation="Vertical">
                <TextBlock Text="Content longerrrrrrrrrr"/>
                <TextBlock Text="Content 2nd line"/>
            </StackPanel>
        </StackPanel>
    </essential:SegmentedItem>

    <essential:Segmented.ItemsPanel>
        <ItemsPanelTemplate>
            <StackPanel Orientation="Vertical"/>
        </ItemsPanelTemplate>
    </essential:Segmented.ItemsPanel>
</essential:Segmented>
```
- Allow reordering items
```xml
<essential:Segmented CanReorderItems="True" AllowDrop="True"
    ...
```

Usage:
- Add this to `App.xaml` (UWP)
```xml
<Application.Resources>
    <controls:XamlControlsResources>
        <controls:XamlControlsResources.MergedDictionaries>
            <ResourceDictionary Source="ms-appx:///UWPPackage/Segmented_Resource.xaml"/>
            ...
        </controls:XamlControlsResources.MergedDictionaries>
    </controls:XamlControlsResources>
</Application.Resources>
```
- Add this to `App.xaml` (WinUI3)
```xml
<Application.Resources>
    <ResourceDictionary>
        <ResourceDictionary.MergedDictionaries>
            <ResourceDictionary Source="ms-appx:///WinUI3Package/Segmented_Resource.xaml"/>
            ...
        </ResourceDictionary.MergedDictionaries>
    </ResourceDictionary>
</Application.Resources>
```