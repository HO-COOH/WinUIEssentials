#include "pch.h"
#include "IconUtils.h"
#include "GdiInitializeHelper.h"
#include <filesystem>
#include <winrt/Windows.Storage.h>

namespace Utils
{
    HICON Utils::GetHIcon(std::wstring_view file)
    {
        HICON hicon{};
        GdiInitializeHelper::Initialize();

        Gdiplus::Image iconImage{ file.data() };
        INT const width = iconImage.GetWidth();
        INT const height = iconImage.GetHeight();

        Gdiplus::Bitmap bitmap{ width, height };
        auto graphics = Gdiplus::Graphics::FromImage(&bitmap);

        graphics->Clear(Gdiplus::Color::Transparent);
        graphics->DrawImage(&iconImage, 0, 0, width, height);

        bitmap.GetHICON(&hicon);

        winrt::check_pointer(hicon);
        return hicon;
    }

    HICON GetHIcon(winrt::Windows::Foundation::Uri uri)
    {
        return HICON();
    }


}
