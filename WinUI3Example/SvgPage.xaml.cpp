#include "pch.h"
#include "SvgPage.xaml.h"
#if __has_include("SvgPage.g.cpp")
#include "SvgPage.g.cpp"
#endif

#include <winrt/Microsoft.UI.Xaml.Media.Imaging.h>
#include "TestSvgUrls.hpp"


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> SvgPage::Svgs()
	{
		if (m_svgs)
			return m_svgs;

		std::vector<winrt::Windows::Foundation::IInspectable> transformed;
		transformed.reserve(std::size(TestSvgUrls::urls));
		std::transform(
			std::begin(TestSvgUrls::urls),
			std::end(TestSvgUrls::urls),
			std::back_inserter(transformed),
			[](auto url) {return winrt::Windows::Foundation::Uri{ url }; }
		);
		m_svgs = winrt::single_threaded_vector(std::move(transformed));
		return m_svgs;
	}


	winrt::Windows::Foundation::Uri SvgPage::GetPngFromSvgUrl(winrt::Windows::Foundation::IInspectable const& item)
	{
		auto uri = item.as<winrt::Windows::Foundation::Uri>();
		std::wstring s{ uri.RawUri() };
		if (auto p = s.find(L"/svg/"); p != std::wstring::npos)
			s.replace(p, 5, L"/png/");
		if (auto e = s.rfind(L".svg"); e != std::wstring::npos)
			s.replace(e, 4, L".png");
		return winrt::Windows::Foundation::Uri{ winrt::hstring{ s } };
	}

	winrt::Microsoft::UI::Xaml::Media::ImageSource SvgPage::GetSvgImageSourceFromString(winrt::hstring const& svgContent)
	{
		winrt::Microsoft::UI::Xaml::Media::Imaging::SvgImageSource source;
		if (svgContent.empty())
			return source;

		[](auto source, auto svgContent)->winrt::fire_and_forget
		{
			winrt::Windows::Storage::Streams::InMemoryRandomAccessStream stream;
			winrt::Windows::Storage::Streams::DataWriter writer{ stream };
			writer.UnicodeEncoding(winrt::Windows::Storage::Streams::UnicodeEncoding::Utf8);
			writer.WriteString(svgContent);
			co_await writer.StoreAsync();
			writer.DetachStream();
			stream.Seek(0);
			source.SetSourceAsync(stream);
		}(source, svgContent);
		
		return source;
	}
}
