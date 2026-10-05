#include "pch.h"
#include "PlaygroundPage.h"
#if __has_include("PlaygroundPage.g.cpp")
#include "PlaygroundPage.g.cpp"
#endif
#include "CreateWindowHelper.hpp"

namespace winrt::UWPExample::implementation
{
    void PlaygroundPage::InitializeComponent()
    {
        PlaygroundPageT::InitializeComponent();
        XamlString().Editor().SetText(LR"(<Page 
    xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
    xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
    xmlns:essential="using:UWPPackage">

    <essential:SettingsExpander
        Description="The SettingsExpander has the same properties as a Card, and you can set SettingsCard as part of the Items collection."
        Header="SettingsExpander">
        <essential:SettingsExpander.HeaderIcon>
            <FontIcon Glyph="&#xE91B;" />
        </essential:SettingsExpander.HeaderIcon>

        <ComboBox SelectedIndex="0">
            <ComboBoxItem>Option 1</ComboBoxItem>
            <ComboBoxItem>Option 2</ComboBoxItem>
            <ComboBoxItem>Option 3</ComboBoxItem>
        </ComboBox>

        <essential:SettingsExpander.Items>
            <essential:SettingsCard Header="A basic SettingsCard within an SettingsExpander">
                <Button Content="Button" />
            </essential:SettingsCard>
            <essential:SettingsCard
                Description="SettingsCard within an Expander can be made clickable too!"
                Header="This item can be clicked"
                IsClickEnabled="True" />

            <essential:SettingsCard ContentAlignment="Left">
                <CheckBox Content="Here the ContentAlignment is set to Left. This is great for e.g. CheckBoxes or RadioButtons." />
            </essential:SettingsCard>

            <essential:SettingsCard
                HorizontalContentAlignment="Left"
                ContentAlignment="Vertical"
                Description="You can also align your content vertically. Make sure to set the HorizontalAlignment to Left when you do!"
                Header="Vertically aligned">
                <GridView SelectedIndex="1">
                    <GridViewItem>
                        <Border
                            Width="64"
                            Height="64"
                            Background="#0078D4"
                            CornerRadius="4" />
                    </GridViewItem>
                    <GridViewItem>
                        <Border
                            Width="64"
                            Height="64"
                            Background="#005EB7"
                            CornerRadius="4" />
                    </GridViewItem>
                    <GridViewItem>
                        <Border
                            Width="64"
                            Height="64"
                            Background="#003D92"
                            CornerRadius="4" />
                    </GridViewItem>
                    <GridViewItem>
                        <Border
                            Width="64"
                            Height="64"
                            Background="#001968"
                            CornerRadius="4" />
                    </GridViewItem>
                </GridView>
            </essential:SettingsCard>
            <essential:SettingsCard 
                Description="You can override the Left indention of a SettingsCard by overriding the SettingsCardLeftIndention" 
                Header="Customization">
                <essential:SettingsCard.Resources>
                    <x:Double x:Key="SettingsCardLeftIndention">40</x:Double>
                </essential:SettingsCard.Resources>
            </essential:SettingsCard>
        </essential:SettingsExpander.Items>
    </essential:SettingsExpander>
</Page>)");
    }

    winrt::fire_and_forget PlaygroundPage::LoadButton_Click(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        auto const editor = XamlString().Editor();
        editor.TargetWholeDocument();
        winrt::hstring const xaml = editor.GetTargetText();

        /*
            XamlReader::Load hard-crashes (access violation in XamlNamespace::IsConditional)
            instead of throwing when an element uses a namespace that was never declared,
            so refuse to parse a snippet whose root is missing the default xmlns.
         */
        if (std::wstring_view{ xaml }.find(L"xmlns=") == std::wstring_view::npos)
        {
            ErrorText().Message(L"The root element needs xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"");
            co_return;
        }

        long long loadTimeMilliseconds{};
        winrt::hstring error;
		auto strongThis = get_strong();
        switch (RootKind().SelectedIndex())
        {
            case 0:
            {
                co_await CreateWindowWithFactory([xaml, &loadTimeMilliseconds, &error]()->winrt::Windows::UI::Xaml::UIElement
                {
                    auto const t1 = std::chrono::steady_clock::now();
                    try 
                    {
                        auto obj = winrt::Windows::UI::Xaml::Markup::XamlReader::Load(xaml);
                        loadTimeMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - t1).count();
                        return obj.as<winrt::Windows::UI::Xaml::UIElement>();
                    }
					catch (winrt::hresult_error const& e) 
                    {
						error = e.message();
                        return nullptr;
					}
                });
                break;
            }
            case 1: 
            {
                auto const t1 = std::chrono::steady_clock::now();
                try
                {
                    auto obj = winrt::Windows::UI::Xaml::Markup::XamlReader::Load(xaml);
                    loadTimeMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - t1).count();
                    auto contentDialog = obj.as<winrt::Windows::UI::Xaml::Controls::ContentDialog>();
                    contentDialog.ShowAsync();
                }
                catch (winrt::hresult_error const& e)
                {
                    error = e.message();
                }
                break;
            }
            default:
                break;
        }
        ErrorText().Message(error);

        if (error.empty())
        {
            LoadTimeText().Message(std::format(L"Load Time: {} ms", loadTimeMilliseconds));
            LoadTimeText().IsOpen(true);
            ErrorText().IsOpen(false);
        }
        else
        {
            LoadTimeText().IsOpen(false);
            ErrorText().IsOpen(true);
        }
    }
}
