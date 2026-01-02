#include "pch.h"
#include "GithubRequest.h"
#include <winrt/Windows.Web.Http.Headers.h>

GithubRequest::GithubRequest(wchar_t const* url) :
	HttpRequestMessage{ winrt::Windows::Web::Http::HttpMethod::Get(), winrt::Windows::Foundation::Uri{url} }
{
	Headers().Append(L"User-Agent", L"WinUI3ExampleApp");
}