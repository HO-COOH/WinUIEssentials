#pragma once
#include <winrt/base.h>
#include <ppltasks.h>

struct IDWriteFactory;
struct IDWriteFontFile;

namespace DWriteInterop
{
	concurrency::task<winrt::com_ptr<IDWriteFontFile>> GetFontFileFromUri(
		IDWriteFactory* dwriteFactory,
		winrt::Windows::Foundation::Uri const& uri
	);
}