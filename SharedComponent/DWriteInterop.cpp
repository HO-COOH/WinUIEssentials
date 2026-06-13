#include "pch.h"
#include "DWriteInterop.h"
#include <winrt/Windows.Storage.h>
#include <dwrite.h>
#include <pplawait.h>

namespace DWriteInterop
{
	concurrency::task<winrt::com_ptr<IDWriteFontFile>> GetFontFileFromUri(
		IDWriteFactory* dwriteFactory, 
		winrt::Windows::Foundation::Uri const& uri)
	{
		auto file = co_await winrt::Windows::Storage::StorageFile::GetFileFromApplicationUriAsync(uri);
		winrt::com_ptr<IDWriteFontFile> fontFile;
		winrt::check_hresult(dwriteFactory->CreateFontFileReference(file.Path().data(), nullptr, fontFile.put()));
		co_return fontFile;
	}
}