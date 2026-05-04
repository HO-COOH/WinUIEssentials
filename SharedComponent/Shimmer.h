#pragma once

#include "Shimmer.g.h"
#include "include/EnsureDependencyProperty.hpp"
#include <optional>
#include "Shimmer.AnimationMember.h"
#include "include/TemplateControlHelper.hpp"

namespace winrt::PackageRoot::implementation
{
    struct Shimmer : ShimmerT<Shimmer>, TemplateControlHelper<Shimmer>, EnsureDependencyProperty<Shimmer>
    {
        static void EnsureDependencyProperties();
        Shimmer() = default;

        bool IsLoading();

#if defined Build_WinUIPackage
        constexpr static auto ResourceUri = L"ms-appx:///WinUI3Package/Shimmer_Resource.xaml";
#else
        constexpr static auto ResourceUri = L"ms-appx:///UWPPackage/Shimmer_Resource.xaml";
#endif

        void IsLoading(bool value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty IsLoadingProperty();

        winrt::WinUINamespace::UI::Xaml::Media::GradientStopCollection GradientStops();
        void GradientStops(winrt::WinUINamespace::UI::Xaml::Media::GradientStopCollection const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty GradientStopsProperty();

        void OnApplyTemplate();
    private:
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_isLoadingProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_gradientStopsProperty = nullptr;
        winrt::WinUINamespace::UI::Xaml::FrameworkElement m_animationContainer{ nullptr };
        winrt::WinUINamespace::UI::Xaml::FrameworkElement::SizeChanged_revoker m_animationSizeChangedRevoker;
        void startAnimation();

        void applyGradientStops();

        // IsLoading == true
        void loadShimmer();

        // IsLoading == false
        void loadContent();

        static bool removeChildFromPanel(
            winrt::WinUINamespace::UI::Xaml::Controls::Panel const& panel,
            winrt::WinUINamespace::UI::Xaml::FrameworkElement const& child
        );

        std::optional<ShimmerAnimationMember> m_animation;
        winrt::WinUINamespace::UI::Xaml::Controls::ContentPresenter m_presenter{ nullptr };
        winrt::WinUINamespace::UI::Xaml::Controls::Panel m_rootPanel{ nullptr };
        bool m_loaded{};
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct Shimmer : ShimmerT<Shimmer, implementation::Shimmer>
    {
    };
}
