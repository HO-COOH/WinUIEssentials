#pragma once
#include <winrt/Windows.Web.Http.h>

class GithubRequest : public winrt::Windows::Web::Http::HttpRequestMessage
{
public:
	GithubRequest(wchar_t const* url);
};