#pragma once

#include "DefaultWindowBrokenCaptionButton.g.h"
#include "SupportThemeToggle.h"

namespace winrt::WinUI3Example::implementation
{
    struct DefaultWindowBrokenCaptionButton : DefaultWindowBrokenCaptionButtonT<DefaultWindowBrokenCaptionButton>, public SupportThemeToggle<DefaultWindowBrokenCaptionButton>
    {
        DefaultWindowBrokenCaptionButton()
        {
            ExtendsContentIntoTitleBar(true);
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct DefaultWindowBrokenCaptionButton : DefaultWindowBrokenCaptionButtonT<DefaultWindowBrokenCaptionButton, implementation::DefaultWindowBrokenCaptionButton>
    {
    };
}
