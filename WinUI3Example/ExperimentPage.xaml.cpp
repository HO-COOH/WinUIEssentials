#include "pch.h"
#include "ExperimentPage.xaml.h"
#if __has_include("ExperimentPage.g.cpp")
#include "ExperimentPage.g.cpp"
#endif
#include <VisualTreeHelper.hpp>
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include "MorphAnimationHelper.h"
#include <ppltasks.h>
#include <pplawait.h>


static void restoreVisual(winrt::Microsoft::UI::Composition::Visual const& visual, winrt::Microsoft::UI::Composition::CompositionAnimationGroup const& animationGroup, bool isSourceToTarget = true)
{
	visual.StopAnimationGroup(animationGroup);
	visual.Properties().InsertVector3(L"Translation", {});
	visual.Scale({ 1.f, 1.f, 1.f });
	visual.Opacity(isSourceToTarget ? 1.f : 0.f);
}

static winrt::Windows::Foundation::IAsyncAction waitForLayoutUpdateAsync(winrt::Microsoft::UI::Xaml::FrameworkElement const& element)
{
	concurrency::task_completion_event<void> event;
	element.LayoutUpdated([event](auto&&...) {
		event.set();
		});
	element.UpdateLayout();
	co_await concurrency::task<void>{ event };
}

namespace winrt::WinUI3Example::implementation
{

	void ExperimentPage::TestWindowBtn_Click(
		winrt::Windows::Foundation::IInspectable const&,
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::TestWindow{}.Activate();
	}

	void ExperimentPage::SelfDrawnWindowButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::EntranceAnimationDemo{}.Activate();
	}

	void ExperimentPage::CreateNonResizableBtn_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::NormalNonResizableWindow{}.Activate();
	}

	void ExperimentPage::CreateNonResizableWithWorkaroundBtn_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::NonResizableWindowWithWorkaround{}.Activate();
	}

	void ExperimentPage::FlipWindowButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::FlipWindow{}.Activate();
	}


	void winrt::WinUI3Example::implementation::ExperimentPage::ButtonMorph_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		morphButtonToProgressBar(ButtonMorph(), ProgressBarMorph(), std::chrono::milliseconds{600});
	}

	void ExperimentPage::SlowButtonMorph_Click(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		morphButtonToProgressBar(ButtonMorph(), ProgressBarMorph(), std::chrono::milliseconds{ 3000 });
	}

	winrt::fire_and_forget ExperimentPage::morphButtonToProgressBar(
		winrt::Microsoft::UI::Xaml::Controls::Button button,
		winrt::Microsoft::UI::Xaml::Controls::ProgressBar progressBar,
		std::chrono::milliseconds duration
	)
	{
		//set both visual able to do Translation
		winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetIsTranslationEnabled(button, true);

		//get both visual
		auto buttonVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(button);
		if (buttonAnimationGroup)
		{
			restoreVisual(buttonVisual, buttonAnimationGroup);
			co_await waitForLayoutUpdateAsync(button);
		}

		auto compositor = buttonVisual.Compositor();
		
		if (progressBar.Visibility() == winrt::Microsoft::UI::Xaml::Visibility::Collapsed || !progressBar.IsLoaded())
		{
			progressBar.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			co_await waitForLayoutUpdateAsync(progressBar);
		}
		auto progressBarRootGrid = VisualTreeHelper::FindVisualChildByType<winrt::Microsoft::UI::Xaml::Shapes::Rectangle>(progressBar)
			.Parent()
			.as<winrt::Microsoft::UI::Xaml::Controls::Grid>();
		auto progressBarVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(progressBarRootGrid);
		if (progressBarAnimationGroup)
		{
			restoreVisual(progressBarVisual, progressBarAnimationGroup, false);
			co_await waitForLayoutUpdateAsync(progressBar);
		}
		winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetIsTranslationEnabled(progressBarRootGrid, true);
		//get both size
		auto const sourceSize = button.ActualSize();
		auto const targetSize = progressBarRootGrid.ActualSize();

		//get translation
		auto const p = button.TransformToVisual(progressBarRootGrid).TransformPoint({});

		//source animation
		using namespace MorphAnimationHelper;
		buttonAnimationGroup = CreateAnimationGroup(compositor,
			CreateSourceScaleAnimation(compositor, sourceSize, targetSize, true, duration),
			CreateTranslationAnimation(compositor, p, true, duration),
			CreateOpacityAnimation(compositor, true, duration)
		);
		buttonVisual.StartAnimationGroup(buttonAnimationGroup);



		progressBarAnimationGroup = CreateAnimationGroup(compositor,
			CreateSourceScaleAnimation(compositor, sourceSize, targetSize, false, duration),
			CreateTranslationAnimation(compositor, p, false, duration),
			CreateOpacityAnimation(compositor, false, duration));
		progressBarVisual.StartAnimationGroup(progressBarAnimationGroup);
	}
}
