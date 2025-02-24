#pragma once

#include "ExperimentPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ExperimentPage : ExperimentPageT<ExperimentPage>
    {
        ExperimentPage() = default;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ExperimentPage : ExperimentPageT<ExperimentPage, implementation::ExperimentPage>
    {
    };
}
